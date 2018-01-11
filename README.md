# myOs
Simple Operating system, created to understand how Os-es actually works.

* [OSDev](http://wiki.osdev.org/Main_Page). Base for my work.
* [Bran's Kernel Development](http://www.osdever.net/bkerndev/index.php). Additional information
* [Extended](http://www.cs.vu.nl/~herbertb/misc/writingkernels.txt).

|Filename    |Description                       |
|------------|----------------------------------|
|[boot.s](https://github.com/sebastianbakala/myOs/blob/master/boot.s)      |This file sets many [things](https://www.gnu.org/software/grub/manual/multiboot/html_node/boot_002eS.html) like grub Multiboot Header, implements stack for x86, sets entrypoint of kernel, loads kernel, etc.</br>In near future I'm planing to implement stuff like</br> *Interrupts*</br> *Paging*</br> *Fully Initialize CPU*</br> *libc*</br> *floating point instructions*</br> *security*</br> *safeguards*</br> *debug*</br> *GDT*</br> *runtime support for Cxx*</br>And so on.</br>Gcc Call:</br>`i686-elf-as boot.s -o boot.o`
|[kernel.c](https://github.com/sebastianbakala/myOs/blob/master/kernel.c)    |will includes many base functions needed for system use.</br>Freestanding gcc call:</br>`i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra`</br>I'm using [freedstanding cross-compiler](https://github.com/lordmilko/i686-elf-tools) with libgcc included|
|[linker.ld](https://github.com/sebastianbakala/myOs/blob/master/linker.ld)   |For gcc cross-compiler to link boot.o, and kernel.o together. It produces kernel.bin. ELF look-alike|
