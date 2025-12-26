#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include<stdint.h>

void exception_handler(uint32_t interrupt, uint32_t error);
void idt_init(void);

typedef struct {   //IDT-entry(32-bit)
    uint16_t isr_low; 
    uint16_t kernel_cs; //Loads this into CS before calling ISR
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;

} __attribute__((packed)) idt_entry_t;

// typedef struct{ //IDT-entry(64-bit)
//     uint16_t isr_low;
//     uint16_t kernel_cs;
//     uint8_t ist;
//     uint8_t attributes;
//     uint16_t isr_mid;
//     uint32_t isr_high;
//     uint32_t reserved;
// } __attribute__((packed)) idt_entry_t

typedef struct { //idt-ptr
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;


#endif