/* define the constant need by protect mode such as idt, gdt */
#ifndef __PM_H 
#define __PM_H 

#include <type.h>

/* ref: http://wiki.osdev.org/GDT */
/* ref: http://wiki.osdev.org/IDT */

#define NGDT 256

#define AC_AC 0x1       // access
#define AC_RW 0x2       // readable for code selector & writeable for data selector
#define AC_DC 0x4       // direcion
#define AC_EX 0x8       // executable, code segment
#define AC_REVERSE 0x10 
#define AC_PL_KERN 0x0  // RING 0 kernel level
#define AC_PL_USER 0x60 // RING 3 user level
#define AC_PR 0x80      // persent in memory

#define GDT_GR 0x8     // limit in 4k blocks
#define GDT_SZ 0x4     // 32 bit protect mode

#define NGDT 256

// gdt selector 
#define SEL_KERN_CODE 0x8
#define SEL_KERN_DATA 0x10
#define SEL_USER_CODE 0x18
#define SEL_USER_DATA 0x20

struct gdt_entry{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    unsigned limit_high: 4;
    unsigned flags: 4;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define NIDT 256

/* 386 32-bit gata type */
#define GATE_TASK 0x5
#define GATE_INT  0xe
#define GATE_TRAP 0xf

#define IDT_SS   0x1        // store segment
#define IDT_DPL_KERN 0x0    // descriptor privilege level
#define IDT_DPL_USER 0x6    
#define IDT_PR  0x8         // present in memory

struct idt_entry{
    uint16_t base_low;
    uint16_t selector;
    uint8_t always0;
    unsigned gate_type: 4;   // gate type
    unsigned flags: 4;  // S(0) DPL(1-2) P(3)
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void gdt_set_gate(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_init();

void idt_init();
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t gate, uint8_t flags);

#endif
