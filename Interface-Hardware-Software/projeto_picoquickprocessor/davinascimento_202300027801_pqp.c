#define  _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <ucontext.h>
#include <signal.h>

/*

$$$$$$$\  $$$$$$$\  $$\   $$\ $$\   $$\  $$$$$$\         $$$$$$\   $$$$$$\  $$$$$$$$\  $$$$$$\  $$$$$$$\   $$$$$$\  
$$  __$$\ $$  __$$\ $$ |  $$ |$$$\  $$ |$$  __$$\       $$  __$$\ $$  __$$\ $$  _____|$$  __$$\ $$  __$$\ $$  __$$\ 
$$ |  $$ |$$ |  $$ |$$ |  $$ |$$$$\ $$ |$$ /  $$ |      $$ /  \__|$$ /  $$ |$$ |      $$ /  $$ |$$ |  $$ |$$ /  $$ |
$$$$$$$\ |$$$$$$$  |$$ |  $$ |$$ $$\$$ |$$ |  $$ |      \$$$$$$\  $$$$$$$$ |$$$$$\    $$$$$$$$ |$$ |  $$ |$$ |  $$ |
$$  __$$\ $$  __$$< $$ |  $$ |$$ \$$$$ |$$ |  $$ |       \____$$\ $$  __$$ |$$  __|   $$  __$$ |$$ |  $$ |$$ |  $$ |
$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |\$$$ |$$ |  $$ |      $$\   $$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |
$$$$$$$  |$$ |  $$ |\$$$$$$  |$$ | \$$ | $$$$$$  |      \$$$$$$  |$$ |  $$ |$$ |      $$ |  $$ |$$$$$$$  | $$$$$$  |
\_______/ \__|  \__| \______/ \__|  \__| \______/        \______/ \__|  \__|\__|      \__|  \__|\_______/  \______/

*/

#define BUFFER_LEN      10000000
#define DEC_OFFSET      48
#define HEX_OFFSET      55
#define WRITE_MODE      "w"
#define READ_MODE       "r"
#define PAGE_SIZE       4096
#define INT_3           0xCC
#define NOP1            0x90
#define NOP2            0x90, NOP1
#define NOP3            0x90, NOP2
#define NOP4            0x90, NOP3
#define NOP5            0x90, NOP4
#define NOP6            0x90, NOP5
#define NOP7            0x90, NOP6
#define OPCODE_SIZE     16
#define HALF_OPCODE     8

#define INSINS(x)           memcpy(fa_bytes_cursor, x, OPCODE_SIZE);fa_bytes_cursor += 9
#define PHEXSEQ(ptr, x, y)  for(uint16_t i = 0; i < x; i++) { printf("%2.2X%c", ptr[i], ((i+1)%y) ? ' ' : '\n'); }
#define TESTE               printf("TESTE\n")
#define BITSET(var, nbit)   ((var) |=  (1<<(nbit)))
#define BITCLEAR(var, nbit) ((var) &= ~(1<<(nbit)))

typedef struct {
    FILE     *file;
    char     buffer[BUFFER_LEN];
    char     *cursor;
} fileBuffer_t;

typedef struct {
    uint32_t pqp_opcodes;
    bool     was_translated;
    uint8_t  *exec; 
} instruction_t;

uint32_t *XMM_INC_0;
uint32_t *XMM_INC_1;
uint32_t *XMM_INC_2;
uint32_t *XMM_INC_3;

uint8_t SAR_1[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xF8, 0x00,       NOP4 };
uint8_t SAR_2[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0xC1, 0xF8, 0x00, NOP3 };

uint8_t SAL_1[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xE0, 0x00,       NOP4 };
uint8_t SAL_2[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0xC1, 0xE0, 0x00, NOP3 };

uint8_t XOR_1[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x31, 0xC0,       NOP5 };
uint8_t XOR_2[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x31, 0xC0, NOP4 };
uint8_t XOR_3[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x31, 0xC0, NOP4 };
uint8_t XOR_4[]   = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x31, 0xC0, NOP4 };

uint8_t OR_1[]    = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x09, 0xC0,       NOP5 };
uint8_t OR_2[]    = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x09, 0xC0, NOP4 };
uint8_t OR_3[]    = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x09, 0xC0, NOP4 };
uint8_t OR_4[]    = { 0x66, 0x0F, 0xFE, 0x24, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x09, 0xC0, NOP4 };

uint8_t AND_1[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x21, 0xC0,       NOP5 };
uint8_t AND_2[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x21, 0xC0, NOP4 };
uint8_t AND_3[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x21, 0xC0, NOP4 };
uint8_t AND_4[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x21, 0xC0, NOP4 };

uint8_t SUB_1[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x29, 0xC0,       NOP5 };
uint8_t SUB_2[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x29, 0xC0, NOP4 };
uint8_t SUB_3[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x29, 0xC0, NOP4 };
uint8_t SUB_4[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x29, 0xC0, NOP4 };

uint8_t ADD_1[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0,       NOP5 };
uint8_t ADD_2[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x01, 0xC0, NOP4 };
uint8_t ADD_3[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x01, 0xC0, NOP4 };
uint8_t ADD_4[]   = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x01, 0xC0, NOP4 };

uint8_t JE_1[]    = { 0x66, 0x0F, 0xFE, 0x1C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, NOP1 };

uint8_t JL_1[]    = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x8C, 0x00, 0x00, 0x00, 0x00, NOP1 };

uint8_t JG_1[]    = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x8F, 0x00, 0x00, 0x00, 0x00, NOP1 };

uint8_t JMP_1[]   = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00,       NOP2 };

uint8_t CMP_1[]   = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0x39, 0xC0,       NOP5 };
uint8_t CMP_2[]   = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x39, 0xC0, NOP4 };
uint8_t CMP_3[]   = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x39, 0xC0, NOP4 };
uint8_t CMP_4[]   = { 0x66, 0x0F, 0xFE, 0x14, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x39, 0xC0, NOP4 };

uint8_t MOVMR_1[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x89, 0x80, 0x00, 0x00, 0x00, 0x00, NOP1 };
uint8_t MOVMR_2[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x89, 0x80, 0x00, 0x00, 0x00, 0x00 };
uint8_t MOVMR_3[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x89, 0x80, 0x00, 0x00, 0x00, 0x00 };
uint8_t MOVMR_4[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x89, 0x80, 0x00, 0x00, 0x00, 0x00 };

uint8_t MOVRM_1[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x80, 0x00, 0x00, 0x00, 0x00, NOP1 };
uint8_t MOVRM_2[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x8B, 0x80, 0x00, 0x00, 0x00, 0x00 };
uint8_t MOVRM_3[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x8B, 0x80, 0x00, 0x00, 0x00, 0x00 };
uint8_t MOVRM_4[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x8B, 0x80, 0x00, 0x00, 0x00, 0x00 };

uint8_t MOVRR_1[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x89, 0xC0,       NOP5 };
uint8_t MOVRR_2[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0x89, 0xC0, NOP4 };
uint8_t MOVRR_3[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x44, 0x89, 0xC0, NOP4 };
uint8_t MOVRR_4[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x45, 0x89, 0xC0, NOP4 };

uint8_t MOVRI_1[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00, 0x00,       NOP2 };
uint8_t MOVRI_2[] = { 0x66, 0x0F, 0xFE, 0x0C, 0x25, 0x00, 0x00, 0x00, 0x00, 0x41, 0xB8, 0x00, 0x00, 0x00, 0x00, NOP1 };

fileBuffer_t input;
fileBuffer_t output;

instruction_t control[64];
uint8_t       control_pc;
uint8_t       *fa_bytes;
uint8_t       *fa_bytes_end;
uint8_t       qof_instructions;
uint8_t       *fa_bytes_cursor;

uint16_t pc;
uint32_t *stats;
int32_t  regs[16] = {0};
uint8_t  *byte_mem;
uint32_t *word_mem;
bool     flags[3];

struct sigaction sa_jitting;
struct sigaction sa_ending;
stack_t          alt_stack;
ucontext_t       jit_ctx;
ucontext_t       native_ctx;
bool             jump_native;
bool             coming_from_jit;
instruction_t    *current;
ucontext_t       *handler_ctx;

uint64_t         semnome0;
uint64_t         semnome1;
uint64_t         semnome2;
const uint32_t bosta = {0, 0, 0, 0};

void printctx(ucontext_t *some) {
    printf(
        "EAX: %d\n"
        "ECX: %d\n"
        "EDX: %d\n"
        "EBX: %d\n"
        "ESP: %d\n"
        "EBP: %d\n"
        "ESI: %d\n"
        "EDI: %d\n"
        "R8D: %d\n"
        "R9D: %d\n"
        "R10D: %d\n"
        "R11D: %d\n"
        "R12D: %d\n"
        "R13D: %d\n"
        "R14D: %d\n"
        "R15D: %d\n"
        "EFL: %d\n"
        "RIP: %d\n",
        some->uc_mcontext.gregs[REG_RAX],
        some->uc_mcontext.gregs[REG_RCX],
        some->uc_mcontext.gregs[REG_RDX],
        some->uc_mcontext.gregs[REG_RBX],
        some->uc_mcontext.gregs[REG_RSP],
        some->uc_mcontext.gregs[REG_RBP],
        some->uc_mcontext.gregs[REG_RSI],
        some->uc_mcontext.gregs[REG_RDI],
        some->uc_mcontext.gregs[REG_R8] ,
        some->uc_mcontext.gregs[REG_R9] ,
        some->uc_mcontext.gregs[REG_R10],
        some->uc_mcontext.gregs[REG_R11],
        some->uc_mcontext.gregs[REG_R12],
        some->uc_mcontext.gregs[REG_R13],
        some->uc_mcontext.gregs[REG_R14],
        some->uc_mcontext.gregs[REG_R15],
        some->uc_mcontext.gregs[REG_EFL],
        some->uc_mcontext.gregs[REG_RIP]
    );
}

void loadMem() {
    uint8_t  offset;
    uint16_t i;

    for(i = 0; i < 256 && *input.cursor != '\0'; i++) {
        input.cursor += 2;
        offset = *input.cursor >= 'A' ? HEX_OFFSET : DEC_OFFSET;
        byte_mem[i] = (*input.cursor - offset) << 4;

        input.cursor++;
        offset = *input.cursor >= 'A' ? HEX_OFFSET : DEC_OFFSET;
        byte_mem[i] += (*input.cursor - offset);

        input.cursor += 2;
    }

    qof_instructions = i >> 2;
}

void changePCs(const uint16_t new_value) {
    pc = new_value;
    control_pc = pc >> 2;
}

void addPCs(const int16_t new_value) {
    pc += new_value;
    control_pc += new_value >> 2;
}

void incPCs() {
    pc += 4;
    control_pc++;
}

void interpretTranslate(instruction_t *instruction, uint32_t pqp_opcodes) {
    const uint8_t *ins_bytes = (uint8_t*)&pqp_opcodes;

    instruction->pqp_opcodes = pqp_opcodes;
    fa_bytes_cursor = &fa_bytes[control_pc * OPCODE_SIZE];
    stats[ins_bytes[0]]++;

    output.cursor += sprintf(
        output.cursor,
        "0x%04X->",
        pc
    );

    switch(ins_bytes[0]) {
        case 0x00: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const int16_t imm = *(int16_t*)&ins_bytes[2];

            regs[reg_number_dst] = imm;

            output.cursor += sprintf(
                output.cursor,
                "MOV_R%d=0x%08X\n",
                reg_number_dst,
                regs[reg_number_dst]
            );

            if(reg_number_dst < 8) {
                INSINS(MOVRI_1);

                fa_bytes_cursor[0] += reg_number_dst;
                *(int32_t*)&fa_bytes_cursor[1] = imm;
            }
            else {
                INSINS(MOVRI_2);

                fa_bytes_cursor[1] += reg_number_dst - 8;
                *(int32_t*)&fa_bytes_cursor[2] = imm;
            }
            
            break;
        }
            
        case 0x01: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "MOV_R%d=R%d=0x%08X\n",
                reg_number_dst,
                reg_number_src,
                regs[reg_number_src]
            );

            regs[reg_number_dst] = regs[reg_number_src];

            if(reg_number_dst < 8) {
                if(reg_number_src < 8) {
                    INSINS(MOVRR_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_src * 0x08);
                }
                else {
                    INSINS(MOVRR_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_src - 8) * 0x08);
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(MOVRR_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_src * 0x08);
                }
                else {
                    INSINS(MOVRR_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_src - 8) * 0x08);
                }
            }

            break;
        }

        case 0x02: {
            const uint8_t reg_number_mem = ins_bytes[1] >> 4;
            const uint8_t reg_number_dst = ins_bytes[1] & 0x0F;
            const uint8_t pqp_addr = regs[reg_number_dst] & 0xFF;

            output.cursor += sprintf(
                output.cursor,
                "MOV_R%d=MEM[0x%02X,0x%02X,0x%02X,0x%02X]=[0x%02X,0x%02X,0x%02X,0x%02X]\n",
                reg_number_mem,
                pqp_addr,
                pqp_addr + 1,
                pqp_addr + 2,
                pqp_addr + 3,
                byte_mem[pqp_addr],
                byte_mem[pqp_addr + 1],
                byte_mem[pqp_addr + 2],
                byte_mem[pqp_addr + 3]
            );

            regs[reg_number_mem] = *(uint32_t*)&byte_mem[pqp_addr];

            if(reg_number_dst < 8) {
                if(reg_number_mem < 8) {
                    INSINS(MOVRM_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_mem * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[2] = (uint32_t)byte_mem;
                }
                else {
                    INSINS(MOVRM_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_mem - 8) * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[3] = (uint32_t)byte_mem;
                }
            }
            else {
                if(reg_number_mem < 8) {
                    INSINS(MOVRM_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_mem * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[3] = (uint32_t)byte_mem;
                }
                else {
                    INSINS(MOVRM_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_mem - 8) * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[3] = (uint32_t)byte_mem;
                }
            }

            break;
        }

        case 0x03: {
            const uint8_t reg_number_mem = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;
            const uint8_t pqp_addr = regs[reg_number_mem];

            *(uint32_t*)&byte_mem[pqp_addr] = regs[reg_number_src];

            output.cursor += sprintf(
                output.cursor,
                "MOV_MEM[0x%02X,0x%02X,0x%02X,0x%02X]=R%d=[0x%02X,0x%02X,0x%02X,0x%02X]\n",
                pqp_addr,
                pqp_addr + 1,
                pqp_addr + 2,
                pqp_addr + 3,
                reg_number_src,
                byte_mem[pqp_addr],
                byte_mem[pqp_addr + 1],
                byte_mem[pqp_addr + 2],
                byte_mem[pqp_addr + 3]
            );

            if(reg_number_mem < 8) {
                if(reg_number_src < 8) {
                    INSINS(MOVMR_1);

                    fa_bytes_cursor[1] += reg_number_mem + (reg_number_src * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[2] = (uint32_t)byte_mem;
                }
                else {
                    INSINS(MOVMR_3);

                    fa_bytes_cursor[2] += reg_number_mem + ((reg_number_src - 8) * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[3] = (uint32_t)byte_mem;
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(MOVMR_2);

                    fa_bytes_cursor[2] += (reg_number_mem - 8) + (reg_number_src * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[3] = (uint32_t)byte_mem;
                }
                else {
                    INSINS(MOVMR_4);

                    fa_bytes_cursor[2] += (reg_number_mem - 8) + ((reg_number_src - 8) * 0x08);
                    *(uint32_t*)&fa_bytes_cursor[3] = (uint32_t)byte_mem;
                }
            }

            break;
        }

        case 0x04: {
            const uint8_t reg_number_a = ins_bytes[1] >> 4;
            const uint8_t reg_number_b = ins_bytes[1] & 0x0F;

            if(regs[reg_number_a] == regs[reg_number_b]) {
                flags[0] = false;
                flags[1] = false;
                flags[2] = true;
            }
            else if(regs[reg_number_a] > regs[reg_number_b]) {
                flags[0] = true;
                flags[1] = false;
                flags[2] = false;
            }
            else {
                flags[0] = false;
                flags[1] = true;
                flags[2] = false;
            }
            
            output.cursor += sprintf(
                output.cursor,
                "CMP_R%d<=>R%d(G=%d,L=%d,E=%d)\n",
                reg_number_a,
                reg_number_b,
                flags[0],
                flags[1],
                flags[2]
            );

            if(reg_number_a < 8) {
                if(reg_number_b < 8) {
                    INSINS(CMP_1);

                    fa_bytes_cursor[1] += reg_number_a + (reg_number_b * 0x08);
                }
                else {
                    INSINS(CMP_3);

                    fa_bytes_cursor[2] += reg_number_a + ((reg_number_b - 8) * 0x08);
                }
            }
            else {
                if(reg_number_b < 8) {
                    INSINS(CMP_2);

                    fa_bytes_cursor[2] += (reg_number_a - 8) + (reg_number_b * 0x08);
                }
                else {
                    INSINS(CMP_4);

                    fa_bytes_cursor[2] += (reg_number_a - 8) + ((reg_number_b - 8) * 0x08);
                }
            }

            break;
        }

        case 0x05: {
            const int16_t addr = *(int16_t*)&ins_bytes[2];

            addPCs(addr);

            output.cursor += sprintf(
                output.cursor,
                "JMP_0x%04X\n",
                pc + 4
            );

            INSINS(JMP_1);
            
            *(int32_t*)&fa_bytes_cursor[1] = (addr + 4) * 4 - 0x0E;

            break;
        }

        case 0x06: {
            const int16_t addr = *(int16_t*)&ins_bytes[2];

            output.cursor += sprintf(
                output.cursor,
                "JG_0x%04X\n",
                pc + addr + 4
            );

            if(flags[0]) {
                addPCs(addr);
            }

            INSINS(JG_1);
            *(int32_t*)&fa_bytes_cursor[2] = (addr + 4) * 4 - 0x0F;

            break;
        }

        case 0x07: {
            const int16_t addr = *(int16_t*)&ins_bytes[2];

            output.cursor += sprintf(
                output.cursor,
                "JL_0x%04X\n",
                (pc + addr + 4)
            );

            if(flags[1]) {
                addPCs(addr);
            }

            INSINS(JL_1);
            *(int32_t*)&fa_bytes_cursor[2] = (addr + 4) * 4 - 0x0F;

            break;
        }

        case 0x08: {
            const int16_t addr = *(int16_t*)&ins_bytes[2];
            const int32_t x86addr = (addr + 4) * 4 - 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "JE_0x%04hX\n",
                pc + addr + 4
            );

            if(flags[2]) {
                addPCs(addr);
            }

            INSINS(JE_1);

            *(int32_t*)&fa_bytes_cursor[2] = x86addr;

            break;
        }

        case 0x09: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "ADD_R%d+=R%d=0x%08X+0x%08X=0x%08X\n",
                reg_number_dst,
                reg_number_src,
                regs[reg_number_dst],
                regs[reg_number_src],
                regs[reg_number_dst] + regs[reg_number_src]
            );

            regs[reg_number_dst] += regs[reg_number_src];

            if(reg_number_dst < 8) {
                if(reg_number_src < 8) {
                    INSINS(ADD_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_src * 0x08);
                }
                else {
                    INSINS(ADD_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_src - 8) * 0x08);
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(ADD_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_src * 0x08);
                }
                else {
                    INSINS(ADD_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_src - 8) * 0x08);
                }
            }

            break;
        }

        case 0x0A: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "SUB_R%d-=R%d=0x%08X-0x%08X=0x%08X\n",
                reg_number_dst,
                reg_number_src,
                regs[reg_number_dst],
                regs[reg_number_src],
                regs[reg_number_dst] - regs[reg_number_src]
            );

            regs[reg_number_dst] -= regs[reg_number_src];

            if(reg_number_dst < 8) {
                if(reg_number_src < 8) {
                    INSINS(SUB_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_src * 0x08);
                }
                else {
                    INSINS(SUB_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_src - 8) * 0x08);
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(SUB_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_src * 0x08);
                }
                else {
                    INSINS(SUB_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_src - 8) * 0x08);
                }
            }

            break;
        }

        case 0x0B: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "AND_R%d&=R%d=0x%08X&0x%08X=0x%08X\n",
                reg_number_dst,
                reg_number_src,
                regs[reg_number_dst],
                regs[reg_number_src],
                regs[reg_number_dst] & regs[reg_number_src]
            );

            regs[reg_number_dst] &= regs[reg_number_src];

            if(reg_number_dst < 8) {
                if(reg_number_src < 8) {
                    INSINS(AND_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_src * 0x08);
                }
                else {
                    INSINS(AND_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_src - 8) * 0x08);
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(AND_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_src * 0x08);
                }
                else {
                    INSINS(AND_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_src - 8) * 0x08);
                }
            }

            break;
        }

        case 0x0C: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "OR_R%d|=R%d=0x%08X|0x%08X=0x%08X\n",
                reg_number_dst,
                reg_number_src,
                regs[reg_number_dst],
                regs[reg_number_src],
                regs[reg_number_dst] | regs[reg_number_src]
            );

            regs[reg_number_dst] |= regs[reg_number_src];

            if(reg_number_dst < 8) {
                if(reg_number_src < 8) {
                    INSINS(OR_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_src * 0x08);
                }
                else {
                    INSINS(OR_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_src - 8) * 0x08);
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(OR_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_src * 0x08);
                }
                else {
                    INSINS(OR_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_src - 8) * 0x08);
                }
            }

            break;
        }

        case 0x0D: {
            const uint8_t reg_number_dst = ins_bytes[1] >> 4;
            const uint8_t reg_number_src = ins_bytes[1] & 0x0F;
            
            output.cursor += sprintf(
                output.cursor,
                "XOR_R%d^=R%d=0x%08X^0x%08X=0x%08X\n",
                reg_number_dst,
                reg_number_src,
                regs[reg_number_dst],
                regs[reg_number_src],
                regs[reg_number_dst] ^ regs[reg_number_src]
            );

            regs[reg_number_dst] ^= regs[reg_number_src];

            if(reg_number_dst < 8) {
                if(reg_number_src < 8) {
                    INSINS(XOR_1);

                    fa_bytes_cursor[1] += reg_number_dst + (reg_number_src * 0x08);
                }
                else {
                    INSINS(XOR_3);

                    fa_bytes_cursor[2] += reg_number_dst + ((reg_number_src - 8) * 0x08);
                }
            }
            else {
                if(reg_number_src < 8) {
                    INSINS(XOR_2);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + (reg_number_src * 0x08);
                }
                else {
                    INSINS(XOR_4);

                    fa_bytes_cursor[2] += (reg_number_dst - 8) + ((reg_number_src - 8) * 0x08);
                }
            }

            break;
        }

        case 0x0E: {
            const uint8_t reg_number_a = ins_bytes[1] >> 4;
            const uint8_t shift = ins_bytes[3] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "SAL_R%d<<=%d=0x%08X<<%d=0x%08X\n",
                reg_number_a,
                shift,
                regs[reg_number_a],
                shift,
                regs[reg_number_a] << shift
            );

            regs[reg_number_a] <<= shift;

            if(reg_number_a < 8) {
                INSINS(SAL_1);

                fa_bytes_cursor[1] += reg_number_a;
                fa_bytes_cursor[2] =  shift;
            }
            else {
                INSINS(SAL_2);
                
                fa_bytes_cursor[2] += reg_number_a - 8;
                fa_bytes_cursor[3] =  shift;
            }

            break;
        }

        case 0x0F: {
            const uint8_t reg_number_a = ins_bytes[1] >> 4;
            const uint8_t shift = ins_bytes[3] & 0x0F;

            output.cursor += sprintf(
                output.cursor,
                "SAR_R%d>>=%d=0x%08X>>%d=0x%08X\n",
                reg_number_a,
                shift,
                regs[reg_number_a],
                shift,
                regs[reg_number_a] >> shift
            );

            regs[reg_number_a] >>= shift;

            if(reg_number_a < 8) {
                INSINS(SAR_1);

                fa_bytes_cursor[1] += reg_number_a;
                fa_bytes_cursor[2] =  shift;
            }
            else {
                INSINS(SAR_2);
                
                fa_bytes_cursor[2] += reg_number_a - 8;
                fa_bytes_cursor[3] =  shift;
            }

            break;
        }
    }
    
    instruction->exec = fa_bytes_cursor - 9;
    instruction->was_translated = true;
    incPCs();
}

void jitting() {
    asm(
        ".intel_syntax noprefix\n"
        "fclex\nfinit\n"
        "pxor xmm3, xmm3\n"
        "pxor xmm2, xmm2\n"
        "pxor xmm1, xmm1\n"
        "pxor xmm4, xmm4\n"
        ".att_syntax"
        : : : "xmm1", "xmm2", "xmm3", "xmm4"
    );


    while(pc <= 252) {
        current = &control[control_pc];

        if(current->was_translated) {
            coming_from_jit = true;
            asm("int3\n");
            continue;
        }

        interpretTranslate(current, word_mem[control_pc]);
    }
}

void switchMode(int sig, siginfo_t *info, void *ucontext) {
    handler_ctx = (ucontext_t*)ucontext;

    if(coming_from_jit) {
        coming_from_jit = false;

        memcpy(&jit_ctx, handler_ctx, sizeof(ucontext_t));

        handler_ctx->uc_mcontext.gregs[REG_RAX] = regs[0];
        handler_ctx->uc_mcontext.gregs[REG_RCX] = regs[1];
        handler_ctx->uc_mcontext.gregs[REG_RDX] = regs[2];
        handler_ctx->uc_mcontext.gregs[REG_RBX] = regs[3];
        handler_ctx->uc_mcontext.gregs[REG_RSP] = regs[4];
        handler_ctx->uc_mcontext.gregs[REG_RBP] = regs[5];
        handler_ctx->uc_mcontext.gregs[REG_RSI] = regs[6];
        handler_ctx->uc_mcontext.gregs[REG_RDI] = regs[7];
        handler_ctx->uc_mcontext.gregs[REG_R8]  = regs[8];
        handler_ctx->uc_mcontext.gregs[REG_R9]  = regs[9];
        handler_ctx->uc_mcontext.gregs[REG_R10] = regs[10];
        handler_ctx->uc_mcontext.gregs[REG_R11] = regs[11];
        handler_ctx->uc_mcontext.gregs[REG_R12] = regs[12];
        handler_ctx->uc_mcontext.gregs[REG_R13] = regs[13];
        handler_ctx->uc_mcontext.gregs[REG_R14] = regs[14];
        handler_ctx->uc_mcontext.gregs[REG_R15] = regs[15];

        for(uint8_t i = 0; i < 4; i++) {
            memset(&handler_ctx->uc_mcontext.fpregs->_xmm[i], 0, 16);
        }

        handler_ctx->uc_mcontext.gregs[REG_RIP] = (uintptr_t)current->exec;
    }
    else {
        regs[0]  = handler_ctx->uc_mcontext.gregs[REG_RAX];
        regs[1]  = handler_ctx->uc_mcontext.gregs[REG_RCX];
        regs[2]  = handler_ctx->uc_mcontext.gregs[REG_RDX];
        regs[3]  = handler_ctx->uc_mcontext.gregs[REG_RBX];
        regs[4]  = handler_ctx->uc_mcontext.gregs[REG_RSP];
        regs[5]  = handler_ctx->uc_mcontext.gregs[REG_RBP];
        regs[6]  = handler_ctx->uc_mcontext.gregs[REG_RSI];
        regs[7]  = handler_ctx->uc_mcontext.gregs[REG_RDI];
        regs[8]  = handler_ctx->uc_mcontext.gregs[REG_R8];
        regs[9]  = handler_ctx->uc_mcontext.gregs[REG_R9];
        regs[10] = handler_ctx->uc_mcontext.gregs[REG_R10];
        regs[11] = handler_ctx->uc_mcontext.gregs[REG_R11];
        regs[12] = handler_ctx->uc_mcontext.gregs[REG_R12];
        regs[13] = handler_ctx->uc_mcontext.gregs[REG_R13];
        regs[14] = handler_ctx->uc_mcontext.gregs[REG_R14];
        regs[15] = handler_ctx->uc_mcontext.gregs[REG_R15];
        
        changePCs((handler_ctx->uc_mcontext.gregs[REG_RIP] - (uint64_t)fa_bytes - 1) / 4);

        handler_ctx->uc_mcontext.gregs[REG_RAX] = jit_ctx.uc_mcontext.gregs[REG_RAX];
        handler_ctx->uc_mcontext.gregs[REG_RCX] = jit_ctx.uc_mcontext.gregs[REG_RCX];
        handler_ctx->uc_mcontext.gregs[REG_RDX] = jit_ctx.uc_mcontext.gregs[REG_RDX];
        handler_ctx->uc_mcontext.gregs[REG_RBX] = jit_ctx.uc_mcontext.gregs[REG_RBX];
        handler_ctx->uc_mcontext.gregs[REG_RSP] = jit_ctx.uc_mcontext.gregs[REG_RSP];
        handler_ctx->uc_mcontext.gregs[REG_RBP] = jit_ctx.uc_mcontext.gregs[REG_RBP];
        handler_ctx->uc_mcontext.gregs[REG_RSI] = jit_ctx.uc_mcontext.gregs[REG_RSI];
        handler_ctx->uc_mcontext.gregs[REG_RDI] = jit_ctx.uc_mcontext.gregs[REG_RDI];
        handler_ctx->uc_mcontext.gregs[REG_R8]  = jit_ctx.uc_mcontext.gregs[REG_R8];
        handler_ctx->uc_mcontext.gregs[REG_R9]  = jit_ctx.uc_mcontext.gregs[REG_R9];
        handler_ctx->uc_mcontext.gregs[REG_R10] = jit_ctx.uc_mcontext.gregs[REG_R10];
        handler_ctx->uc_mcontext.gregs[REG_R11] = jit_ctx.uc_mcontext.gregs[REG_R11];
        handler_ctx->uc_mcontext.gregs[REG_R12] = jit_ctx.uc_mcontext.gregs[REG_R12];
        handler_ctx->uc_mcontext.gregs[REG_R13] = jit_ctx.uc_mcontext.gregs[REG_R13];
        handler_ctx->uc_mcontext.gregs[REG_R14] = jit_ctx.uc_mcontext.gregs[REG_R14];
        handler_ctx->uc_mcontext.gregs[REG_R15] = jit_ctx.uc_mcontext.gregs[REG_R15];

        const struct _libc_fpstate* fp = handler_ctx->uc_mcontext.fpregs;

        for(uint8_t i = 0; i < 4; i++) {
            const uint32_t* words = (const uint32_t*)&fp->_xmm[i + 1];

            for(uint8_t j = 0; j < 4; j++) {
                stats[4 * i + j] += words[j];
            }
        }
        
        handler_ctx->uc_mcontext.gregs[REG_RIP] = jit_ctx.uc_mcontext.gregs[REG_RIP];
    }
}

void badEnding(int sig, siginfo_t *info, void *ucontext) {
    changePCs((((ucontext_t*)ucontext)->uc_mcontext.gregs[REG_RIP] - (uint64_t)fa_bytes) / 4);
//(addr + 4) * 4 - 0x0E;
    regs[0]  = handler_ctx->uc_mcontext.gregs[REG_RAX];
    regs[1]  = handler_ctx->uc_mcontext.gregs[REG_RCX];
    regs[2]  = handler_ctx->uc_mcontext.gregs[REG_RDX];
    regs[3]  = handler_ctx->uc_mcontext.gregs[REG_RBX];
    regs[4]  = handler_ctx->uc_mcontext.gregs[REG_RSP];
    regs[5]  = handler_ctx->uc_mcontext.gregs[REG_RBP];
    regs[6]  = handler_ctx->uc_mcontext.gregs[REG_RSI];
    regs[7]  = handler_ctx->uc_mcontext.gregs[REG_RDI];
    regs[8]  = handler_ctx->uc_mcontext.gregs[REG_R8];
    regs[9]  = handler_ctx->uc_mcontext.gregs[REG_R9];
    regs[10] = handler_ctx->uc_mcontext.gregs[REG_R10];
    regs[11] = handler_ctx->uc_mcontext.gregs[REG_R11];
    regs[12] = handler_ctx->uc_mcontext.gregs[REG_R12];
    regs[13] = handler_ctx->uc_mcontext.gregs[REG_R13];
    regs[14] = handler_ctx->uc_mcontext.gregs[REG_R14];
    regs[15] = handler_ctx->uc_mcontext.gregs[REG_R15];

    handler_ctx->uc_mcontext.gregs[REG_RAX] = jit_ctx.uc_mcontext.gregs[REG_RAX];
    handler_ctx->uc_mcontext.gregs[REG_RCX] = jit_ctx.uc_mcontext.gregs[REG_RCX];
    handler_ctx->uc_mcontext.gregs[REG_RDX] = jit_ctx.uc_mcontext.gregs[REG_RDX];
    handler_ctx->uc_mcontext.gregs[REG_RBX] = jit_ctx.uc_mcontext.gregs[REG_RBX];
    handler_ctx->uc_mcontext.gregs[REG_RSP] = jit_ctx.uc_mcontext.gregs[REG_RSP];
    handler_ctx->uc_mcontext.gregs[REG_RBP] = jit_ctx.uc_mcontext.gregs[REG_RBP];
    handler_ctx->uc_mcontext.gregs[REG_RSI] = jit_ctx.uc_mcontext.gregs[REG_RSI];
    handler_ctx->uc_mcontext.gregs[REG_RDI] = jit_ctx.uc_mcontext.gregs[REG_RDI];
    handler_ctx->uc_mcontext.gregs[REG_R8]  = jit_ctx.uc_mcontext.gregs[REG_R8];
    handler_ctx->uc_mcontext.gregs[REG_R9]  = jit_ctx.uc_mcontext.gregs[REG_R9];
    handler_ctx->uc_mcontext.gregs[REG_R10] = jit_ctx.uc_mcontext.gregs[REG_R10];
    handler_ctx->uc_mcontext.gregs[REG_R11] = jit_ctx.uc_mcontext.gregs[REG_R11];
    handler_ctx->uc_mcontext.gregs[REG_R12] = jit_ctx.uc_mcontext.gregs[REG_R12];
    handler_ctx->uc_mcontext.gregs[REG_R13] = jit_ctx.uc_mcontext.gregs[REG_R13];
    handler_ctx->uc_mcontext.gregs[REG_R14] = jit_ctx.uc_mcontext.gregs[REG_R14];
    handler_ctx->uc_mcontext.gregs[REG_R15] = jit_ctx.uc_mcontext.gregs[REG_R15];

    const struct _libc_fpstate* fp = handler_ctx->uc_mcontext.fpregs;

    for(uint8_t i = 0; i < 4; i++) {
        const uint32_t* words = (const uint32_t*)&fp->_xmm[i + 1];

        for(uint8_t j = 0; j < 4; j++) {
            stats[4 * i + j] += words[j];
        }
    }

    handler_ctx->uc_mcontext.gregs[REG_RIP] = jit_ctx.uc_mcontext.gregs[REG_RIP];
}

void writeEnd() {
    output.cursor += sprintf(
        output.cursor,
        "0x%04X->EXIT\n"
        "[00:%d,01:%d,02:%d,03:%d,04:%d,05:%d,06:%d,07:%d,08:%d,09:%d,0A:%d,0B:%d,0C:%d,0D:%d,0E:%d,0F:%d]\n"
        "[R0=0x%08X,R1=0x%08X,R2=0x%08X,R3=0x%08X,R4=0x%08X,R5=0x%08X,R6=0x%08X,R7=0x%08X,"
        "R8=0x%08X,R9=0x%08X,R10=0x%08X,R11=0x%08X,R12=0x%08X,R13=0x%08X,R14=0x%08X,R15=0x%08X]\n",
        pc,
        stats[0], stats[1], stats[2], stats[3], stats[4], stats[5], stats[6], stats[7],
        stats[8], stats[9], stats[10], stats[11], stats[12] / 2 + 1, stats[13], stats[14] / 2 + 2, stats[15] / 2 + 1,
        regs[0], regs[1], regs[2], regs[3], regs[4], regs[5], regs[6], regs[7],
        regs[8], regs[9], regs[10], regs[11], regs[12], regs[13], regs[14], regs[15]
    ); 
}

void setup() {
    alt_stack.ss_sp = malloc(SIGSTKSZ);
    alt_stack.ss_size = SIGSTKSZ;
    alt_stack.ss_flags = 0;
    sigaltstack(&alt_stack, NULL);

    sa_jitting.sa_flags = SA_SIGINFO | SA_ONSTACK;
    sa_jitting.sa_sigaction = switchMode;
    sigaction(SIGTRAP, &sa_jitting, NULL);

    sa_ending.sa_flags = SA_ONSTACK | SA_SIGINFO;
    sa_ending.sa_sigaction = badEnding;
    sigaction(SIGSEGV, &sa_ending, NULL);

    input.cursor = input.buffer;
    output.cursor = output.buffer;
    fread(input.buffer, 1, BUFFER_LEN, input.file);
    
    fa_bytes = (uint8_t*)mmap(
        NULL, PAGE_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0
    );
    memset(fa_bytes, INT_3, PAGE_SIZE);
    fa_bytes_cursor = fa_bytes;
    fa_bytes_end = &fa_bytes[PAGE_SIZE - 1];

    byte_mem = (uint8_t*)mmap(
        (void*)0x10000000, 256, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );
    memset(byte_mem, 0, 256);
    word_mem = (uint32_t*) byte_mem;

    stats = (uint32_t*)mmap(
        (void*)0x10001000, 64, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );
    memset(stats, 0, 64);

    XMM_INC_0 = (uint32_t*) mmap(
        (void*)0x10002000, 16, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );
    XMM_INC_0[0] = 1;
    XMM_INC_0[1] = 0;
    XMM_INC_0[2] = 0;
    XMM_INC_0[3] = 0;

    XMM_INC_1 = (uint32_t*) mmap(
        (void*)0x10003000, 16, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );
    XMM_INC_1[0] = 0;
    XMM_INC_1[1] = 1;
    XMM_INC_1[2] = 0;
    XMM_INC_1[3] = 0;

    XMM_INC_2 = (uint32_t*) mmap(
        (void*)0x10004000, 16, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );
    XMM_INC_2[0] = 0;
    XMM_INC_2[1] = 0;
    XMM_INC_2[2] = 1;
    XMM_INC_2[3] = 0;

    XMM_INC_3 = (uint32_t*) mmap(
        (void*)0x10005000, 16, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );
    XMM_INC_3[0] = 0;
    XMM_INC_3[1] = 0;
    XMM_INC_3[2] = 0;
    XMM_INC_3[3] = 1;

    *(uint32_t*)&SAR_1[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&SAR_2[5] = (uint32_t)XMM_INC_3;

    *(uint32_t*)&SAL_1[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&SAL_2[5] = (uint32_t)XMM_INC_2;

    *(uint32_t*)&XOR_1[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&XOR_2[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&XOR_3[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&XOR_4[5] = (uint32_t)XMM_INC_1;

    *(uint32_t*)&OR_1[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&OR_2[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&OR_3[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&OR_4[5] = (uint32_t)XMM_INC_0;

    *(uint32_t*)&AND_1[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&AND_2[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&AND_3[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&AND_4[5] = (uint32_t)XMM_INC_3;
    
    *(uint32_t*)&SUB_1[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&SUB_2[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&SUB_3[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&SUB_4[5] = (uint32_t)XMM_INC_2;

    *(uint32_t*)&ADD_1[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&ADD_2[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&ADD_3[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&ADD_4[5] = (uint32_t)XMM_INC_1;

    *(uint32_t*)&JE_1[5] = (uint32_t)XMM_INC_0;

    *(uint32_t*)&JL_1[5] = (uint32_t)XMM_INC_3;

    *(uint32_t*)&JG_1[5] = (uint32_t)XMM_INC_2;

    *(uint32_t*)&JMP_1[5] = (uint32_t)XMM_INC_1;

    *(uint32_t*)&CMP_1[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&CMP_2[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&CMP_3[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&CMP_4[5] = (uint32_t)XMM_INC_0;

    *(uint32_t*)&MOVMR_1[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&MOVMR_2[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&MOVMR_3[5] = (uint32_t)XMM_INC_3;
    *(uint32_t*)&MOVMR_4[5] = (uint32_t)XMM_INC_3;

    *(uint32_t*)&MOVRM_1[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&MOVRM_2[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&MOVRM_3[5] = (uint32_t)XMM_INC_2;
    *(uint32_t*)&MOVRM_4[5] = (uint32_t)XMM_INC_2;

    *(uint32_t*)&MOVRR_1[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&MOVRR_2[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&MOVRR_3[5] = (uint32_t)XMM_INC_1;
    *(uint32_t*)&MOVRR_4[5] = (uint32_t)XMM_INC_1;

    *(uint32_t*)&MOVRI_1[5] = (uint32_t)XMM_INC_0;
    *(uint32_t*)&MOVRI_2[5] = (uint32_t)XMM_INC_0;
}

void sayGoodbye() {
    fwrite(output.buffer, 1, (uint64_t)output.cursor - (uint64_t)output.buffer, output.file);

    munmap(fa_bytes, PAGE_SIZE);
    munmap(byte_mem, 256);
    munmap(stats, 64);
    munmap(XMM_INC_0, 16);
    munmap(XMM_INC_1, 16);
    munmap(XMM_INC_2, 16);
    munmap(XMM_INC_3, 16);
    free(alt_stack.ss_sp);
    
    fclose(input.file);
    fclose(output.file);
}


int main(int argc, char** argv) {
    input.file = fopen(argv[1], READ_MODE);
    output.file = fopen(argv[2], WRITE_MODE);

    setup();
    loadMem();
    jitting();
    writeEnd();
    sayGoodbye();

    return 0;
}