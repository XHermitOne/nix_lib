/**  
 *  Библиотека односвязного списка
 *  Оригинальный текст взят из книги 
 *  Хэзфилд Р., Кирби Л. - Искусство программирования на C - 2001
 *  Но далее модифицирован и дополнен.
 *  @version 0.0.2.1
 */

#ifndef __SLLIST_H
#define __SLLIST_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include  "ext_types.h"

#define SL_SUCCESS    0
#define SL_NO_MEM     1
#define SL_ZERO_SIZE  2


typedef struct 
{
  int tag;
  struct nix_single_linked_list_t *next;
  void *object;
  size_t size;
} nix_single_linked_list_t;

/**
* Создать новый элемент списка.
* 
*/
nix_single_linked_list_t *create_single_linked_list_item(int tag, void *object, size_t size);

/**
 *  Добавить новый элемент списка после указанного
 */
int insert_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size);

/**
 *  Добавить новый элемент в конец списка
 */
int add_last_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size);

/** 
 *  Заменить существующие данные элемента списка
 */
int update_single_linked_list_item(nix_single_linked_list_t *item, int new_tag, void *new_object, size_t new_size);

/** 
*   Получить данные элемента списка 
*/
void *get_data_single_linked_list_item(nix_single_linked_list_t *item, int *tag, size_t *size);

/** 
*   Удалить элемент списка
*   @return: Функция возвращает указатель на следующий элемент списка
*/
nix_single_linked_list_t *delete_single_linked_list_item(nix_single_linked_list_t *item);

/**
 * Удалить элемент из списка по индексу.
 * 
 * @param list Коренвой элемент списка.
 * @param index Индекс элемента списка.
 * @return nix_single_linked_list_t* 
 */
nix_single_linked_list_t *remove_single_linked_list_item(nix_single_linked_list_t *list, unsigned int index);

/** 
*   Удалить следующий элемент за указанным
*/
BOOL delete_next_single_linked_list_item(nix_single_linked_list_t *item);

/** 
 *    Удалить список из памяти
 */
BOOL destroy_single_linked_list(nix_single_linked_list_t *list);

/* 
*   Выполнить функцию func(Tag, ThisItem, Args) для каждого элемента cgbcrf
*/
int walk_single_linked_list(nix_single_linked_list_t *list, int (*func)(int, void *, void *), void *args);

/**
 *    Получить количество элементов списка
 * 
 * @param list Указатель на корневой элемент списка
 * @return unsigned int   Количество элементов списка
 */
unsigned int get_count_single_linked_list(nix_single_linked_list_t *list);

/**
 *  Получить элемент списка по индексу
 * 
 * @param list Корневой элемент списка
 * @param index Запрашиваемый индекс
 * @return nix_single_linked_list_t* Элемент списка или NULL  в случае ошибки
 */
nix_single_linked_list_t *get_single_linked_list_item(nix_single_linked_list_t *list, unsigned int index);

/**
 * Получить последний элемент списка
 * 
 * @param list Корневой элемент списка
 * @return nix_single_linked_list_t*  Последний элемент списка.
 */
nix_single_linked_list_t *get_single_linked_list_last_item(nix_single_linked_list_t *list);

/**
 * Найти элемент списка по значению тега
 * 
 * @param item Элемент списка начала поиска
 * @param tag Значение тега
 * @return nix_single_linked_list_t* Элемент списка или NULL если такой элемент не найден
 */
nix_single_linked_list_t *find_item_single_linked_list_by_tag(nix_single_linked_list_t *item, int tag);

#endif /*__SLLIST_H*/
