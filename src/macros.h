/**
* Модуль макросов
* @author XHermit <xhermitone@gmail.com>
* @file
* @version 0.0.0.1
*/

#ifndef __MACROS_H 
#define __MACROS_H

#define MAJOR_VERSION   1
#define MINOR_VERSION   1

#define HELP_TEXT "\n\
Параметры коммандной строки:\n\
\n\
    ./gl_view [Параметры]\n\
\n\
Параметры:\n\
\n\
    [Помощь и отладка]\n\
        --help|-h|-?        Напечатать строки помощи\n\
        --version|-v        Напечатать версию программы\n\
        --debug|-D          Включить режим отладки\n\
        --log|-L            Включить режим журналирования\n\
\n\
    [Параметры запуска]\n\
\n\
"

#define PROFILE_DIRNAME     ".starwars_duel"

#define LOG_FILENAME        "/starwars_duel.log"

#endif /*__MACROS_H*/

