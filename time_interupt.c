#include "types.h"
#include "riscv.h"
// 定义时钟频率（QEMU 模拟器通常是 10,000,000，即 10MHz）
// 如果你想 1 秒触发 10 次（即 100ms 一次），间隔就是 1,000,000
#define CLINT_TIMEBASE_FREQ 10000000
#define INTERVAL (CLINT_TIMEBASE_FREQ / 10)


void set_next_timer() {
    uint64 next = r_time() + INTERVAL;
    w_stimecmp(next);
}


extern char kernelvec[];
void trapinit(){
    w_stvec((uint64)kernelvec);
    intr_on();
} 