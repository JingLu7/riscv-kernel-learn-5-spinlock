#include "types.h"

// r_mstatus
// w_mstatus
// w_mepc
// w_satp
// w_medeleg
// w_mideleg
static inline unsigned long r_mstatus() {
  unsigned long x;
  asm volatile("csrr %0, mstatus" : "=r" (x));
  return x;
}

static inline void w_mstatus(unsigned long x) {
  asm volatile("csrw mstatus, %0" : : "r" (x));
}


static inline void w_mepc(unsigned long x) {
  asm volatile("csrw mepc, %0" : : "r" (x));
}

static inline void w_mideleg(unsigned long x) {
  asm volatile("csrw mideleg, %0" : : "r" (x));
}

static inline void w_medeleg(unsigned long x) {
  asm volatile("csrw medeleg, %0" : : "r" (x));
}

static inline void w_satp(unsigned long x) {
  asm volatile("csrw satp, %0" : : "r" (x));
}

static inline unsigned long r_satp() {
  unsigned long x;
  asm volatile("csrr %0, satp" : "=r" (x));
  return x;
}

static inline void w_pmpcfg0(unsigned long x) {
  asm volatile("csrw pmpcfg0, %0" : : "r" (x));
}

static inline void w_pmpaddr0(unsigned long x) {
  asm volatile("csrw pmpaddr0, %0" : : "r" (x));
}

//r_sstatus
//w_sstatus
static inline uint64 r_sstatus() {
    uint64 x;
    asm volatile("csrr %0, sstatus" : "=r" (x));
    return x;
}

static inline void w_sstatus(uint64 x) {
    asm volatile("csrw sstatus, %0" : : "r" (x));
}

//r_scause
//w_stvec
//r_time
//w_stimecmp
static inline uint64 r_scause() {
    uint64 x;
    asm volatile("csrr %0, scause" : "=r" (x));
    return x;
}

static inline void w_stvec(uint64 x) {
    asm volatile("csrw stvec, %0" : : "r" (x));
}

static inline uint64 r_time() {
    uint64 x;
    asm volatile("csrr %0, time" : "=r" (x) : : "memory");
    return x;
}
static inline void w_stimecmp(uint64 x) {
    // stimecmp 的 CSR 地址通常是 0x14D
    asm volatile("csrw 0x14D, %0" : : "r" (x));
}

//r_mie
//w_mie
//r_menvcfg
//w_menvcfg
//r_mcounteren
//w_mcounteren
//w_stimecmp
static inline uint64 r_mie() {
    uint64 x;
    asm volatile("csrr %0, mie" : "=r" (x));
    return x;
}

static inline void w_mie(uint64 x) {
    asm volatile("csrw mie, %0" : : "r" (x));
}

static inline uint64 r_menvcfg() {
    uint64 x;
    asm volatile("csrr %0, 0x30A" : "=r" (x));
    return x;
}

static inline void w_menvcfg(uint64 x) {
    asm volatile("csrw 0x30A, %0" : : "r" (x));
}

static inline uint64 r_mcounteren() {
    uint64 x;
    asm volatile("csrr %0, mcounteren" : "=r" (x));
    return x;
}

static inline void w_mcounteren(uint64 x) {
    asm volatile("csrw mcounteren, %0" : : "r" (x));
}


//r_sie
//w_sie
static inline uint64 r_sie() {
    uint64 x;
    asm volatile("csrr %0, sie" : "=r" (x));
    return x;
}

static inline void w_sie(uint64 x) {
    asm volatile("csrw sie, %0" : : "r" (x));
}

//r_tp
//intr_get
//intr_off
//intr_on
static inline uint64 r_tp() {
  uint64 x;
  asm volatile("mv %0, tp" : "=r" (x) );
  return x;
}

#define SSTATUS_SIE (1L<<1)
// 开中断
static inline void
intr_on()
{
  w_sstatus(r_sstatus() | SSTATUS_SIE);
}

// 关中断
static inline void
intr_off()
{
  w_sstatus(r_sstatus() & ~SSTATUS_SIE);
}

// 获取sstatus第一位
static inline int
intr_get()
{
  uint64 x = r_sstatus();
  return (x & SSTATUS_SIE) != 0;
}

//w_sepc
//r_sepc
static inline void 
w_sepc(uint64 x)
{
  asm volatile("csrw sepc, %0" : : "r" (x));
}

static inline uint64
r_sepc()
{
  uint64 x;
  asm volatile("csrr %0, sepc" : "=r" (x) );
  return x;
}