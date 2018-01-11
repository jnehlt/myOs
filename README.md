# myOs
Simple Operating system, created to understand how Os-es actually works.

* [OSDev](http://wiki.osdev.org/Main_Page). Base for my work.
* [Bran's Kernel Development](http://www.osdever.net/bkerndev/index.php). Additional information
* [Extended](http://www.cs.vu.nl/~herbertb/misc/writingkernels.txt).

|Filename    |Description                       |
|------------|----------------------------------|
|            |This file sets many [things](https://www.gnu.org/software/grub/manual/multiboot/html_node/boot_002eS.html)|
|            |like grub Multiboot Header,       |
|            |implements stack for x86,         |
|            |sets entrypoint of kernel,        |
|            |Load kernel, etc.                 |
|            |In near future i plan to implement|
|            | *Interrupts*                     |
|            | *Paging*                         |
|boot.s      | *Fully Initialize CPU*           |
|            | *libc*                           |
|            | *floating point instructions*    |
|            | *security*                       |
|            | *safeguards*                     |
|            | *debug*                          |
|            | *GDT*                            |
|            | *runtime support for Cxx*        |
|            |                                  |
