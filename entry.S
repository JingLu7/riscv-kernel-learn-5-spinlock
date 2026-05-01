.section .text
.global _start

_start:
    la sp, stack0
    li a0, 4096
    add sp, sp, a0

    call start

.section .bss
.align 16       # 16字节对齐
stack0:         # 标签
    .skip 4096  # 挖一块4kb大小内存