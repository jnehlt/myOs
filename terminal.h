#ifndef __TERMINAL_H__
#define __TERMINAL_H__

    #include "vga.h"

    size_t strlen(const char* str);
    void terminal_init(void);
    void terminal_scroll_without_buffering(size_t lines);
    void terminal_setcolor(uint8_t color);
    void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
    void terminal_putchar(char c);
    void terminal_write(const char *data, size_t size);
    void terminal_writestring(const char *data);

#endif /* __TERMINAL_H__ */
