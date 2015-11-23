.set magic, 0x1BADB002
.set flags, 0x00003
//in binary: 0b 0000 0000 0000 0000 0000 0000 0000 0011
//0: allignes boot modules to 4KB pages;
//1: to reserve kernal space
//no video capacity
.set checksum, -1 * (magic + flags)
.set header_addr, 1000000 
.set load_addr, 1000000
.set load_end_addr, 2000000
.set bss_end_addr,  3000000
.set entry_addr, 1000000

//Graphics settings
.set mode_type, 0
.set width, 0
.set height, 0
.set depth, 0

.section .multiboot
.align 4
.long magic
.long flags
.long checksum


//Loads program
.globl _start
_start:
//Makes room on the stack
lea 10000(%esp), %esp
call main
lea -10000(%esp), %esp //returns stack to initial state
jmp .Infinite

.Infinite:
	jmp .Infinite


