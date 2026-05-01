#include "riscv.h"
#include "spinlock.h"
#include "proc.h"

struct cpu cpus[NCPU];

struct cpu* mycpu(void){
    int id = r_tp();
    return &cpus[id];
}

void initlock(struct spinlock *lk, char *name){
    lk->name = name;
    lk->locked = 0;
    lk->cpu = 0;
}

void push_off(void){
    int old = intr_get();
    intr_off();

    if(mycpu()->noff == 0)
        mycpu()->intena = old;
    mycpu()->noff += 1;
}

void pop_off(void){
    struct cpu *c = mycpu();
    if(intr_get())
        for(;;);
    if(c->noff < 1)
        for(;;);
    
    c->noff -= 1;
    if(c->noff == 0 && c->intena)
        intr_on();
}

int holding(struct spinlock *lk){
    int r;
    r = (lk->locked && lk->cpu == mycpu());
    return r;
}
void acquire(struct spinlock *lk){
    push_off();
    if(holding(lk))
        for(;;);
    while(__sync_lock_test_and_set(&lk->locked, 1) != 0) // 返回locked旧值 赋予新值1 原子操作 进入临界区
        ;

    __sync_synchronize();
    lk->cpu = mycpu();
}

void release(struct spinlock *lk){
    if(!holding(lk))
        for(;;);
    lk->cpu = 0;

    __sync_synchronize();
    __sync_lock_release(&lk->locked);
    pop_off();
}
