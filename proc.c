#include "proc.h"
#include "types.h"
#include "spinlock.h"
#include "riscv.h"

struct proc pcb[NPROC];
struct proc *current_proc = 0;
extern struct cpu cpus[NCPU];

void swtch(struct context *old, struct context *new);
void *kalloc();
void uart_puts();
struct cpu* mycpu(void);


void initlock(struct spinlock *lk, char *name);
void acquire(struct spinlock *lk);
void release(struct spinlock *lk);

void proc_init(){
    for(int i = 0; i < NPROC; i++){
        initlock(&pcb[i].lock, "proc");
        pcb[i].state = UNUSED;
    }
}

void task_init(int i, void (*entry)()){
    struct proc *p = &pcb[i];
    p->state = RUNNABLE;
    p->pid = i;
    p->kstack = (uint64)kalloc();
    p->context.sp = p->kstack + 4096;
    p->context.ra = (uint64)entry;
}

void scheduler(){
    struct cpu *c = mycpu();
    for(;;){
        intr_on();
        for(int i = 0; i < NPROC; i++){
            struct proc *p = &pcb[i];
            acquire(&p->lock);
            if(p->state == RUNNABLE){
                
                p->state = RUNNING;
                c->proc = p;
                current_proc = p;
                swtch(&c->context, &p->context);
                c->proc = 0;      
            }
            release(&p->lock);
        }
    }
}

void sched(){
    struct proc *p = mycpu()->proc;
    if(mycpu()->noff != 1)
        for(;;);
    swtch(&p->context, &mycpu()->context);    
}

void yield(){
    struct proc *p = mycpu()->proc;
    acquire(&p->lock);
    p->state = RUNNABLE;
    sched();
    release(&p->lock);
}

void task_a() {
    release(&pcb[0].lock);
    // intr_on();
    while(1){
        uart_puts("Hello from Task A!\n");
        for(int i=0; i<10000000; i++); 
    }
}

void task_b() {
    release(&pcb[1].lock);
    intr_on();
    while(1){
        uart_puts("Hello from Task B!\n");
        for(int i=0; i<10000000; i++);
    }
} 