#include <stdlib.h>
#include <stdio.h>
#include "pfr/pfr.h"

int main() {

	printf("START property file reading and parsing test \n");

	vcpfr_show_file_content();

	int age = vcpfr_read_int("age");
	printf("Age: %d\n", age);

	float weight = vcpfr_read_float("weight");
	printf("Weight: %f\n", weight);

	int gender = vcpfr_read_char("gender");
	printf("Gender: %c\n", gender);
	
	char *name = vcpfr_read_string("name");
	printf("Name: %s\n", name);
	

	vcpfr_free();
	printf("END test \n");
}

