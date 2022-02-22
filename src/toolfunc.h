/**
 * Модуль сервисных функций
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.1.3
 */

#ifndef __TOOLFUNC_H
#define __TOOLFUNC_H

#include <stdio.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <iconv.h>
#include <math.h>
#include <locale.h>
#include <malloc.h>
#include <time.h>

#include <fcntl.h>              /* O_RDONLY */
#include <sys/types.h>
#include <sys/statvfs.h>
#include <sys/param.h>          /* MAXPATHLEN */

#include "ext_types.h"
#include "logfunc.h"
#include "strfunc.h"
// #include "main.h"

#define MAX_NUM_LEN 20

int check_parameters(const char *check, int argc, char **argv);

BOOL err_box(char *fmt,...);
BOOL print_error(char *msg);
BOOL print_message(char *message, int options);

/**
*   Прочитать файл и вернуть массив символов
*/
unsigned int load_txt_file_size(char *filename, char *result);
char *load_txt_file(char *filename);

/**
*   Выбрать максимальное/минимальное значение из 2-х
*/
double max(double a, double b);
double min(double a, double b);

char *itoa(int value, int base);
char * dtoa(double n);

/**
*   Конвертация строки в число double
*/
double str_to_double(char *value);

int bytes_to_int(BYTE *bytes);
double bytes_to_double(BYTE *bytes);

long get_now_time(void);
long time_to_long(char *buffer);
char *long_to_time(long time);

/**
*   Цвета
*/
enum nix_print_color_t {
    NORMAL_COLOR_TEXT = 0,      // normal
    RED_COLOR_TEXT,             // red
    GREEN_COLOR_TEXT,           // green
    YELLOW_COLOR_TEXT,          // yellow
    BLUE_COLOR_TEXT,            // blue
    PURPLE_COLOR_TEXT,          // purple
    CYAN_COLOR_TEXT,            // cyan
    WHITE_COLOR_TEXT,           // white
};
/**
*   Печать цветного текста
*/
void print_color_txt(unsigned int color, char *str, ...);

#endif /*__TOOLFUNC_H*/
