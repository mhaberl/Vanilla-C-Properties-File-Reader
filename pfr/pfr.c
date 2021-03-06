#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct _property {
	char *name;
	char *value;
} property;


static property *properties = NULL;
static int property_count = 0;

static char* trim(char* inputString) {

	char* start = inputString;
	char* end;

	while(isspace( (unsigned char)* start))  // leading space
		start++;

	if(*start == 0)
		return "\0";
	
	end = start + strlen(start) - 1;
	while(end > start && isspace((unsigned char)*end)) // trailing space
		end--;
	

	int length = end - start + 2;
	char* trimmedString = (char*) malloc(length * sizeof(char));
	memcpy(trimmedString, start, length);
	trimmedString[length-1] = '\0'; // end the string

	
	return trimmedString;
}

static int isFileUnread() {
	return properties == NULL;
}

static int getEqualsSignPosition(char *string) {

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

static char * getPropertyName(char *line) {

	int esp = getEqualsSignPosition(line);

	if(esp==-1 || esp==0) //does not exist or key is empty
		return NULL;

	int i;
	char *pn = malloc(esp+1);
	memcpy(pn,line,esp);
	pn[esp]='\0';
	

	char* trimmedPn = trim(pn);
	free(pn);

	return trimmedPn;
}

static char * getPropertyValue(char *line) {
	
	int esp = getEqualsSignPosition(line);
	int lineLength = strlen(line);

	if(esp==-1 || esp==0 || esp==lineLength+1) //does not exist or key is empty
		return NULL;

	int i;
	char *pv = malloc(lineLength-esp);
	memcpy(pv,line+esp+1,lineLength-esp-1);
	pv[lineLength-esp-1]='\0';

	char* trimmedPv = trim(pv);
	free(pv);

	return trimmedPv;
}

static char* read_file() {

	FILE *file = fopen(CONFIG_FILE_NAME, "r");
	size_t max_line_length = DEFAULT_MAX_LINE_LENGTH;
	char * inputLine = (char*) malloc(max_line_length * sizeof(char));
	ssize_t read;

	int max_property_count = DEFAULT_MAX_PROPERTY_COUNT;
	properties = (property*) malloc(max_property_count * sizeof(property));

	if (file != NULL) {
		while ((read = getline(&inputLine, &max_line_length, file)) != -1) {
			
			if(property_count == max_property_count) {
				max_property_count *=2;
				properties = (property *) realloc(properties, max_property_count * sizeof(property));
			}

			char* line = trim(inputLine);

			char* pn = getPropertyName(line);
			if(pn != NULL && line[0]!='#')	{
				char* pv = getPropertyValue(line);
				if(pv != NULL) {
					properties[property_count].name=pn;
		                        properties[property_count].value=pv;
					property_count++;
				}
			}
			if (line && *line)
				free(line);
		}
		if (inputLine && *inputLine)
			free(inputLine);
		fclose(file);
	}
	return NULL;
}

int vcpfr_show_file_content() {

	if(isFileUnread())
		read_file();
	int ind;
	for(ind=0;ind<property_count; ind++) {
		printf("\t prop name: '%s'\n", properties[ind].name);
		printf("\t prop value: '%s'\n\n", properties[ind].value);

	}
	return 0;
}

int vcpfr_free() {

	if(isFileUnread())
		return;

	int ind;
	for(ind=0;ind<property_count; ind++) {
		free(properties[ind].name);
		free(properties[ind].value);
	}
	free(properties);
	return 0;
} 

static char* read_value(char* propertyName) {

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

int vcpfr_read_int(char* propertyName) {
	char* value = read_value(propertyName);
	if (value!= NULL)
		return atoi(value);
	else 
		return 0;
}

float vcpfr_read_float(char* propertyName){
	char* value = read_value(propertyName);
	if (value!= NULL)
		return atof(value); 
	else 
		return 0.0;
}

char vcpfr_read_char(char* propertyName){
	char* value = read_value(propertyName);
	if (value!= NULL)
		return *value; 
	else 
		return '\0';
}

char* vcpfr_read_string(char* propertyName){
	return read_value(propertyName);
}

