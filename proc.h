#ifndef PROC_H
#define PROC_H
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
    struct context context;
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

#endif