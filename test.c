#include <stdlib.h>
#include <stdio.h>
#include "pfr/pfr.h"

int main() {

	printf("START property file reading and parsing test \n");

	int age = Read_Int("age");
	
	int gender = Read_Char("gender");
	
	char *name = Read_String("name");

	printf("Age: %d\n", age);
	printf("Gender: %c\n", gender);
	printf("Name: %s\n", name);

	printf("END test \n");
}

