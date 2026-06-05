#include "types.h"
#include "riscv.h"
#include "proc.h"


void uart_puts();
void set_next_timer();
void yield();
void uart_puts(char *s);
void kernelvec();
void *myproc();
void syscall();


extern struct proc *current_proc;
extern char trampoline[], uservec[];



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

void usertrap(){
    w_stvec((uint64)kernelvec);

    struct proc *p = myproc();
    p->trapframe->epc = r_sepc();
    if(r_scause == 8){
        p->trapframe->epc += 4;
        intr_on();
        syscall();
    }
}