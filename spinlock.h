#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"
struct spinlock {
    uint locked; // 状态
    char *name;  // 名字
    struct cpu *cpu;
};



#endif