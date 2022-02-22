/**
*                                    
*   Code from the book C Unleashed   
*   Macmillan, 2000                  
*   Chapter 6: Data Files            
*   Steve Summit 2000-03-17          
*                                    
*/

#ifndef __INIFUNC_H 
#define __INIFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ext_types.h"

/*
 *  This version of inifetch() differs from the one printed
 *  in the chapter in that it only opens the .ini file, and
 *  searches for the requested section, when necessary
 *  (not redundantly on each call).
 */

#define MAXLINE 1024

char * get_ini_parameter_value_as_string(const char *ini_filename, const char *section_name, const char *parameter_name);

#endif /* __INIFUNC_H */
