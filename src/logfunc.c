/**
 * Модуль функций записи в лог
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.3.1
 */

#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "toolfunc.h"
#include "logfunc.h"
#include "strfunc.h"
#include "filefunc.h"

static nix_log_t Log;

char DefaultLogFileName[] = LOG_FILENAME;     /**< Имя файла лога по умолчанию*/

/**
* Текущее время-дата
*/
char CurrentDateTime[128];

char *get_current_datetime()
{
    CurrentDateTime[0] = 0;
    time_t loc_time;
    time(&loc_time);

    struct tm *today = localtime(&loc_time);
    strftime(CurrentDateTime, 128, "%d/%m/%y (%H:%M:%S)", today);

    return CurrentDateTime;
}

static char *get_log_filename()
{
    char *profile_path = get_profile_path();
    char *log_filename = (char *)calloc(strlen(profile_path) + strlen(DefaultLogFileName) + 1, sizeof(char));

    strcpy(log_filename, profile_path);
    strcat(log_filename, DefaultLogFileName);

    destroy_and_null_str(profile_path);

    return log_filename;
}

/**
*  Открыть лог для записи
*  log_filename - Имя файла лога
*       Если NULL, то берется имя по умолчанию
*/
nix_log_t *open_log(char *log_filename)
{
    if (log_filename == NULL)
        log_filename = get_log_filename();

    Log.out = NULL;
    Log.is_new = FALSE;

    Log.out = fopen(log_filename, "a");
    fprintf(Log.out, "[START LOG] %s - - - - - - - - - - - - - - - - - - - - -\n", get_current_datetime());

    destroy_and_null_str(log_filename);

    return &Log;
}

BOOL close_log(nix_log_t *log)
{
    if (log == NULL)
        log = &Log;

    if (log->out)
    {
        fprintf(log->out, "[STOP LOG] %s - - - - - - - - - - - - - - - - - - - - -\n", get_current_datetime());
        fclose(log->out);
        log->out = NULL;
        return TRUE;
    }
    return FALSE;
}

BOOL delete_log(char *log_filename)
{
    if (log_filename == NULL)
        log_filename = get_log_filename();

    close_log(NULL);
    return del_file(log_filename);
}

/**
* Добавить строчку в лог
*/
BOOL add_log_line(char *fmt, ...)
{
    BOOL result;
    char buffer[MAX_LOG_MSG];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    result = print_log_color_line(CYAN_COLOR_TEXT, buffer);

    va_end(ap);
    return result;
}

/**
* Вывести информационную строку
*/
BOOL log_info(char *fmt, ...)
{
    BOOL result;
    char buffer[MAX_LOG_MSG];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    result = print_log_color_line(GREEN_COLOR_TEXT, buffer);

    va_end(ap);
    return result;
}

/**
* Сообщение об ошибке
*/
BOOL log_err(char *fmt, ...)
{
    BOOL result;
    char buffer[MAX_LOG_MSG];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    result = print_log_color_line(RED_COLOR_TEXT, buffer);

    va_end(ap);
    return result;
}

/**
* Предупреждение
*/
BOOL log_warning(char *fmt, ...)
{
    BOOL result;
    char buffer[MAX_LOG_MSG];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    result = print_log_color_line(YELLOW_COLOR_TEXT, buffer);

    va_end(ap);
    return result;
}

BOOL print_log_color_line(unsigned int color, char *fmt, ...)
{
    if (Log.out)
    {
        va_list argptr;
        va_start(argptr, fmt);

        char msg[MAX_LOG_MSG];
        vsnprintf(msg, sizeof(msg), fmt, argptr);
        va_end(argptr);

        // Сигнатуру сообщения определяем по цвету
        char signature[10];
        if (color == CYAN_COLOR_TEXT)
            strcpy(signature, "DEBUG:");
        else if (color == RED_COLOR_TEXT)
            strcpy(signature, "ERROR:");
        else if (color == YELLOW_COLOR_TEXT)
            strcpy(signature, "WARNING:");
        else
            strcpy(signature, "");

        fprintf(Log.out, "    %s %s %s\n", get_current_datetime(), signature, msg);
        print_color_txt(color, "%s %s %s\n", get_current_datetime(), signature, msg);
        print_color_txt(NORMAL_COLOR_TEXT, "");
        fflush(Log.out);
        return TRUE;
    }
    return FALSE;
}

/**
 * Печать результата тестирования функции
 *
 * @param verification
 * @param fmt
 * @return BOOL
 */
BOOL print_test(BOOL verification, char *fmt, ...)
{
    char buffer[MAX_LOG_MSG];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);

    print_color_txt(CYAN_COLOR_TEXT, buffer);

    if (verification)
        print_color_txt(GREEN_COLOR_TEXT, "\tOK\n");
    else
        print_color_txt(RED_COLOR_TEXT, "\tFAIL\n");

    print_color_txt(NORMAL_COLOR_TEXT, "----------------------------------------------------------------------------------------------\n");

    va_end(ap);

    return TRUE;
}
