#include "types.h"
#include "spinlock.h"

struct context {
    uint64 ra;
    uint64 sp;
    uint64 s0;
    uint64 s1;
    uint64 s2;
    uint64 s3;
    uint64 s4;
    uint64 s5;
    uint64 s6;
    uint64 s7;
    uint64 s8;
    uint64 s9;
    uint64 s10;
    uint64 s11;
};

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct proc {
    struct spinlock lock;
    enum procstate state;
    int pid;
    uint64 kstack;
    pagetable_t pagetable;
    struct context context;
    struct trapframe *trapframe;
};

#define NPROC 4
extern struct proc pcb[NPROC];
extern struct proc *current_proc;

struct cpu {
    struct proc *proc;  
    struct context context;
    int noff; // 嵌套深度
    int intena; // 中断使能状态
};
#define NCPU 1
extern struct cpu cpus[NCPU];


struct trapframe {
    uint64 kernel_stap; // 内核页表
    uint64 kernel_sp;   // 栈
    uint64 kernel_trap; // usertrap
    uint64 epc; // 用户态程序返回
    uint64 kernel_hartid;
    uint64 ra; /* 40*/
    uint64 sp; // 用户栈
    uint64 gp;
    uint64 tp;
    uint64 t0;
    uint64 t1;
    uint64 t2;
    uint64 s0;
    uint64 s1;
    uint64 a0;
    uint64 a1;
    uint64 a2;
    uint64 a3;
    uint64 a4;
    uint64 a5;
    uint64 a6;
    uint64 a7;
    uint64 s2;
    uint64 s3;
    uint64 s4;
    uint64 s5;
    uint64 s6;
    uint64 s7;
    uint64 s8;
    uint64 s9;
    uint64 s10;
    uint64 s11;
    uint64 t3;
    uint64 t4;
    uint64 t5;
    uint64 t6;
};