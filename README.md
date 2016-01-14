# CS410f15p4
Kernel

Overview:
This kernel waits for the user to input a sentence, and then
prints it out. Please note that some keys are not supported.
The supported keys are all letters, numbers, and punctuation.
If a particular key is not supported, a '|' is printed.
To capitalize, use left-shift.

Prerequisites:
qemu
Ubuntu 14.04 (not sure about later versions)
i586-elf cross compiler

Compiling and Running:
To compile, make. To run, qemu-system-i386 -kernel Executable.
