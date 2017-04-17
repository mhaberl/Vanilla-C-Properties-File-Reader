#include <stdlib.h>
#include <stdio.h>
#include "pfr/pfr.h"

int main() {

	printf("START property file reading and parsing test \n");

	int age = vc_read_int("age");
	
	int gender = vc_read_char("gender");
	
	char *name = vc_read_string("name");

	printf("Age: %d\n", age);
	printf("Gender: %c\n", gender);
	printf("Name: %s\n", name);

	vc_read_file();

	printf("END test \n");
}

