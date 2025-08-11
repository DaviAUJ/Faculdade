#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#pragma region Global

#define BUFFER_LEN 1000000
#define WRITE_MODE "w"
#define READ_MODE "r"
#define DEC_OFFSET 48
#define HEX_OFFSET 55

typedef struct {
    FILE *file;
    char buffer[BUFFER_LEN];
    uint32_t cursor;
} fileBuffer_t;

typedef uint32_t instruction_t;

fileBuffer_t input;
fileBuffer_t output;

const char HEX_TABLE[] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
};

const char* DEC_TABLE[] = {
    "0",  "1",  "2",  "3",
    "4",  "5",  "6",  "7",
    "8",  "9",  "10", "11",
    "12", "13", "14", "15"
};

uint16_t pc;
uint32_t stats[16];
int32_t reg[16];
uint8_t mem[256];
bool flags[3];

#pragma endregion

#pragma region EntradaSaida

void fileBuffer_Init(fileBuffer_t* buffer, const char* file_name, const char* mode) {
    buffer->file = fopen(file_name, mode);
    buffer->cursor = 0;
}

instruction_t readInstruction() {
    uint8_t ins_bytes_rev[4] = {0};
    uint8_t offset;

    for(int8_t i = 0; i < 4; i++) {
        input.cursor += 2;
        offset = input.buffer[input.cursor] >= 'A' ? HEX_OFFSET : DEC_OFFSET;
        ins_bytes_rev[i] = (input.buffer[input.cursor] - offset) << 4;

        input.cursor++;
        offset = input.buffer[input.cursor] >= 'A' ? HEX_OFFSET : DEC_OFFSET;
        ins_bytes_rev[i] += (input.buffer[input.cursor] - offset);

        input.cursor += 2;
    }

    return *(instruction_t*)ins_bytes_rev;
}

void writeChar(const char c) {
    output.buffer[output.cursor++] = c;
}

void writeString(const char* str, const uint8_t len) {
    memcpy(&output.buffer[output.cursor], str, len);
    output.cursor += len;
}

void writeHex(uint64_t integer, int8_t n_digits) {
    writeString("0x", 2);
    
    output.cursor += n_digits;
    uint32_t temp_cursor = output.cursor;
    
    while(n_digits--) {
        output.buffer[--temp_cursor] = HEX_TABLE[integer & 0x0F];
        integer >>= 4;
    }
}

void writeRegNumber(const uint8_t reg_number) {
    writeChar('R');
    writeString(DEC_TABLE[reg_number], reg_number >= 10 ? 2 : 1);
}

void writeDec(const uint64_t integer) {

}

void write_movImm(const uint8_t reg_number_dst, const int16_t imm) {
    writeHex(pc, 4);
    writeString("->MOV_", 6);
    writeRegNumber(reg_number_dst);
    writeChar('=');
    writeHex((uint64_t)imm, 8);
    writeChar('\n');
}

void write_movReg(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    writeHex(pc, 4);
    writeString("->MOV_", 6);
    writeRegNumber(reg_number_dst);
    writeChar('=');
    writeRegNumber(reg_number_src);
    writeChar('=');
    writeHex(reg_number_src, 8);
    writeChar('\n');
}

void write_movFromMem(const uint8_t reg_number_dst, const uint8_t mem_addr) {
    writeHex(pc, 4);
    writeString("->MOV_", 6);
    writeRegNumber(reg_number_dst);
    writeString("=MEM[", 5);
    writeHex(mem_addr - 4, 2);
    writeChar(',');
    writeHex(mem_addr - 3, 2);
    writeChar(',');
    writeHex(mem_addr - 2, 2);
    writeChar(',');
    writeHex(mem_addr - 1, 2);
    writeString("]=[", 3);
    writeHex(mem[mem_addr - 4], 2);
    writeChar(',');
    writeHex(mem[mem_addr - 3], 2);
    writeChar(',');
    writeHex(mem[mem_addr - 2], 2);
    writeChar(',');
    writeHex(mem[mem_addr - 1], 2);
    writeString("]\n", 2);
}

void write_movToMem(const uint8_t mem_addr, const int8_t reg_number_src) {
    const uint32_t a = reg[reg_number_src];
    
    writeHex(pc, 4);
    writeString("->MOV_MEV[", 10);
    writeHex(mem_addr - 4, 2);
    writeChar(',');
    writeHex(mem_addr - 3, 2);
    writeChar(',');
    writeHex(mem_addr - 2, 2);
    writeChar(',');
    writeHex(mem_addr - 1, 2);
    writeString("]=", 2);
    writeRegNumber(reg_number_src);
    writeString("=[", 2);
    writeHex(a >> 24, 2);
    writeChar(',');
    writeHex(a >> 16, 2);
    writeChar(',');
    writeHex(a >> 8, 2);
    writeChar(',');
    writeHex(a, 2);
    writeString("]\n", 2);
}

void write_cmp(const uint8_t reg_number_a, const int8_t reg_number_b) {
    writeHex(pc, 4);
    writeString("->CMP_", 6);
    writeRegNumber(reg_number_a);
    writeString("<=>", 3);
    writeRegNumber(reg_number_b);
    writeString("(G=0,L=0,E=1)\n", 14);
}

void write_jmp(const int16_t addr) {
    writeHex(pc, 4);
    writeString("->JMP_", 6);
    writeHex(4 + pc + addr, 4);
    writeChar('\n');
}

void write_jg(const int16_t addr) {
    writeHex(pc, 4);
    writeString("->JG_", 5);
    writeHex(4 + pc + addr, 4);
    writeChar('\n');
}

void write_jl(const int16_t addr) {
    writeHex(pc, 4);
    writeString("->JL_", 5);
    writeHex(4 + pc + addr, 4);
    writeChar('\n');
}

void write_je(const int16_t addr) {
    writeHex(pc, 4);
    writeString("->JE_", 5);
    writeHex(4 + pc + addr, 4);
    writeChar('\n');
}

void write_add(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    writeHex(pc, 4);
    writeString("->ADD_", 6);
    writeRegNumber(reg_number_dst);
    writeString("+=", 2);
    writeRegNumber(reg_number_src);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeChar('+');
    writeHex(reg[reg_number_src], 8);
    writeChar('=');
    writeHex(reg[reg_number_dst] + reg[reg_number_src], 8);
    writeChar('\n');
}

void write_sub(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    writeHex(pc, 4);
    writeString("->SUB_", 6);
    writeRegNumber(reg_number_dst);
    writeString("-=", 2);
    writeRegNumber(reg_number_src);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeChar('-');
    writeHex(reg[reg_number_src], 8);
    writeChar('=');
    writeHex(reg[reg_number_dst] - reg[reg_number_src], 8);
    writeChar('\n');
}

void write_and(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    writeHex(pc, 4);
    writeString("->AND_", 6);
    writeRegNumber(reg_number_dst);
    writeString("&=", 2);
    writeRegNumber(reg_number_src);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeChar('&');
    writeHex(reg[reg_number_src], 8);
    writeChar('=');
    writeHex(reg[reg_number_dst] & reg[reg_number_src], 8);
    writeChar('\n');
}

void write_or(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    writeHex(pc, 4);
    writeString("->OR_", 5);
    writeRegNumber(reg_number_dst);
    writeString("|=", 2);
    writeRegNumber(reg_number_src);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeChar('|');
    writeHex(reg[reg_number_src], 8);
    writeChar('=');
    writeHex(reg[reg_number_dst] | reg[reg_number_src], 8);
    writeChar('\n');
}

void write_xor(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    writeHex(pc, 4);
    writeString("->XOR_", 6);
    writeRegNumber(reg_number_dst);
    writeString("^=", 2);
    writeRegNumber(reg_number_src);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeChar('^');
    writeHex(reg[reg_number_src], 8);
    writeChar('=');
    writeHex(reg[reg_number_dst] ^ reg[reg_number_src], 8);
    writeChar('\n');
}

void write_sal(const uint8_t reg_number_dst, const uint8_t imm) {
    writeHex(pc, 4);
    writeString("->SAL_", 6);
    writeRegNumber(reg_number_dst);
    writeString("<<=", 3);
    writeString(DEC_TABLE[imm & 0x0F], imm >= 10 ? 2 : 1);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeString("<<", 2);
    writeString(DEC_TABLE[imm & 0x0F], imm >= 10 ? 2 : 1);
    writeChar('=');
    writeHex(reg[reg_number_dst] << imm, 8);
    writeChar('\n');
}

void write_sar(const uint8_t reg_number_dst, const uint8_t imm) {
    writeHex(pc, 4);
    writeString("->SAR_", 6);
    writeRegNumber(reg_number_dst);
    writeString(">>=", 3);
    writeString(DEC_TABLE[imm & 0x0F], imm >= 10 ? 2 : 1);
    writeChar('=');
    writeHex(reg[reg_number_dst], 8);
    writeString(">>", 2);
    writeString(DEC_TABLE[imm & 0x0F], imm >= 10 ? 2 : 1);
    writeChar('=');
    writeHex(reg[reg_number_dst] >> imm, 8);
    writeChar('\n');
}

void write_end() {
    writeHex(pc, 4);
    writeString("->EXIT\n", 7);
}

void write_RegStats() {
    output.cursor += sprintf(
        &output.buffer[output.cursor],
        "[00:%d,01:%d,02:%d,03:%d,04:%d,05:%d,06:%d,07:%d,08:%d,09:%d,0A:%d,0B:%d,0C:%d,0D:%d,0E:%d,0F:%d]\n",
        stats[0],  stats[1],  stats[2],  stats[3], 
        stats[4],  stats[5],  stats[6],  stats[7], 
        stats[8],  stats[9],  stats[10], stats[11], 
        stats[12], stats[13], stats[14], stats[15]
    );
}

void write_AllRegs() {
    writeString("[R0=", 4);
    writeHex(reg[0], 8);
    writeString(",R1=", 4);
    writeHex(reg[1], 8);
    writeString(",R1=", 4);
    writeHex(reg[1], 8);
    writeString(",R2=", 4);
    writeHex(reg[2], 8);
    writeString(",R3=", 4);
    writeHex(reg[3], 8);
    writeString(",R4=", 4);
    writeHex(reg[4], 8);
    writeString(",R5=", 4);
    writeHex(reg[5], 8);
    writeString(",R6=", 4);
    writeHex(reg[6], 8);
    writeString(",R7=", 4);
    writeHex(reg[7], 8);
    writeString(",R8=", 4);
    writeHex(reg[8], 8);
    writeString(",R9=", 4);
    writeHex(reg[9], 8);
    writeString(",R10=", 5);
    writeHex(reg[10], 8);
    writeString(",R11=", 5);
    writeHex(reg[11], 8);
    writeString(",R12=", 5);
    writeHex(reg[12], 8);
    writeString(",R13=", 5);
    writeHex(reg[13], 8);
    writeString(",R14=", 5);
    writeHex(reg[14], 8);
    writeString(",R15=", 5);
    writeHex(reg[15], 8);
    writeChar(']');
}

#pragma endregion

#pragma region PicoQuickProcessor


void loadMem() {
    for(pc = 0; pc < 256; pc += 4) {
        const instruction_t ins = readInstruction();
        *(uint32_t*)&mem[pc] = ins;

        if(input.buffer[input.cursor] == '\0') {
            pc = 0;
            return;
        }
    }
}

void movImm(const uint8_t reg_number_dst, const int16_t imm) {
    reg[reg_number_dst] = (int32_t)imm;
}

void movReg(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    reg[reg_number_dst] = reg[reg_number_src];
}

void movFromMem(const uint8_t reg_number_dst, const uint8_t mem_addr) {
    reg[reg_number_dst] = *(int32_t*)&mem[mem_addr - 4];
}

void movToMem(const uint8_t mem_addr, const uint8_t reg_number_src) {
    *(int32_t*)&mem[mem_addr - 4] = reg[reg_number_src];
}

void cmp(const uint8_t reg_number_a, const uint8_t reg_number_b) {
    if(reg[reg_number_a] == reg[reg_number_b]) {
        flags[0] = false;
        flags[1] = false;
        flags[2] = true;

        return;
    }

    if(reg[reg_number_a] > reg[reg_number_b]) {
        flags[0] = true;
        flags[1] = false;
        flags[2] = false;
        
        return;
    }

    flags[0] = false;
    flags[1] = true;
    flags[2] = false;
}

void jmp(const int16_t addr) {
    pc += (int32_t)addr;
}

void jg(const int16_t addr) {
    if(flags[0]) {
        pc += (int32_t)addr;
    }
}

void jl(const int16_t addr) {
    if(flags[1]) {
        pc += (int32_t)addr;
    }
}

void je(const int16_t addr) {
    if(flags[2]) {
        pc += (int32_t)addr;
    }
}

void add(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    reg[reg_number_dst] += reg[reg_number_src];
}

void sub(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    reg[reg_number_dst] -= reg[reg_number_src];
}

void and(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    reg[reg_number_dst] &= reg[reg_number_src];
}

void or(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    reg[reg_number_dst] |= reg[reg_number_src];
}

void xor(const uint8_t reg_number_dst, const uint8_t reg_number_src) {
    reg[reg_number_dst] ^= reg[reg_number_src];
}

void sal(const uint8_t reg_number_dst, const uint8_t imm) {
    reg[reg_number_dst] <<= (imm & 0x0F);
}

void sar(const uint8_t reg_number_dst, const uint8_t imm) {
    reg[reg_number_dst] >>= (imm & 0x0F);
}

void exec(const instruction_t ins) {
    const uint8_t* ins_bytes = (uint8_t*)&ins;

    switch(ins_bytes[0]) {
        case 0x00: {
            movImm(ins_bytes[1] >> 4, *(int16_t*)&ins_bytes[2]);
            break;
        }
            
        case 0x01: {
            movReg(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x02: {
            movFromMem(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x03: {
            movToMem(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x04: {
            cmp(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x05: {
            jmp(*(int16_t*)&ins_bytes[2]);
            break;
        }

        case 0x06: {
            jg(*(int16_t*)&ins_bytes[2]);
            break;
        }

        case 0x07: {
            jl(*(int16_t*)&ins_bytes[2]);
            break;
        }

        case 0x08: {
            je(*(int16_t*)&ins_bytes[2]);
            break;
        }

        case 0x09: {
            add(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x0A: {
            sub(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x0B: {
            and(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x0C: {
            or(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x0D: {
            xor(ins_bytes[1] >> 4, ins_bytes[1] & 0x0F);
            break;
        }

        case 0x0E: {
            sal(ins_bytes[1] >> 4, ins_bytes[3]);
            break;
        }

        case 0x0F: {
            sar(ins_bytes[1] >> 4, ins_bytes[3]);
            break;
        }
        default: ;
    }

    pc += 4;
}

#pragma endregion

#pragma region Translation

uint8_t fa_program[] = { 0x90 };

void run_fa() {
    
}

#pragma endregion

int main(int argc, char **argv) {
    fileBuffer_Init(&input, argv[1], READ_MODE);
    fileBuffer_Init(&output, argv[2], WRITE_MODE);
    
    fread(input.buffer, 1, BUFFER_LEN, input.file);

    loadMem();

    while(pc <= 252) {
        exec(*(instruction_t*)&mem[pc]);
    }

    write_end();
    write_RegStats();
    write_AllRegs();

    fwrite(output.buffer, 1, output.cursor, output.file);

    fclose(input.file);
    fclose(output.file);
}
