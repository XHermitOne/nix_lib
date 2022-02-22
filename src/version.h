/**
* Модуль функций всё что связано с версией...
 * @author XHermit <xhermitone@gmail.com>
* @file
* @version 0.0.0.1
*/

#ifndef __VERSION_H 
#define __VERSION_H

#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

#include "ext_types.h"
#include "macros.h"

char *get_version(void);
BOOL print_version(void);
BOOL print_help(void);
BOOL print_system_info(void);


#endif /*__VERSION_H*/
