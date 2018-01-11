#if !defined(__cplusplus)
    #include <stdbool.h>
#endif

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);
void terminal_init(void);
void terminal_scroll_without_buffering(size_t lines);
void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);

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
vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t
vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t
strlen(const char* str)
{
    size_t len = 0;
    while(*(str + len++));
    return len;
}

void
terminal_init(void)
{
    terminal.row = 0;
    terminal.column = 0;
    terminal.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    terminal.buffer = (uint16_t*) 0xB8000;

    for(size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal.buffer[index] = vga_entry(' ', terminal.color);
        }
    }
}

void
terminal_scroll_without_buffering(size_t lines)
{
    if(lines == 0) return;
    /* if(lines < 0) { terminal_rewind(lines); return; } for future use. */

    for(size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            if(y == VGA_HEIGHT - lines)
                terminal.buffer[index] = vga_entry(' ', terminal.color);
            else
                terminal.buffer[index] = terminal.buffer[index + VGA_WIDTH - 1];
        }
    }
}

void
terminal_setcolor(uint8_t color)
{
    terminal.color = color;
}

void
terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal.buffer[index] = vga_entry(c, color);
}

void
terminal_putchar(char c)
{
    if(c == '\n')
    {
        terminal.column = 0;
        ++terminal.row;
    }

    // else if(c == '\t')
    // {
    //     if(terminal.column + 3 >= VGA_WIDTH)
    //     {
    //         terminal.column = 0;
    //         if(++terminal.row == VGA_HEIGHT)
    //             terminal_scroll();
    //     }
    //     else
    //         terminal.column += 3;
    // }

    else
    {
        terminal_putentryat(c, terminal.color, terminal.column, terminal.row);
    }

    if(++terminal.column >= VGA_WIDTH)
    {
        terminal.column = 0;
        if(++terminal.row >= VGA_HEIGHT)
        {
            terminal_scroll_without_buffering(1 /* line */ );
            --terminal.row;
        }
    }
    else if(terminal.row >= VGA_HEIGHT)
    {
        terminal_scroll_without_buffering(terminal.row - (VGA_HEIGHT - 1));
        terminal.row = terminal.row - (VGA_HEIGHT - 1);
    }
}

void
terminal_write(const char *data, size_t size)
{
    for(size_t i = 0; i < size; ++i)
        terminal_putchar(data[i]);
}

void
terminal_writestring(const char *data)
{
    terminal_write(data, strlen(data));
}


void
kernel_main(void)
{
    terminal_init();

    terminal_writestring("11111111111111111111111111111111111111111111111111111111111111111111111111111111\n\
22222222222222222222222222222222222222222222222222222222222222222222222222222222\n\
33333333333333333333333333333333333333333333333333333333333333333333333333333333\n\
44444444444444444444444444444444444444444444444444444444444444444444444444444444\n\
55555555555555555555555555555555555555555555555555555555555555555555555555555555\n\
66666666666666666666666666666666666666666666666666666666666666666666666666666666\n\
77777777777777777777777777777777777777777777777777777777777777777777777777777777\n\
88888888888888888888888888888888888888888888888888888888888888888888888888888888\n\
99999999999999999999999999999999999999999999999999999999999999999999999999999999\n\
10101010101010101010101010101010101010101010101010101010101010101010101010101010\n\
11111111111111111111111111111111111111111111111111111111111111111111111111111111\n\
12121212121212121212121212121212121212121212121212121212121212121212121212121212\n\
13131313131313131313131313131313131313131313131313131313131313131313131313131313\n\
14141414141414141414141414141414141414141414141414141414141414141414141414141414\n\
15151515151515151515151515151515151515151515151515151515151515151515151515151515\n\
16161616161616161616161616161616161616161616161616161616161616161616161616161616\n\
17171717171717171717171717171717171717171717171717171717171717171717171717171717\n\
18181818181818181818181818181818181818181818181818181818181818181818181818181818\n\
19191919191919191919191919191919191919191919191919191919191919191919191919191919\n\
20202020202020202020202020202020202020202020202020202020202020202020202020202020\n\
21212121212121212121212121212121212121212121212121212121212121212121212121212121\n\
22222222222222222222222222222222222222222222222222222222222222222222222222222222\n\
23232323232323232323232323232323232323232323232323232323232323232323232323232323\n\
24242424242424242424242424242424242424242424242424242424242424242424242424242424\n\
25252525252525252525252525252525252525252525252525252525252525252525252525252525\n\
26262626262626262626262626262626262626262626262626262626262626262626262626262626");
}
