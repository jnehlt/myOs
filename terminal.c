#include "terminal.h"
#include "vga.h"

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
