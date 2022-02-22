/**
* Модуль определения дополнительных типов
* @author XHermit <xhermitone@gmail.com>
* @file
* @version 0.0.0.1
*/

#ifndef __EXT_TYPES_H
#define __EXT_TYPES_H

typedef int                 BOOL;
typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

#ifndef FALSE
#define FALSE   0
#endif

#ifndef TRUE
#define TRUE    1
#endif

#ifndef NONE
#define NONE    -1
#endif

#ifndef ERROR
#define ERROR   0
#endif

#ifndef OK
#define OK      +1
#endif

#define MAX_PATH          260

typedef DWORD COLORREF;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RANDOM(a) (rand() % (a))

#endif /*__EXT_TYPES_H*/

