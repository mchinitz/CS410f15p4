#include "Multiboot_Header.h"
#include "OS_Image.h"
int old_eflags = 0;
#define BEGINNING_OF_HEADER 1000000
#define BEGINNING_OF_DATA_SEGMENT ((BEGINNING_OF_HEADER) + 1763)
//The constant to add is virtual size of text segment
#define BASE_VIDEO_MEMORY 0xb8000

//[2]
void write_char(int col, int color, char data)
{
	char *loc_to_write = (char *)(BASE_VIDEO_MEMORY + 2 * col);
	loc_to_write[0] = data;
	loc_to_write[1] = color;
}

void write_sentence(int color, char *s)
{
	int index = 0;
	while (s[index] != '\0')
	{
		write_char(index, color, s[index]);
		index ++;
	}
}


//Grub documentation seems to suggest it is necessary to initialize
//the state of the machine, but it doesn't actually appear
//necessary.
void init_state()
{
__asm__(
	"mov %1, %%ebx \n\t"
	"mov $0x2BADB002, %%eax \n\t"
	"mov $0x1, %%ecx \n\t"
	"mov %%ecx, %%cr0 \n\t"
	//now setup eflags
	"pushfl \n\t"
	"mov 0(%%esp), %%ecx \n\t"
	"mov %%ecx, %0 \n\t" //retains old value
	"andl $0xFFFDFDFF, 0(%%esp) \n\t"
	"popfl \n\t"
	: "=r" (old_eflags)
	: "r" (BEGINNING_OF_HEADER)
	);
}


int main()
{
	init_state();
	terminal_initialize();
	char s[MAX_LEN];
	int result;
	while (1)
	{
		result = insert_nxt_char(s);
		if (result == -1)
		{
			write_sentence(COLOR_WHITE, "Error: buffer overflow");
			break;
		}
		else if (result == 1)
			break;
		}
	if (result != -1) //if no error
		write_sentence(COLOR_WHITE, s);
	
	//restores state of eflags
	__asm__
	(
	"pushfl \n\t"
	"mov old_eflags, %ecx \n\t"
	"mov %ecx, 0(%esp) \n\t"
	"popfl"
	);
	return 0;
}
