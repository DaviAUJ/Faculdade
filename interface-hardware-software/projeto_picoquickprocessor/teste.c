#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <ucontext.h>
#include <signal.h>
#include <stdlib.h>

uint32_t* a;
uint8_t* bytes;


int main() {
    bytes = mmap(0, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    mprotect(bytes, 4096, PROT_WRITE | PROT_EXEC);
    
    a = (uint32_t*)mmap(
        (void*)0x10000100, 4,  PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED_NOREPLACE, -1, 0
    );

    printf("%d", a);
}

// uint8_t *bytes;
// void (*badFunction)(); 
// ucontext_t before_bad_ctx;
// ucontext_t *latest_ctx;
// ucontext_t nnsei;
// bool jump_bad_function = false;

// void sigill_handler(int sig, siginfo_t *info, void *ucontext) {
//     printf("sigill\n");
//     latest_ctx = (ucontext_t*) ucontext;
//     jump_bad_function = true;
    
//     setcontext(&before_bad_ctx);
// }

// void supostamentenormal() {
//     printf("Se piscar já era\n");
    
//     getcontext(&nnsei);

//     nnsei.uc_mcontext.gregs[REG_RIP] = (uint64_t)bytes;
//     getcontext(&before_bad_ctx);

    
//     if(!jump_bad_function) {
//         setcontext(&nnsei);
//     }
    
//     printf("Pulou\n");
    
//     jump_bad_function = false;
    
//     ucontext_t now;
//     getcontext(&now);
    
//     printf("Aqui deu problema: %016llX - rbp: %016llX\n", latest_ctx->uc_mcontext.gregs[REG_RIP], latest_ctx->uc_mcontext.gregs[REG_RBP]);
//     printf("Estamos aqui agora: %016llX - rbp: %016llX\n", now.uc_mcontext.gregs[REG_RIP], now.uc_mcontext.gregs[REG_RBP]);
// }

// int main() {
//     bytes = mmap(0, 4096, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
//     mprotect(bytes, 4096, PROT_WRITE | PROT_EXEC);
//     badFunction = (void(*)()) bytes;
    
//     stack_t alt_stack;
//     alt_stack.ss_sp = malloc(SIGSTKSZ);
//     alt_stack.ss_size = SIGSTKSZ;
//     alt_stack.ss_flags = 0;
//     sigaltstack(&alt_stack, NULL);

//     struct sigaction sa = {0};
//     sa.sa_sigaction = sigill_handler;
//     sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
//     sigaction(SIGTRAP, &sa, NULL);


//     // mov ebp, 0
//     bytes[0] = 0xbd;
//     bytes[1] = 0x00;
//     bytes[2] = 0x00;
//     bytes[3] = 0x00;
//     bytes[4] = 0x00;

//     //mov esp, 0
//     bytes[5] = 0xbc;
//     bytes[6] = 0x00;
//     bytes[7] = 0x00;
//     bytes[8] = 0x00;
//     bytes[9] = 0x00;

//     bytes[10] = 0x90;

//     // Interrupção
//     bytes[11] = 0xcc;

//     printf("Ponteiro da badFunction: %016lX\n", (uint64_t)badFunction);
//     printf("Ponteiro da sigill: %016lX\n", (uint64_t)sigill_handler);
//     printf("Ponteiro da supostamentenormal: %016lX\n", (uint64_t)supostamentenormal);
//     supostamentenormal();
//     printf("sai do programa\n");
// }


// uint64_t e[] = { 10, 30, 100 }; 

// const uint64_t a = 10;
// const uint64_t b = 20;
// uint64_t c;
// uint64_t d;

// uint64_t* pa = &a;
// uint64_t* pb = &b;
// uint64_t* pc = &c;

// void asm_var() {
//         asm("mov %0, %%rdi" : : "r" (*pa) :);
//         asm("mov %0, %%rsi" : : "r" (*pb) :);
//         asm("xor %rdx, %rdx");
//         asm("add %rdi, %rdx");
//         asm("add %rsi, %rdx");
//         asm("mov %%rdx, %0": "=r" (*pc) : :);
//         asm("mov %1, %0" : "=r" (d) : "r" (*pc) :);
// }

// asm(
//     ".intel_syntax noprefix\n"
//     "f_addp:\n"
//     "mov eax, DWORD PTR [rsi]\n"
//     "add DWORD PTR [rdi], eax\n"
//     "ret\n"
//     ".att_syntax"
// );

// int32_t reg[15];
// bool flags[3];
// int32_t mem[64];

// void cmp(const uint8_t reg_number_a, const uint8_t reg_number_b) {
//     if(reg[reg_number_a] == reg[reg_number_b]) {
//         flags[0] = false;
//         flags[1] = false;
//         flags[2] = true;

//         return;
//     }

//     if(reg[reg_number_a] > reg[reg_number_b]) {
//         flags[0] = true;
//         flags[1] = false;
//         flags[2] = false;
        
//         return;
//     }

//     flags[0] = false;
//     flags[1] = true;
//     flags[2] = false;
// }

// void add(int8_t a, int8_t b) {
//     mem[a] += mem[b];
// }

// void addp(uint32_t* a, uint32_t* b) {
//     *a +=
// }

// uint32_t a = 0;

// void printOi() {
//     printf("Opa\n");
// }

// void add(uint32_t a, uint32_t b) {
//     printf("%d + %d = %d\n", a, b, a + b);
// }

// void printEax() {
//     asm(
//         ".intel_syntax noprefix\n"
//         "mov %0, eax\n"
//         ".att_syntax"
//         : [a] "=r" (a) : : "eax"
//     );

//     printf("%d\n", a);
// }

// uint8_t ins_bytes[] = {
//     0x48, 0x83, 0xEC, 0x08, // sub rsp, 8
//     0xBF, 0x0B, 0x00, 0x00, 0x00, // mov edi, 11
//     0xBE, 0x16, 0x00, 0x00, 0x00, // mov esi, 22
//     0x01, 0xF7, // add edi, esi
//     0x89, 0xF8, // mov eax, edi
//     0x90, 0x90, 0x90, 0x90,
//     0x48, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // movabs rdi, 0x0
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00,
//     0xFF, 0xD7, // call rdi
//     0x48, 0x83, 0xc4, 0x8, // add rsp, 8
//     0xC3 // ret
// };

// uint32_t teste = 10;

// asm(
//     ".intel_syntax noprefix\n"
//     "baguga:\n"
//     "add DWORD PTR [rip + teste], 5\n"
//     ".att_syntax"
// );

// void baguga();

