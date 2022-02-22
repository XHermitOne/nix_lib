/**
*                                    
*   Code from the book C Unleashed   
*   Macmillan, 2000                  
*   Chapter 6: Data Files            
*   Steve Summit 2000-03-17          
*                                    
*/

#include "inifunc.h"

static FILE *INIFile = NULL;
static char *INIFileName = NULL;
static char *INISectionName = NULL;
static long int SectionOffset;

static BOOL has_ini_section(FILE *, const char *);

char *get_ini_parameter_value_as_string(const char *ini_filename, const char *section_name, const char *parameter_name)
{
	static char line[MAXLINE];
	char *p, *retp = NULL;
	int len;

	if ((INIFile == NULL) || (INIFileName == NULL) || (strcmp(INIFileName, ini_filename) != 0))
	{
		if (INIFile != NULL)
			fclose(INIFile);
		if (INIFileName != NULL)
		{ 
			free(INIFileName); 
			INIFileName = NULL; 
		}
		if (INISectionName != NULL)
		{ 
			free(INISectionName); 
			INISectionName = NULL; 
		}
		INIFile = fopen(ini_filename, "r");
		if (INIFile == NULL)
			return NULL;

		INIFileName = malloc(strlen(ini_filename) + 1);
		if (INIFileName != NULL)
			strcpy(INIFileName, ini_filename);
	}

	if ((INISectionName != NULL) && (strcmp(INISectionName, section_name) == 0))
		fseek(INIFile, SectionOffset, SEEK_SET);
	else	
	{
		if(INISectionName != NULL)
		{ 
			free(INISectionName); 
			INISectionName = NULL; 
		}
		rewind(INIFile);
		if (!has_ini_section(INIFile, section_name))
			return NULL;
		SectionOffset = ftell(INIFile);

		INISectionName = malloc(strlen(section_name) + 1);
		if (INISectionName != NULL)
			strcpy(INISectionName, section_name);
	}

	/* search for parameter */
	len = strlen(parameter_name);
	while (fgets(line, MAXLINE, INIFile) != NULL)
	{
		if (*line == '[')
			break;
		if ((strncmp(line, parameter_name, len) == 0) && (line[len] == '='))
		{
			retp = &line[len+1];
			if((p = strrchr(retp, '\n')) != NULL)
				*p = '\0';
			break;
		}
	}

	return retp;
}

static BOOL has_ini_section(FILE *fp, const char *sect)
{
	char line[MAXLINE];
	int len = strlen(sect);

	while(fgets(line, MAXLINE, fp) != NULL)
	{
		if(*line != '[')
			continue;
		if(strncmp(&line[1], sect, len) == 0 &&	line[1+len] == ']')
		return TRUE;	/* found it */
	}

	return FALSE;
}
