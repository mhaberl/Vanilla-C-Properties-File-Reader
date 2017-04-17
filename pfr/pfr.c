#include "config.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { INT, FLOAT, CHAR, STRING } property_type;

typedef struct _property {
	char name;
	property_type type;
	
	int i_value;
	float f_value;
	char c_value;
	char *s_value;
} property;


static property *properties = NULL;

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
float vc_read_float(char* propertyName){
	return 0.0;
}
char vc_read_char(char* propertyName){
	return 'c';
}
char* vc_read_string(char* propertyName){
	return "abc";
}

