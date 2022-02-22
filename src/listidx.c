/**
 * Модуль поддержки индексирования списков
 * @author XHermit <xhermitone@gmail.com>
 * @file
 * @version 0.0.0.1
 */

#include "listidx.h"

/**
 * Создать массив индекса для односвязного списка.
 */
BOOL create_single_linked_list_index_array(nix_single_linked_list_t *list, nix_single_linked_list_index_array_t *index_array)
{
    BOOL result = FALSE;

    if (list != NULL)
    {
        index_array = (nix_single_linked_list_index_array_t *) malloc(sizeof(nix_single_linked_list_index_array_t));
        index_array->list = list;
        index_array->count = get_count_single_linked_list(list);
        index_array->index = (nix_single_linked_list_t**) malloc(sizeof(nix_single_linked_list_t*) * index_array->count);

        item = list;
        i = 0;
        do
        {
            *(index_array->index + i) = item;
            item = item->next;
        } while (item != NULL);
        result = TRUE;
    }
    
    return result;
}

/**
 * Удалить массив индекса для односвязного списка.
 */
BOOL destroy_single_linked_list_index_array(nix_single_linked_list_index_array_t *index_array, BOOL delete_list)
{
    BOOL result = FALSE;

    if (index_array != NULL)
    {
        if (delete_list == TRUE)
            destroy_single_linked_list(index_array->list);

        if (index_array->index != NULL)
            free(index_array->index);

        free(index_array);
        index_array = NULL;

        result = TRUE;
    }

    return result;
}

/**
 * Получить элемент списка по индексу через массив индекса.
 */
nix_single_linked_list_t *get_single_linked_list_item(const nix_single_linked_list_index_array_t *index_array, unsigned int index)
{
    nix_single_linked_list_t *item = NULL;

    if (index_array != NULL)
        if (index < index_array->count)
            item = *(index_array->index + index);

    return item;
}

/**
 * Создать массив индекса для двухсвязного списка.
 */
BOOL create_double_linked_list_index_array(nix_double_linked_list_t *list, nix_double_linked_list_index_array_t **index)
{
    BOOL result = FALSE;

    if (list != NULL)
    {
        index_array = (nix_double_linked_list_index_array_t *)malloc(sizeof(nix_double_linked_list_index_array_t));
        index_array->list = list;
        index_array->count = get_count_double_linked_list(list);
        index_array->index = (nix_double_linked_list_t **)malloc(sizeof(nix_double_linked_list_t *) * index_array->count);

        item = list;
        i = 0;
        do
        {
            *(index_array->index + i) = item;
            item = item->next;
        } while (item != NULL);
        result = TRUE;
    }

    return result;
}

/**
 * Удалить массив индекса для двухсвязного списка.
 */
BOOL destroy_double_linked_list_index_array(nix_double_linked_list_index_array_t *index_array, BOOL delete_list)
{
    BOOL result = FALSE;
    if (index_array != NULL)
    {
        if (delete_list == TRUE)
            destroy_double_linked_list(index_array->list);

        if (index_array->index != NULL)
            free(index_array->index);

        free(index_array);
        index_array = NULL;

        result = TRUE;
    }

    return result;
}

/**
 * Получить элемент списка по индексу через массив индекса.
 */
nix_double_linked_list_t *get_double_linked_list_item(const nix_double_linked_list_index_array_t *index_array, unsigned int index)
{
    nix_double_linked_list_t *item = NULL;

    if (index_array != NULL)
        if (index < index_array->count)
            item = *(index_array->index + index);

    return item;
}
