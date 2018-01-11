#if !defined(__cplusplus)
    #include <stdbool.h>
#endif

#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);
void terminal_init(void);
void terminal_refresh(void);
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
terminal_refresh(void)
{
    for(size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH + x;
            if(y == VGA_HEIGHT - 1)
                terminal.buffer[index] = vga_entry(' ', terminal.color);
            else
                terminal.buffer[index] = terminal.buffer[index + VGA_WIDTH];
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
        if(++terminal.row == VGA_HEIGHT)
            terminal_refresh();
    }

    else if(c == '\t')
    {
        if(terminal.column + 3 >= VGA_WIDTH)
        {
            terminal.column = 0;
            if(++terminal.row == VGA_HEIGHT)
                terminal_refresh();
        }
        else
            terminal.column += 3;
    }

    else
    {
        terminal_putentryat(c, terminal.color, terminal.column, terminal.row);
    }

    if(++terminal.column == VGA_WIDTH)
    {
        terminal.column = 0;
        if(++terminal.row == VGA_HEIGHT)
            terminal_refresh();
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

    terminal_writestring("1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26");
}
