/*
 * Multiboot_Header.h
 *
 *  Created on: Nov 6, 2015
 *      Author: Michael
 */

#ifndef MULTIBOOT_HEADER_H_
#define MULTIBOOT_HEADER_H_

unsigned int magic;
unsigned int flags;
//in binary: 0b 0000 0000 0000 0001 0000 0000 0000 0011
//0: allignes boot modules to 4KB pages;
//1: to reserve kernal space
//no video capacity

unsigned int checksum; 
//address
unsigned int header_addr;
//Address to put header

//NOT SURE ON VALUES YET
//TODO decide on values
unsigned int load_addr;
unsigned int load_end_addr; //beginning of BSS
unsigned int bss_end_addr; //Should leave enough room
unsigned int entry_addr;
//Graphics settings
unsigned int mode_type;
unsigned int width;
unsigned int height;
unsigned int depth;

typedef struct multiboot_info
{
unsigned int flags;
unsigned int mem_lower;
unsigned int mem_upper;
unsigned int boot_device;
unsigned int mods_count;
unsigned int mods_addr;
unsigned int syms;
unsigned int mmap_length;
unsigned int mmap_addr;
unsigned int drives_length;
unsigned int drives_addr;
unsigned int config_table;
unsigned int boot_loader_name;
unsigned int apm_table;
} multiboot_info;



//YOU SHOULD BE USING #'s USED BY A REAL OS



#endif /* MULTIBOOT_HEADER_H_ */

