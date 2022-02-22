/**
 * Модуль поддержки индексирования списков
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */

#ifndef __LISTIDX_H 
#define __LISTIDX_H

#include "ext_types.h"
#include "sllist.h"
#include "dllist.h"

typedef struct
{
    unsigned int count;
    struct nix_single_linked_list_t *list;
    struct nix_single_linked_list_t **index;
} nix_single_linked_list_index_array_t;

/**
* Создать массив индекса для односвязного списка.
*/
BOOL create_single_linked_list_index_array(nix_single_linked_list_t *list, nix_single_linked_list_index_array_t *index_array);

/**
 * Удалить массив индекса для односвязного списка.
 */
BOOL destroy_single_linked_list_index_array(nix_single_linked_list_index_array_t *index_array, BOOL delete_list);

/**
 * Получить элемент списка по индексу через массив индекса.
 */
nix_single_linked_list_t *get_single_linked_list_item(const nix_single_linked_list_index_array_t *index_array, unsigned int index);

typedef struct
{
    unsigned int count;
    struct nix_double_linked_list_t *list;
    struct nix_double_linked_list_t **index;
} nix_double_linked_list_index_array_t;

/**
 * Создать массив индекса для двухсвязного списка.
 */
BOOL create_double_linked_list_index_array(nix_double_linked_list_t *list, nix_double_linked_list_index_array_t **index);

/**
 * Удалить массив индекса для двухсвязного списка.
 */
BOOL destroy_double_linked_list_index_array(nix_double_linked_list_index_array_t *index_array, BOOL delete_list);

/**
 * Получить элемент списка по индексу через массив индекса.
 */
nix_double_linked_list_t *get_double_linked_list_item(const nix_double_linked_list_index_array_t *index_array, unsigned int index);

#endif /* __LISTIDX_H */
