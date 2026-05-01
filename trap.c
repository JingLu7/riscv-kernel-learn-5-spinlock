#include "types.h"
#include "riscv.h"
#include "proc.h"


void uart_puts();
void set_next_timer();
void yield();
void uart_puts(char *s);

extern struct proc *current_proc;

void kerneltrap(){
    uint64 scause = r_scause();
    uint64 sepc = r_sepc();
    uint64 sstatus = r_sstatus();
    if (scause == 0x8000000000000005ULL){
        set_next_timer();
        uart_puts(".");
        if(current_proc != 0 && current_proc->state == RUNNING){
            yield();
        }
        w_sepc(sepc);
        w_sstatus(sstatus);
    }
}

