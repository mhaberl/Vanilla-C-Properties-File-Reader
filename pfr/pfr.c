#include "config.h"
#include <stdio.h>
#include <stdlib.h>

char* vc_read_file() {

	FILE *file = fopen(CONFIG_FILE_NAME, "r");
	size_t len = 128;
	char * line = (char*)malloc(len * sizeof(char));
	ssize_t read;

	if (file != NULL) {

		while ((read = getline(&line, &len, file)) != -1) {
			printf("%s", line);
		}

		if (line)
			free(line);
		fclose(file);
	}
	return NULL;
}


int vc_read_int(char* propertyName) {
	return 0;
}
long vc_read_long(char* propertyName){
	return 0L;
}
float vc_read_float(char* propertyName){
	return 0.0;
}
double vc_read_double(char* propertyName){
	return 0.0;
}
char vc_read_char(char* propertyName){
	return 'c';
}
char* vc_read_string(char* propertyName){
	return "abc";
}

