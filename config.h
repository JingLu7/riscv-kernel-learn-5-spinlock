// 类型定义
typedef unsigned int uint;
typedef unsigned long uint64;
typedef uint64 pte_t;
typedef uint64* pagetable_t;

// 常量
#define KERNBASE 0x80000000
#define PHYSTOP (KERNBASE + 128*1024*1024)
#define PGSIZE 4096

// 工具宏
#define PGROUNDUP(sz) (((sz) + PGSIZE - 1) & ~(PGSIZE - 1))
#define PGROUNDDOWN(sz) ((sz) & ~(PGSIZE -1))

/* --- 权限位 (PTE Flags) --- */
#define PTE_V (1L << 0) // Valid: 该页表项是否有效
#define PTE_R (1L << 1) // Readable
#define PTE_W (1L << 2) // Writable
#define PTE_X (1L << 3) // Executable
#define PTE_U (1L << 4) // User: 是否允许用户态访问
#define PTE_A (1L << 6)

