#include <stdlib.h>
#include <stdio.h>
#include "pfr/pfr.h"

int main() {

	printf("START property file reading and parsing test \n");

	vc_show_file_content();

	int age = vc_read_int("age");
	printf("Age: %d\n", age);

	float weight = vc_read_float("weight");
	printf("Weight: %f\n", weight);

	int gender = vc_read_char("gender");
	printf("Gender: %c\n", gender);
	
	char *name = vc_read_string("name");
	printf("Name: %s\n", name);
	

	printf("END test \n");
}

