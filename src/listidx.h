/**
 * Модуль поддержки индексирования списков
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */

#ifndef __LISTIDX_H 
#define __LISTIDX_H

#include <stdio.h>

#include "ext_types.h"
#include "sllist.h"
// #include "dllist.h"

typedef struct
{
    unsigned int count;
    struct nix_single_linked_list_t *list;
    struct nix_single_linked_list_t **index;
} nix_single_linked_list_index_array_t;

/**
* Создать массив индекса для односвязного списка.
*/
nix_single_linked_list_index_array_t *create_single_linked_list_index_array(nix_single_linked_list_t *list);

/**
 * Переиндексировать список
 * 
 */
BOOL reindex_single_linked_list_index_array(nix_single_linked_list_index_array_t *index_array);

/**
 * Удалить массив индекса для односвязного списка.
 */
BOOL destroy_single_linked_list_index_array(nix_single_linked_list_index_array_t *index_array, BOOL delete_list);

/**
 * Получить элемент списка по индексу через массив индекса.
 */
nix_single_linked_list_t *get_single_linked_list_index_array_item(const nix_single_linked_list_index_array_t *index_array, unsigned int index);

/**
 * Удалить элемент из списка по индексу.
 * 
 */
nix_single_linked_list_t *remove_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, unsigned int index);

/**
 * Удалить элемент списка по индексу.
 * 
 */
BOOL delete_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, unsigned int index);

/**
 * Вставить элемент в список по индексу.
 * 
 */
BOOL insert_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, unsigned int index, nix_single_linked_list_t *item);


/**
 * Добавить в конец списка элемент.
 * @return: Индекс добавленного элемента или -1 в случае ошибки
 */
int append_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, nix_single_linked_list_t *item);

#endif /* __LISTIDX_H */
