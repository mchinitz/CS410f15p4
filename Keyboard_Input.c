#define ENTER 28
#define CLEAR 250
#define SHIFT 0x2A
#define SHIFT_UP 170
#define false 0
#include "OS_Image.h"

int is_upper_case = false;
int curr_len = 0;

//We are only supporting alpha-numeric characters and basic
//punctuation. '|' denotes a character that is not human-
//readible among the scancodes 0-53. 
char lower_scancode_arr[54] = \
	{'|','|', '1','2','3','4', '5','6','7','8','9','0','-','=','|', \
	'\t', 'q','w','e','r','t','y','u','i','o','p','[',']','\n', \
	'|','a','s','d','f','g','h','j','k','l',';','\'',
	'~','|','|','z','x','c','v','b','n','m',',','.','/'};
char upper_scancode_arr[54] = 
	{'|','|', '!','@','#','$', '%','^','&','*','(',')','_','+','|', \
	'|', 'Q','W','E','R','T','Y','U','I','O','P','{','}','\n', \
	'|','A','S','D','F','G','H','J','K','L',':','\"',
	'`','|','|','Z','X','C','Y','B','N','M','<','>','?'};	

//Used [1] for scancode information

//Given a scancode, returns the corresponding character in 
//upper or lower case
char scancode_to_char(int scancode)
{
	if (scancode < 0 || scancode >= 55)
		return '|';	
	if (is_upper_case)
		return upper_scancode_arr[scancode];
	else
		return lower_scancode_arr[scancode];
}

//Gets the value stored in port 0x60
int get_scancode()
{
		register unsigned int x __asm__("%al");
		x = 0;
		__asm__("inb $0x60, %al"); //output goes in %al
		return x;
}

int insert_nxt_char(char *s)
{
	if (curr_len >= MAX_LEN)
	{
		return -1;
	}
	unsigned int x = get_scancode();
	if (x != CLEAR)
	{
		//if just receiving the same shift status,
		//wait for a new signal
		if ((x == SHIFT && is_upper_case) || \
			(x == SHIFT_UP && !is_upper_case))
			return 0;
			
		else if (x == SHIFT_UP || x == SHIFT)
		{
			is_upper_case = !is_upper_case;
			return 0;
		}
		else if (x == ENTER)
		{
			s[curr_len] = '\0';
			return 1;
		}
		while (get_scancode() == x); //wait until released
		if (scancode_to_char(x) != '|')
		{
			s[curr_len] = scancode_to_char(x);
			curr_len ++;
		}
	}
	return 0;
}



