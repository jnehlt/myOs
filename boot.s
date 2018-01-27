/* MULTIBOOT1 HEADER */
.set ALIGN,     1<<0                /* align loaded modules on page boundaries */
.set MEMINFO,   1<<1                /* provide memory map */
.set FLAGS,     ALIGN | MEMINFO     /* Multiboot flag field */
.set MAGIC,     0x1BADB002          /* 'magic number' for MULTIBOOT1 */
.set CHECKSUM,  -(MAGIC + FLAGS)    /* checksum to provide we are in multiboot */

/* First 8KiB of the kernel file, aligned 32-bit boundary. */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack implementation
    its a x86 implementation so, size = 16384bytes
    it also contains its top and bottom to make kernel-panic work properly
*/
.section        .bss
.align          16
stack_bottom:
.skip           16384 # 16KiB
stack_top:

/* entrypoint of the kernel, after bootloader finish its job */
.section        .text
.global         _start
.type           _start, @function
_start:
    /* Since this, we're in 32-bit protected mode.
     * Interrupts are disabled.
     * Paging is disabled - no virtual memory.
     * Kernel has full control of the CPU, but...
     * CPU is not fully initialized yet.
     * no libc/glibc in there - make your own :)
     * floating point instructions - not initialized
     * security - NULL
     * safeguards - NULL
     * debug - NULL also :D
     */

     /* Setup top of stack on esp register */
     mov $stack_top, %esp

     /* TODO:
      *    Load GDT
      *    Enable Paging //if you want
      *    write runtime support to work with;
            -global constructors
            -exceptions
            -eg //cxx Stuff.
      */

      /* enter High-level kernel.
       * it will require 16-byte stack aligned since there
       */
      call kernel_main

      /*
      after kernel_main finishes its work, put CPU into infinite loop
      it requires:
        Disabling interrupts with cli (clear interrupt enable in flags).
        //they are alredy disabled by bootloader
        Wait for the next interrupt to arrive with halt instruction
        Jump to the halt instruction.
      */

      cli /*disable interrupts*/
1:    hlt
      jmp 1b

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start
