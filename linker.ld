ENTRY(_start)
SECTIONS{
    . = 0x80000000;
    .text : { *(.text) }
    . = ALIGN(0x1000);
    PROVIDE(etext = .);
    .rodata : { 
        . = ALIGN(16);
        *(.rodata)
        *(.rodata.*)
         }
    .data : { 
        . = ALIGN(16);
        *(.data)
        *(.data.*)
         }
    .bss : { 
        . = ALIGN(16);
        *(.bss .bss.*) 
        *(.sbss .sbss.*) /* 很关键 直接把全局未初始化的变量放在end前面 */
        . = ALIGN(16);
        }
    . = ALIGN(0x1000);    
    PROVIDE(end = .);
}