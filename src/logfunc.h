/**
 * Модуль функций записи в лог
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.2.1
 */

#ifndef __LOGFUNC_H 
#define __LOGFUNC_H

#include "ext_types.h"

#define MAX_LOG_MSG 1024

/**
* Менеджер лога
*/
typedef struct
{
    FILE *out;
    BOOL is_new;
} nix_log_t;


nix_log_t* open_log(char *log_filename);
BOOL close_log(nix_log_t *log);
BOOL delete_log(char *log_filename);

BOOL add_log_line(char *fmt, ...);
BOOL log_info(char *fmt, ...);
BOOL log_err(char *fmt, ...);
BOOL log_warning(char *fmt, ...);
BOOL print_log_color_line(unsigned int color, char *fmt, ...);

/**
 * Печать результата тестирования функции
 * 
 * @param verification 
 * @param fmt 
 * @return BOOL 
 */
BOOL print_test(BOOL verification, char *fmt, ...);

#endif /* __LOGFUNC_H */
