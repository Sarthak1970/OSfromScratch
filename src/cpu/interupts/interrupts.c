#include "interrupts.h"
#include "../../kernel/terminal.h"

void exception_handler(uint32_t interrupt, uint32_t error)
{
    terminal_writestring("CPU Exception\n");
    terminal_putchar('0' + interrupt);
    terminal_writestring("\n");
    
    for (;;);
}
