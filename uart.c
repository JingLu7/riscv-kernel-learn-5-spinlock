#include "spinlock.h"
#define UART 0x10000000
#define LSR (UART + 5)

void uart_putc(char c) {
    volatile unsigned char *lsr = (unsigned char *)LSR;
    volatile unsigned char *thr = (unsigned char *)UART;

    while ((*lsr & 0x20) == 0) ;

    *thr = (unsigned char)c; //把字符发给0x10000000内存地址
}

void initlock(struct spinlock *lk, char *name);
void acquire(struct spinlock *lk);
void release(struct spinlock *lk);
struct spinlock uart_lock;

void uart_init(){
    initlock(&uart_lock, "uart");
}

void uart_puts(char *s) {
    acquire(&uart_lock);
    while(*s){
        uart_putc(*s++);
    }
    release(&uart_lock);
}