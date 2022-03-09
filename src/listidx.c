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
nix_single_linked_list_index_array_t *create_single_linked_list_index_array(nix_single_linked_list_t *list)
{
    nix_single_linked_list_index_array_t *index_array = NULL;
    // nix_single_linked_list_t *item = NULL;
    // int i;

    if (list != NULL)
    {
        index_array = (nix_single_linked_list_index_array_t *) malloc(sizeof(nix_single_linked_list_index_array_t));
        index_array->index = NULL;
        index_array->count = 0;
        index_array->list = list;
        reindex_single_linked_list_index_array(index_array);
    }
    
    return index_array;
}

/**
 * Переиндексировать список
 * 
 */
BOOL reindex_single_linked_list_index_array(nix_single_linked_list_index_array_t *index_array)
{
    BOOL result = FALSE;
    nix_single_linked_list_t *item = NULL;
    int i = 0;

    if (index_array != NULL)
    {
        if (index_array->index != NULL)
        {
            free(index_array->index);
            index_array->index = NULL;
        }
        if (index_array->list != NULL)
        {
            index_array->count = get_count_single_linked_list(index_array->list);
            if (index_array->count)
                index_array->index = (nix_single_linked_list_t**) malloc(sizeof(nix_single_linked_list_t*) * index_array->count);
        }

        if (index_array->index != NULL)
        {
            item = index_array->list;
            i = 0;
            do
            {
                *(index_array->index + i) = item;
                item = item->next;
            } while (item != NULL);
        }

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
nix_single_linked_list_t *get_single_linked_list_index_array_item(const nix_single_linked_list_index_array_t *index_array, unsigned int index)
{
    nix_single_linked_list_t *item = NULL;

    if (index_array != NULL)
        if (index < index_array->count)
            item = *(index_array->index + index);

    return item;
}

/**
 * Удалить элемент из списка по индексу.
 * @return: Удаленный из списка элемент или NULL в случае ошибки
 */
nix_single_linked_list_t *remove_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, unsigned int index)
{
    nix_single_linked_list_t *item = NULL;
    unsigned int i = 0;
    
    if (index_array != NULL)
    {
        item = remove_single_linked_list_item(index_array->list, index);
        for (i = index; i < index_array->count; i++)
        {
            if (i < (index_array->count - 1))
                index_array->index[i] = index_array->index[i+1];
            else
                index_array->index[i] = NULL;
        }
        (index_array->count)--;
    }
    return item;    
}

/**
 * Удалить элемент списка по индексу.
 * 
 */
BOOL delete_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, unsigned int index)
{
    nix_single_linked_list_t *deleted_item = NULL;
    deleted_item = remove_single_linked_list_item(index_array, index);
    if (deleted_item != NULL)
    {
        free(deleted_item);
        deleted_item = NULL;
        return TRUE;
    }
    return FALSE;
}


/**
 * Вставить элемент в список по индексу.
 * 
 */
BOOL insert_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, unsigned int index, nix_single_linked_list_t *item)
{
    nix_single_linked_list_t * prev = NULL;
    nix_single_linked_list_t * next = NULL;

    if (index_array != NULL)
    {
        prev = index_array->index[index - 1];
        next = prev->next;
        prev->next = item;
        item->next = next;
        // Вставить индекс
        (index_array->count)++;
        return TRUE;
    }
    return FALSE;
}


/**
 * Добавить в конец списка элемент.
 * @return: Индекс добавленного элемента или -1 в случае ошибки
 */
int append_single_linked_list_index_array_item(nix_single_linked_list_index_array_t *index_array, nix_single_linked_list_t *item)
{
    int result = -1;
    nix_single_linked_list_t *last_item = NULL;

    if (index_array != NULL)
    {
        last_item = get_single_linked_list_last_item(index_array->list);
        if (last_item != NULL)
        {
            last_item->next = item;
            item->next = NULL;
            index_array->index = (nix_single_linked_list_t *) realloc(index_array->index, index_array->count + 1);
            index_array->index[index_array->count] = item;
            result = index_array->count;
            (index_array->count)++;            
        }
    }

    return result;
}
