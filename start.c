#include "types.h"
#include "riscv.h"

#define MSTATUS_MPP_MASK (3L << 11)
#define MSTATUS_MPP_S (1L << 11)
void main();
void timerinit();

void start(){
    uint64 x = r_mstatus();
    x &= ~MSTATUS_MPP_MASK;
    x |= MSTATUS_MPP_S;
    w_mstatus(x); //0000000a00000800

    w_mepc((uint64)main);
    w_satp(0);

    w_mideleg(0xffff);
    w_medeleg(0xffff);
    
    w_pmpaddr0(0x3fffffffffffffull);
    w_pmpcfg0(0xf);
    timerinit();

    asm volatile("mret");
}

#define MIE_STIE (1L << 5)
void timerinit(){
  w_mie(r_mie() | MIE_STIE);
  
  w_menvcfg(r_menvcfg() | (1L << 63)); 
  
  w_mcounteren(r_mcounteren() | 2);
  
  w_stimecmp(r_time() + 1000000);
}