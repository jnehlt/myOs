#ifndef __ASM_H__
#define __ASM_H__

    static inline uint8_t
    inb(uint16_t port)
    {
        uint8_t ret;
        asm volatile("inb %1, %0"
                        : "=a"(ret)
                        : "Nd"(port)
                    );
        return ret;
    }

    static inline void
    outb(uint16_t port, uint8_t value)
    {
        asm volatile ("outb %0, %1"::"a"(value), "Nd"(port));
    }

#endif /* __ASM_H__ */
