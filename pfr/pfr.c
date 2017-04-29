#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _property {
	char *name;
	char *value;
} property;


static property *properties = NULL;
static int property_count = 0;

int isFileUnread() {
	return properties == NULL;
}

int getEqualsSignPosition(char *string) {

	int esp = -1;
	if(string == NULL)
		return -1;

	int j;	
	for(j=0;string[j]!='\0'&&string[j]!='\n'; j++) {
		if(string[j] == '=') {
			esp = j;
			break;
		}
	}
	return esp;
}

char * getPropertyName(char *line) {


	int esp = getEqualsSignPosition(line);

	if(esp==-1 || esp==0) //does not exist or key is empty
		return NULL;

	int i;
	char *pn = malloc(esp+1);
	memcpy(pn,line,esp);
	pn[esp]='\0';
	
	return pn;
}

char * getPropertyValue(char *line) {
	
	int esp = getEqualsSignPosition(line);
	int lineLength = strlen(line);

	if(esp==-1 || esp==0 || esp==lineLength+1) //does not exist or key is empty
		return NULL;

	int i;
	char *pv = malloc(lineLength-esp-1);
	memcpy(pv,line+esp+1,lineLength-esp-2);
	pv[lineLength-esp-2]='\0';
	
	return pv;
}

char* read_file() {

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

			char* pn = getPropertyName(line);
			if(pn != NULL)	{
				char* pv = getPropertyValue(line);
				if(pv != NULL) {
					properties[property_count].name=pn;
		                        properties[property_count].value=pv;
					property_count++;
				}
			}
		}
		if (line)
			free(line);
		fclose(file);
	}
	return NULL;
}

void vc_show_file_content() {

	if(isFileUnread())
		read_file();
	int ind;
	for(ind=0;ind<property_count; ind++) {
		printf("\t prop name: '%s'\n", properties[ind].name);
		printf("\t prop value: '%s'\n\n", properties[ind].value);

	}
}

char* read_value(char* propertyName) {

	if(propertyName == NULL)
		return NULL;

	if(isFileUnread())
                read_file();
        int ind;
        for(ind=0;ind<property_count; ind++) {
		if(!strcmp(propertyName, properties[ind].name))
                	return properties[ind].value;
        }
	return NULL;
}

int vc_read_int(char* propertyName) {
	char* value = read_value(propertyName);
	if (value!= NULL)
		return atoi(value);
	else 
		return 0;
}
float vc_read_float(char* propertyName){
	char* value = read_value(propertyName);
	if (value!= NULL)
		return atof(value); 
	else 
		return 0.0;
}
char vc_read_char(char* propertyName){
	char* value = read_value(propertyName);
	if (value!= NULL)
		return *value; 
	else 
		return '\0';
}
char* vc_read_string(char* propertyName){
	return read_value(propertyName);
}

