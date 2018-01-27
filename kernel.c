#include "bin/graphics/terminal.h"
#include "drivers/keyboard/keyboard.h"

void
kernel_main(void)
{
    terminal_init();

    terminal_writestring("Welcome\n");
    //↑swap to asciArt welcome shit
    while(1)
        //terminal_putchar(getScancode());
        terminal_putchar(getchar());
}
