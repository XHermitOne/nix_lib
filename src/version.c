/**
* Модуль функций всё что связано с версией...
* в этом модуле будет хранится версия программы
*
* version - "MajorVersion.MinorVersion [DD.MM.YEAR]
*   MajorVersion - старший разряд версии
*   MinorVersion - младший, реально кол-во фиксов, исправленных багов в версии XX
*        смотри файлик changelog.txt
*
* @author XHermit <xhermitone@gmail.com>
* @file
* @version 0.0.0.1
*/

#include "version.h"

const int MajorVersion = MAJOR_VERSION;  /**< старший разряд версии */
const int MinorVersion = MINOR_VERSION;  /**< младший разряд версии */


static char Version[100];
char *get_version(void)
{
    char build_time[100];
    strcpy(build_time, __TIMESTAMP__);
    sprintf(Version, "v%i.%02i [%s]", MajorVersion, MinorVersion, build_time);
    return Version;
}

/**
* Вывести на экран версию программы
*/
BOOL print_version(void)
{
    printf("Version: ");
    printf(get_version());
    printf("\n");
    return TRUE;
}

static char HelpTxt[] = HELP_TEXT;

/**
* Вывести на экран помощь
*/
BOOL print_help(void)
{
    printf("Программа отображения на экране содержимого OpenGL OBJ файла: \n");
    printf(HelpTxt);
    printf("\n");
    return TRUE;
}

/**
* Вывести на экран системной информации(для выявления утечек памяти)
*/
BOOL print_system_info(void)
{
    struct sysinfo info;

    if (sysinfo(&info) != 0)
    {
        printf("sysinfo: error reading system statistics");
        return FALSE;
    }

    printf("System information:\n");
    printf("\tUptime: %ld:%ld:%ld\n", info.uptime/3600, info.uptime%3600/60, info.uptime%60);
    printf("\tTotal RAM: %ld MB\n", info.totalram/1024/1024);
    printf("\tFree RAM: %ld MB\n", (info.totalram-info.freeram)/1024/1024);
    printf("\tProcess count: %d\n", info.procs);
    return TRUE;
}
