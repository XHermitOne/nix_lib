/**
 * Модуль функций работы со строками
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.2.1
 */

#ifndef __STRFUNC_H 
#define __STRFUNC_H

#include "ext_types.h"

#define     MAX_STR     1024
#define     STR_NULL    ((char) 0)

#define     SLOSH       '\\'
#define     SLASH       '/'
#define     DEFQUOTES   "\"'"   /**< default quote characters */
#define     CNULL       0
#define     CPNULL      0

// ---------------------- Функции управления регистром строк ----------------------------

/**
*   Привести строку к верхнему регистру
*/
char *str_upper(char *str);

/**
*   Привести строку к нижнему регистру
*/
char *str_lower(char *str);

/**
*   Перевод латинских символов строки к верхнему регистру.
*/
char *str_upper_lat(char *str);

/**
*   Перевод латинских символов строки к нижнему регистру.
*/
char *str_lower_lat(char *str);

// --------------- Функции удаления символов из строк ---------------------------

/**
*   Удаление начальных и завершающих пробелов из строки
*/
char *str_trim(char *str);

/**
*   Удаление начальных пробелов из строки
*/
char *str_trim_begin(char *str);
/**
*   Удаление завершающих пробелов из строки
*/
char *str_trim_end(char *str);

// ------------------ Функции замен в строках ---------------------------
typedef struct
{
    char *search;
    char *replace;
} nix_search_replace_t;

/**
*   Заменить символ с номером char_index на new_char в строке
*/
char *str_replace_char_idx(char *str, unsigned int char_index, char new_char);

/**
* Произвести замену в строке
*/
char *create_str_replace(char *str, const char *from, const char *to);

/**
* Произвести все замены в строке
* @param replaces Список замен. Должен заканчиваться структурой {search=NULL, replace=NULL}.
* @return Возвращает новую строку с произведенными заменами.
*/
char *create_str_replace_all(char *src, const nix_search_replace_t *replaces);

// ------------------ Функции работы с кодировками ---------------------------
#define     DEFAULT_CODEPAGE    "UTF-8"     /* Кодовая страница, используемая по умолчанию */

/**
*   Перевод строки в UTF-8 кодировку
*/
int to_utf8(const char *from, char *to, const char *codepage);

/**
*   Создать строку в конировке UTF-8 из строки в кодировки CP1251
*/
char *create_utf8_from_cp1251(const char *from);

/**
*   Создать строку в конировке UTF-8 из строки в кодировки CP866
*/
char *create_utf8_from_cp866(const char *from);

/**
*   Создать строку, перекодированную из одной кодировки в другую
*/
char *create_str_encoding(const char *src, const char *src_codepage, const char *dst_codepage);

// ---------------------- Функции удаления строк из памяти ----------------------------

/**
*   Удалить строку из памяти и присвоить NULL
*/
BOOL destroy_and_null_str(char *str);

/**
* Проверка на пустую строку
*/
BOOL is_str_empty(const char *str);

// ---------------------- Функции форматированного преобразования строк ----------------------------

/**
*   Форматированный вывод в строку
*/
char *str_printf(char *str, const char *fmt, ...);

/**
*   Форматированный вывод в новую строку
*/
char *create_str_printf(const char *fmt, ...);

// ---------------------- Функции работы с подстроками ----------------------------
/**
*   It returns a pointer to the substring
*/
char *create_substr(const char *str, unsigned int position, unsigned int length);

/**
*   Взять length символов с начала строки.
*/
char *create_str_begin(const char *str, int length);

/**
*   Взять length символов с конца строки.
*/
char *create_str_end(const char *str, int length);

/**
*   Создать копию строки. Аналог strdup. 
*/
char *create_str_clone(const char *str);

/**
 * Скопировать строку в другую с ограничением длины
 * 
 */
BOOL str_copy_limit(const char *src_str, char *dst_str, unsigned int max_len);

#endif /*__STRFUNC_H*/
