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
static int property_count = 0;


int getEqualsSignPosition(char *string) {

	int l = -1;
	if(string == NULL)
		return -1;

	int j;	
	for(j=0;string[j]!='\0'&&string[j]!='\n'; j++) {
		if(string[j] == '=') {
			l = j;
		}
	}


}

char * getPropertyName(char *line) {


	int l = getEqualsSignPosition(line);

	if(l==-1 || l==0) //does not exist or key is empty
		return NULL;

	int i;
	char *pn = malloc(l);
	for(i=0; i<l; i++) {
		pn[i]=line[i];
	}
	pn[i+1]='\0';
	
	return pn;
}

char * getPropertyValue(char *line) {
	return "prop value";
}

char* vc_read_file() {

	FILE *file = fopen(CONFIG_FILE_NAME, "r");
	size_t max_line_length = DEFAULT_MAX_LINE_LENGTH;
	char * line = (char*) malloc(max_line_length * sizeof(char));
	ssize_t read;

	int max_property_count = DEFAULT_MAX_PROPERTY_COUNT;
	properties = (property*) malloc(max_property_count * sizeof(property));

	if (file != NULL) {

		while ((read = getline(&line, &max_line_length, file)) != -1) {
			
			
			if(property_count == max_property_count) {
				max_property_count *=2;
				properties = (property *) realloc(properties, max_property_count * sizeof(property));
			}

			printf("\nline: %s\n", line);
			printf("\t prop name: '%s'\n", getPropertyName(line));
			printf("\t prop value; '%s'\n\n", getPropertyValue(line));

			property_count++;

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

