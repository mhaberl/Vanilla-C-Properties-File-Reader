#include "config.h"
#include <stdio.h>
#include <stdlib.h>

char* Read_File() {

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


int Read_Int(char* propertyName) {
	return 0;
}
long Read_Long(char* propertyName){
	return 0L;
}
float Read_Float(char* propertyName){
	return 0.0;
}
double Read_Double(char* propertyName){
	return 0.0;
}
char Read_Char(char* propertyName){
	return 'c';
}
char* Read_String(char* propertyName){
	return "abc";
}

