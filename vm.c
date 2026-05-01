#include "config.h"


#define MAXVA (1L << 38)
#define PXMASK 0x1ff
#define PXSHIFT(level) (12 + (9 * (level)))
#define PX(level, va) (((uint64)va) >> PXSHIFT(level) & PXMASK)

#define PTE2PA(pte) (((pte) >> 10) << 12)
#define PA2PTE(pte) (((pte) >> 12) << 10)
#define PTE_V (1L << 0)

#define UART0 0x10000000

void *kalloc(void);
void *memset(void *v, uint n, uint len);


pte_t* walk(pagetable_t pagetable, uint64 va, uint alloc){
    if(va >= MAXVA)
        for(;;);
    
    for(uint level = 2; level > 0; level --){
        pte_t *pte = &pagetable[PX(level, va)];

        if(*pte & PTE_V){
            pagetable = (pagetable_t)PTE2PA(*pte);
        }else{
            if(!alloc || (pagetable = (pagetable_t)kalloc()) == 0)
                return 0;
            
            memset(pagetable, 0, PGSIZE);    
            
            *pte = (PA2PTE((uint64)pagetable)) | PTE_V;

        }
    }

    return &pagetable[PX(0, va)];
}


int mappages(pagetable_t pagetable, uint64 va, uint64 size, uint64 pa, uint perm){
    uint64 a, last;
    pte_t *pte;

    if(size == 0){
        for(;;);
    }

    a = PGROUNDDOWN(va);
    last = PGROUNDDOWN(va + size -1);

    for(;;){
        if((pte = walk(pagetable, a, 1)) == 0)
            return -1;

        if(*pte & PTE_V)
            for(;;);

        *pte = PA2PTE(pa) | perm | PTE_V;
        
        if(a == last)
            break;
        
        a += PGSIZE;
        pa += PGSIZE;
    }
    return 0;
}

pagetable_t kernel_pagetable;

void kvmmap(pagetable_t kpt, uint64 va, uint64 pa, uint64 sz, uint perm){
    if(mappages(kpt, va, sz, pa, perm) != 0)
        for(;;);
}

extern char end[];
extern char etext[];
void kvminit(){
    kernel_pagetable = (pagetable_t) kalloc();
    memset(kernel_pagetable, 0, PGSIZE);

    kvmmap(kernel_pagetable, UART0, UART0, PGSIZE, PTE_R | PTE_W);
    kvmmap(kernel_pagetable, KERNBASE, KERNBASE, (uint64)etext - KERNBASE, PTE_R | PTE_X);
    kvmmap(kernel_pagetable, (uint64)etext, (uint64)etext, (uint64)end - (uint64)etext, PTE_R | PTE_W);
    kvmmap(kernel_pagetable, (uint64)end, (uint64)end, PHYSTOP - (uint64)end, PTE_R | PTE_W);
}


void kvminithart(){
    uint64 _satp = (8L << 60) | ((uint64)kernel_pagetable >> 12);
    asm volatile("csrw satp, %0" : : "r"(_satp));
    asm volatile("sfence.vma zero, zero");
}