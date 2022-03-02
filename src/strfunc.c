/**
 * Модуль сервисных функций
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.2.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include <iconv.h>
#include <ctype.h>

#include "strfunc.h"

// ---------------------- Функции управления регистром строк ----------------------------
/**
*   Привести строку к верхнему регистру
*/
char *str_upper(char *str)
{
    char *str_begin = str;

    while ((*str = (char) toupper(*str)))
        str++;
    return str_begin;
}

/**
*   Привести строку к нижнему регистру
*/
char *str_lower(char *str)
{
    char *str_begin = str;
    while ((*str = (char) tolower(*str))) 
        str++;
    return str_begin;
}

/**
*   
*   Перевод латинских символов строки к верхнему регистру
*/
char *str_upper_lat(char *str)
{
    char *p = str;
    while (*p)
    {
        if(*p >= 'a' && *p <= 'z')
            *p = toupper(*p);
        p++;
    }
    return str;
}

/**
*   
*   Перевод латинских символов строки к нижнему регистру
*/
char *str_lower_lat(char *str)
{
    char *p = str;
    while (*p)
    {
        if(*p >= 'A' && *p <= 'Z')
            *p = tolower(*p);
        p++;
    }
    return str;
}

// --------------- Функции удаления символов из строк ---------------------------
/**
*   Удаление начальных и завершающих пробелов из строки
*   do_free: Освободить автоматически память после использования?
*   По умолчанию do_free=FALSE.
*   В языке <C> нет возможности задать значение по умолчанию аргумента функции.
*/
char *str_trim(char *str)
{
    str = str_trim_begin(str);
    str = str_trim_end(str);
    return str;
}


/**
*   Удаление начальных пробелов из строки
*/
char *str_trim_begin(char *str)
{
    char *str_begin = str;

    if (str != NULL)
        while (isspace(*str))
            str++;

    memmove(str_begin, str, strlen(str) + 1);
    return str_begin;
}

/**
*   Удаление завершающих пробелов из строки
*/
char *str_trim_end(char *str)
{
    char *end = str + strlen(str);

    while ((end != str) && isspace(*(end-1)))
        --end;
    str[end - str] = '\0';

    return str;
}

// ------------------ Функции замен в строках ---------------------------

/**
*   Заменить символ с номером char_index на new_char в строке
*/
char *str_replace_char_idx(char *str, unsigned int char_index, char new_char)
{
    unsigned int len = strlen(str);
    unsigned int i = 0;

    if (char_index < 0 || char_index >= len)
        return str;

    for (i = 0; i < len; i++)
    {
        if (i == char_index)
        {
            *(str + i) = new_char;
            break;
        }
    }
    return str;
}

/**
*   Произвести замену в строке
*/
char *create_str_replace(char *str, const char *from, const char *to)
{
    char *ret = NULL;
    char *r = NULL;
    const char *p = NULL;
    const char *q = NULL;
    size_t oldlen = strlen(from);
    size_t count, retlen, newlen = strlen(to);

    if (oldlen != newlen)
    {
        for (count = 0, p = str; (q = strstr(p, from)) != NULL; p = q + oldlen)
            count++;
        /* this is undefined if p - str > PTRDIFF_MAX */
        retlen = p - str + strlen(p) + count * (newlen - oldlen);
    }
    else
        retlen = strlen(str);

    if ((ret = (char *) malloc(retlen + 1)) == NULL)
    {
        printf("Memory allocation error\n");
        return NULL;
    }

    for (r = ret, p = str; (q = strstr(p, from)) != NULL; p = q + oldlen)
    {
        /* this is undefined if q - p > PTRDIFF_MAX */
        ptrdiff_t l = q - p;
        memcpy(r, p, l);
        r += l;
        memcpy(r, to, newlen);
        r += newlen;
    }
    strcpy(r, p);
    return ret;
}

/**
*   Произвести все замены в строке
*/

char *create_str_replace_all(char *src, const nix_search_replace_t *replaces)
{
    char *ret = src;
    char *prev = NULL;
    int i = 0;

    for(i = 0; (replaces + i)->search; i++)
    {
        ret = create_str_replace(ret, (replaces + i)->search, (replaces + i)->replace);
        if (prev != NULL)
        {
            destroy_and_null_str(prev);
            prev = ret;
        }
    }

    return ret;
}


// ------------------ Функции работы с кодировками ---------------------------

/**
*   Перевод строки в UTF-8 кодировку
*/
int to_utf8(const char *from, char *to, const char *codepage)
{
    if (strcmp(codepage, "UTF-8") ==0)
        return from;

    size_t length_from, length_to;
    int ret = 0;
    iconv_t d = iconv_open("UTF-8", codepage);

    length_from = strlen(from);
    length_to = 2 * length_from;
    ret = iconv(d, &from, &length_from, &to, &length_to);
    iconv_close(d);
    return ret;
}

/**
*   Создать строку в конировке UTF-8 из строки в кодировки CP1251
*/
char *create_utf8_from_cp1251(const char *from)
{
    char *result = NULL;
    int length;

    if (from != NULL)
    {
        result = (char *)calloc(strlen(from) * 2 + 1, sizeof(char));
        length = to_utf8(from, result, "CP1251");
    }

    return result;
}

/**
*   Создать строку в конировке UTF-8 из строки в кодировки CP866
*/
char *create_utf8_from_cp866(const char *from)
{
    char *result = NULL;
    int length;

    if (from != NULL)
    {
        result = (char *)calloc(strlen(from) * 2 + 1, sizeof(char));
        length = to_utf8(from, result, "CP866");
    }

    return result;
}


/**
*   Создать строку, перекодированную из одной кодировки в другую
*/
char *create_str_encoding(const char *src, const char *src_codepage, const char *dst_codepage)
{
    // Привести к верхнему регистру для корректной проверки
    src_codepage = str_upper_lat(src_codepage);
    dst_codepage = str_upper_lat(dst_codepage);
    
    if ( src_codepage == NULL )
        printf("Not define source codepage. The default is UTF-8\n");
    else if ( dst_codepage == NULL )
        printf("Not define destination codepage. The default is UTF-8\n");
    else if ( (strcmp(src_codepage, "CP866") == 0) && (strcmp(dst_codepage, "UTF-8") == 0) )
        return create_utf8_from_cp866(src);
    else if ( (strcmp(src_codepage, "CP1251") == 0) && (strcmp(dst_codepage, "UTF-8") == 0) )
        return create_utf8_from_cp1251(src);
    else
        printf("Not supported encoding <%s> -> <%s>", src_codepage, dst_codepage);
    return NULL;
}


// ---------------------- Функции удаления строк из памяти ----------------------------

/**
*   Удалить строку из памяти и присвоить NULL
*/
BOOL destroy_and_null_str(char *str)
{
    if (str != NULL)
    {
        free(str);
        str = NULL;
        return TRUE;
    }
    return FALSE;
}

/**
*   Проверка на пустую строку
*/
BOOL is_str_empty(const char *str)
{
    int len = 0;

    if (str == NULL)
        return TRUE;

    len = strlen(str);
    if (len > 0)
        return FALSE;
    else
        return TRUE;
}

// ---------------------- Функции форматированного преобразования строк ----------------------------

/**
*   Форматированный вывод в строку
*/
char *str_printf(char *str, const char *fmt, ...)
{
    char buffer[MAX_STR];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    strcpy(str, buffer);

    va_end(ap);
    return str;
}

/**
*   Форматированный вывод в новую строку
*/
char *create_str_printf(const char *fmt, ...)
{
    char *str = NULL;
    char buffer[MAX_STR];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    str = (char *) calloc(strlen(buffer)+1, sizeof(char));
    strcpy(str, buffer);

    va_end(ap);
    return str;
}

// ---------------------- Функции работы с подстроками ----------------------------
/**
*   It returns a pointer to the substring
*/
char *create_substr(const char *str, unsigned int position, unsigned int length)
{
    char *ret = NULL;
    unsigned int c = 0;

    if ((position + length) > strlen(str))
        length = strlen(str) - position;

    ret = (char *) calloc(length + 1, sizeof(char));

    if (ret == NULL)
    {
        printf("Unable to allocate memory\n");
        return NULL;
    }

    for (c = 0 ; c < length ; c++)
        *(ret + c) = (char) str[position + c];

    *(ret + c) = '\0';

    return ret;
}

/**
*   Взять length символов с начала строки.
*/
char *create_str_begin(const char *str, int length)
{
    char *ret = create_substr(str, 0, length);
    return ret;
}


/**
*   Взять length символов с конца строки.
*/
char *create_str_end(const char *str, int length)
{
    int str_len = strlen(str);
    char *ret = create_substr(str, str_len - length, str_len);
    return ret;
}

/**
*   Создать копию строки. Аналог strdup. 
*/
char *create_str_clone(const char *str)
{
    size_t len;
    char *clone = NULL;

    if (str == NULL)
        return NULL;

    len = strlen(str) + 1;
    clone = (char *) calloc(len, sizeof(char));

    if (clone)
        memcpy(clone, str, len);
    else
        printf("Memory allocation error\n");

    return clone;
}

/**
 * Скопировать строку в другую с ограничением длины
 *
 */
BOOL str_copy_limit(const char *src_str, char *dst_str, unsigned int max_len)
{
    if ((src_str != NULL) || (dst_str != NULL))
    {
        unsigned int src_len = strlen(src_str);
        if (src_len < max_len)
		{
            strcpy(dst_str, src_str);
		}
        else
        {
            char *limit_str = create_str_begin(src_str, max_len);
            strcpy(dst_str, limit_str);
            destroy_and_null_str(limit_str);
        }

        return TRUE;
    }
    return FALSE;
}
