#ifndef __VGA_H__
#define __VGA_H__

    #if !defined(__cplusplus)
        #include <stdbool.h>
    #endif

    #include <stddef.h>
    #include <stdint.h>

    /* Hardware text mode color constants */
    enum vga_color
    {
        VGA_COLOR_BLACK         =   0,
        VGA_COLOR_BLUE          =   1,
        VGA_COLOR_GREEN         =   2,
        VGA_COLOR_CYAN          =   3,
        VGA_COLOR_RED           =   4,
        VGA_COLOR_MAGENTA       =   5,
        VGA_COLOR_BROWN         =   6,
        VGA_COLOR_LIGHT_GREY    =   7,
        VGA_COLOR_DARK_GREY     =   8,
        VGA_COLOR_LIGHT_GREEN   =   10,
        VGA_COLOR_LIGHT_CYAN    =   11,
        VGA_COLOR_LIGHT_RED     =   12,
        VGA_COLOR_LIGHT_MAGENTA =   13,
        VGA_COLOR_WHITE         =   14,
    };

    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;

    struct term
    {
        size_t row;
        size_t column;
        uint8_t color;
        uint16_t *buffer;
    }terminal;

    static inline uint8_t
    vga_entry_color(enum vga_color fg, enum vga_color bg);
    static inline uint16_t
    vga_entry(unsigned char uc, uint8_t color);

#endif /* __VGA_H__ */
