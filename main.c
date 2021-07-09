#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scanner.h"

// DRIVER FUNCTION
int main()
{
	// maximum legth of string is 100 here
	char str[100] = "int a = b + 1c; if 0x98";
	parse(str);

	//~ char *str[] = {"ok", "teste"};
	
	//~ printf("%s\n", str[0]);

	//~ parse(str); // calling the parse function

	return (0);
}
