#compiler = gcc
compiler = ~/opt/cross/bin/i586-elf-gcc

Executable: OS_Image.o Keyboard_Input.o Command_Line.o
	$(compiler) -T linker.ld -ffreestanding -lgcc -nostdlib Multiboot_Header.S OS_Image.o Keyboard_Input.o Command_Line.o -o Executable
OS_Image.o: Multiboot_Header.S OS_Image.c Keyboard_Input.c Command_Line.c Multiboot_Header.h OS_Image.h
	$(compiler) -c -std=c99 Multiboot_Header.S OS_Image.c
Keyboard_Input.o: Keyboard_Input.c OS_Image.h
	$(compiler) -c -std=c99 Keyboard_Input.c
Command_Line.o: Command_Line.c OS_Image.h
	$(compiler) -c -std=c99 Command_Line.c

clean:
	rm Executable OS_Image.o Keyboard_Input.o Command_Line.o
