#ifndef __TERMINAL_H__
#define __TERMINAL_H__

    #include "vga.h"
    #include "../system/asm.h"

    struct term
    {
        struct debug
        {
            size_t row;
            size_t column;
            uint8_t color;
        }debug;
        struct log
        {
            size_t row;
            size_t column;
            uint8_t color;
        }log;
        struct text
        {
            size_t row;
            size_t column;
            uint8_t color;
        }text;
        uint16_t *buffer;
        uint16_t index_register;
        uint16_t data_register;
    }term;

    size_t strlen(const char* str);
    char itoa(size_t number);
    void terminal_init(void);
    void terminal_scroll(size_t lines);
    void terminal_setcolor(uint8_t color);
    void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
    void terminal_putchar(char c);
    void terminal_write(const char *data, size_t size);
    void terminal_writestring(const char *data);
    void terminal_set_cursor();
    void terminal_enable_cursor();

#endif /* __TERMINAL_H__ */
