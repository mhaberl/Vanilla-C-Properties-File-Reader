#include <stdlib.h>
#include <stdio.h>
#include "pfr/pfr.h"

int main() {

	printf("START property file reading and parsing test \n");

	vc_show_file_content();

	int age = vc_read_int("age");
	
	int gender = vc_read_char("gender");
	
	char *name = vc_read_string("name");

	printf("Age: %d\n", age);
	printf("Gender: %c\n", gender);
	printf("Name: %s\n", name);
	

	printf("END test \n");
}

