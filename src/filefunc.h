/**
 * Модуль функций работы с файлами
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */

#ifndef __FILEFUNC_H
#define __FILEFUNC_H

#include <stdio.h>
#include <fcntl.h> /* O_RDONLY */
#include <sys/types.h>
#include <sys/statvfs.h>
#include <sys/param.h> /* MAXPATHLEN */

#include "macros.h"
#include "logfunc.h"
#include "toolfunc.h"

char *get_home_path(void);

BOOL exists_dir(char *path);
int mkpath(const char *path, mode_t mode);

BOOL exists_file(char *filename);
BOOL del_file(char *filename);

/**
 *   Нормализация пути
 */
char *create_norm_path(char *src, size_t src_len);

/**
 *   Конвертация представления пути из dos(C:\\path\\) в unix(C:/path/)
 */
char *create_dos_to_unix_path(char *src);

/**
 *   Поменять расширение в имени файла
 */
char *create_change_filename_ext(char *filename, const char *new_ext);

/**
 *   Проверка на то же самый файл
 */
BOOL is_same_file(const char *filename1, const char *filename2);

/**
 * Путь к папке профиля
 */
char *get_profile_path(void);

#endif /*__FILEFUNC_H*/
