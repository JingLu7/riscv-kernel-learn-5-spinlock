void uart_puts(char *s); //函数声明
void kinit(void);
void kvminit(void);
void kvminithart(void);
void trapinit();
void set_next_timer();
void task_init(int i, void (*entry)());
void task_a();
void task_b();
void scheduler();
void uart_init();
void proc_init();

void main(void) {
    uart_init();
    proc_init();


    kinit();
    kvminit();
    kvminithart();
    trapinit();
    set_next_timer();

    uart_puts("hello my first kernel ");

    task_init(0, task_a);
    task_init(1, task_b);
    
    
    scheduler();

}