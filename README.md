# myOs
Simple Operating system, created to understand how Os-es actually works.

* [OSDev](http://wiki.osdev.org/Main_Page). Base for my work.
* [Bran's Kernel Development](http://www.osdever.net/bkerndev/index.php). Additional information
* [Extended](http://www.cs.vu.nl/~herbertb/misc/writingkernels.txt).

|Filename    |Description                       |
|------------|----------------------------------|
|boot.s      |<ul><li>This file sets many [things](https://www.gnu.org/software/grub/manual/multiboot/html_node/boot_002eS.html)</li><li>like grub Multiboot Header,</li><li>implements stack for x86,</li><li>sets entrypoint of kernel,</li><li>Load kernel, etc.</li>
                  <li>In near future i plan to implement</li>
                  <li> *Interrupts*</li>
                  <li> *Paging*</li>
                  <li> *Fully Initialize CPU*</li>
                  <li> *libc*</li>
                  <li> *floating point instructions*</li>
                  <li> *security*</li>
                  <li> *safeguards*</li>
                  <li> *debug*</li>
                  <li> *GDT*</li>
                  <li> *runtime support for Cxx*</li>
                </ul>
