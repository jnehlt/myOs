#include "..\system\stdlib.h"
#include "terminal.h"
#include "vga.h"

size_t
strlen(const char* str)
{
    size_t len = 0;
    while(*(str + len++));
    return len;
}

char
itoa(size_t number)
{
    return number + 48;
}

void
terminal_init(void)
{
    term.buffer = (uint16_t*) 0xB8000;
    term.index_register = 0x03D4;
    term.data_register = 0x03D5;

    terminal_enable_cursor();

    term.debug.row = DEBUG_POSITION;
    term.debug.column = 0;
    term.debug.color = vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_RED);

    term.log.row = LOG_POSITION;
    term.log.column = 0;
    term.log.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BROWN);

    term.text.row = 1;
    term.text.column = 0;
    term.text.color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLUE);

    for(size_t x = DEBUG_POSITION; x < VGA_WIDTH; ++x)
        term.buffer[x] = vga_entry(' ', term.debug.color);

    for(size_t y = 1; y <= TEXT_HEIGHT; ++y)
        for(size_t x = 0; x < VGA_WIDTH; ++x)
            term.buffer[y * VGA_WIDTH + x] = vga_entry(' ', term.text.color);

    for(size_t x = 0; x < VGA_WIDTH; ++x)
         term.buffer[LOG_POSITION * VGA_WIDTH + x] = vga_entry(' ', term.log.color);


    terminal_set_cursor();
}

void
terminal_scroll(size_t lines_to_scroll)
{
    if(lines_to_scroll == 0) return;
    /* if(lines_to_scroll < 0) { terminal_rewind(lines_to_scroll); return; } for future use. */

    for(size_t y = 1; y <= TEXT_HEIGHT; ++y)
        for(size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t position = y * VGA_WIDTH + x;
            if(y == TEXT_HEIGHT)
                term.buffer[position] = vga_entry(' ', term.text.color);
            else
                term.buffer[position] = term.buffer[position + VGA_WIDTH];
        }
    term.text.row -= lines_to_scroll;
}

void
terminal_setcolor(uint8_t color)
{
    term.text.color = color;
}

void
terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    term.buffer[index] = vga_entry(c, color);
}

void
terminal_putchar(char c)
{
    if(c == 0x39) // space
    {
        if(term.text.column >= VGA_WIDTH)
        {
            term.text.column -= VGA_WIDTH;
            if(++term.text.row >= LOG_POSITION)
                terminal_scroll(term.text.row - LOG_POSITION + 1);
        }
        terminal_putentryat(' ', term.text.color, term.text.column++, term.text.row);
    }
    else if(c == '\n')
    {
        if(++term.text.row >= LOG_POSITION)
            terminal_scroll(term.text.row - LOG_POSITION + 1);
        term.text.column = 0;
    }
    else if(c == '\t')
    {
        if((term.text.column += 3) >= VGA_WIDTH)
        {
            term.text.column -= VGA_WIDTH;
            if(++term.text.row >= LOG_POSITION)
                terminal_scroll(term.text.row - LOG_POSITION + 1);
        }
    }
    else if(c == 0x00)
    {
        return;
    }
    else
    {
        if(term.text.column >= VGA_WIDTH)
        {
            term.text.column -= VGA_WIDTH;
            if(++term.text.row >= LOG_POSITION)
                terminal_scroll(term.text.row - LOG_POSITION + 1);
        }
        terminal_putentryat(c, term.text.color, term.text.column++, term.text.row);
    }

    terminal_set_cursor();
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
    terminal_write(data, strlen(data) - 1);
}

void
terminal_enable_cursor()
{
    outb(term.index_register, 0x0A);    // set vga 'Cursor Start Register (Index 0Ah)'
    outb(term.data_register, 0xCE);     // witch is (1100 1100) -- wideness of cursor
}

void
terminal_set_cursor()
{
    uint16_t position = term.text.row * VGA_WIDTH + term.text.column;

    outb(term.index_register, 0x0E);
    outb(term.data_register, (uint8_t) (0xFF & (position >> 8)));
    outb(term.index_register, 0x0F);
    outb(term.data_register, (uint8_t) (0xFF & position));
}
