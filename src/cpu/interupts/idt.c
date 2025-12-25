#include "interrupts.h"

#define IDT_ENTRIES 256

static idt_entry_t idt[IDT_ENTRIES];
static idtr_t idtr;

/* ISR stubs from assembly */
extern void isr_stub_0();
extern void isr_stub_1();
extern void isr_stub_2();
extern void isr_stub_3();
extern void isr_stub_4();
extern void isr_stub_5();
extern void isr_stub_6();
extern void isr_stub_7();
extern void isr_stub_8();
extern void isr_stub_9();
extern void isr_stub_10();
extern void isr_stub_11();
extern void isr_stub_12();
extern void isr_stub_13();
extern void isr_stub_14();
extern void isr_stub_15();
extern void isr_stub_16();
extern void isr_stub_17();
extern void isr_stub_18();
extern void isr_stub_19();
extern void isr_stub_20();
extern void isr_stub_21();
extern void isr_stub_22();
extern void isr_stub_23();
extern void isr_stub_24();
extern void isr_stub_25();
extern void isr_stub_26();
extern void isr_stub_27();
extern void isr_stub_28();
extern void isr_stub_29();
extern void isr_stub_30();
extern void isr_stub_31();

static void idt_set_gate(uint8_t n, uint32_t handler)
{
    idt[n].isr_low    = handler & 0xFFFF;
    idt[n].kernel_cs = 0x08;     // kernel code segment
    idt[n].reserved  = 0;
    idt[n].attributes= 0x8E;     
    idt[n].isr_high  = (handler >> 16) & 0xFFFF;
}

void idt_init(void)
{
    idtr.limit = sizeof(idt) - 1;
    idtr.base  = (uint32_t)&idt;

    idt_set_gate(0,  (uint32_t)isr_stub_0);
    idt_set_gate(1,  (uint32_t)isr_stub_1);
    idt_set_gate(2,  (uint32_t)isr_stub_2);
    idt_set_gate(3,  (uint32_t)isr_stub_3);
    idt_set_gate(4,  (uint32_t)isr_stub_4);
    idt_set_gate(5,  (uint32_t)isr_stub_5);
    idt_set_gate(6,  (uint32_t)isr_stub_6);
    idt_set_gate(7,  (uint32_t)isr_stub_7);
    idt_set_gate(8,  (uint32_t)isr_stub_8);
    idt_set_gate(9,  (uint32_t)isr_stub_9);
    idt_set_gate(10,  (uint32_t)isr_stub_10);
    idt_set_gate(11,  (uint32_t)isr_stub_11);
    idt_set_gate(12,  (uint32_t)isr_stub_12);
    idt_set_gate(13,  (uint32_t)isr_stub_13);
    idt_set_gate(14,  (uint32_t)isr_stub_14);
    idt_set_gate(15,  (uint32_t)isr_stub_15);
    idt_set_gate(16,  (uint32_t)isr_stub_16);
    idt_set_gate(17,  (uint32_t)isr_stub_17);
    idt_set_gate(18,  (uint32_t)isr_stub_18);
    idt_set_gate(19,  (uint32_t)isr_stub_19);
    idt_set_gate(20,  (uint32_t)isr_stub_20);
    idt_set_gate(21,  (uint32_t)isr_stub_21);
    idt_set_gate(22,  (uint32_t)isr_stub_22);
    idt_set_gate(23,  (uint32_t)isr_stub_23);
    idt_set_gate(24,  (uint32_t)isr_stub_24);
    idt_set_gate(25,  (uint32_t)isr_stub_25);
    idt_set_gate(26,  (uint32_t)isr_stub_26);
    idt_set_gate(27,  (uint32_t)isr_stub_27);
    idt_set_gate(28,  (uint32_t)isr_stub_28);
    idt_set_gate(29,  (uint32_t)isr_stub_29);
    idt_set_gate(30,  (uint32_t)isr_stub_30);
    idt_set_gate(31,  (uint32_t)isr_stub_31);

    asm volatile ("lidt %0" : : "m"(idtr));
}
