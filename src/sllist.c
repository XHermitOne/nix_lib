/**  
 *  Библиотека односвязного списка
 *  Оригинальный текст взят из книги 
 *  Хэзфилд Р., Кирби Л. - Искусство программирования на C - 2001
 *  Но далее модифицирован и дополнен.
 *  @version 0.0.2.1
 */

#include "sllist.h"

nix_single_linked_list_t *create_single_linked_list_item(int tag, void *object, size_t size)
{
    nix_single_linked_list_t *new_item = NULL;

    new_item = malloc(sizeof *new_item);
    new_item ->next = NULL;

    if (new_item != NULL)
    {
        new_item->tag = tag;
        new_item->size = size;
        new_item->object = malloc(size);

        if (new_item->object != NULL)
        {
            memcpy(new_item->object, object, size);
        }
    }
    return new_item;
}

int insert_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size)
{
    nix_single_linked_list_t *new_item = NULL;
    int result = SL_SUCCESS;

    assert(item != NULL);

    if (size > 0)
    {
        new_item = malloc(sizeof *new_item);
        if (new_item != NULL)
        {
            new_item->tag = tag;
            new_item->size = size;
            new_item->object = malloc(size);

            if (new_item->object != NULL)
            {
                memcpy(new_item->object, object, size);
                /* Handle empty list */
                if (item == NULL)
                {
                    new_item->next = NULL;
                    item = new_item;
                }
                else /* Insert just after current item */
                {
                    new_item->next = item->next;
                    item->next = new_item;
                }
            }
            else
            {
                free(new_item);
                result = SL_NO_MEM;
            }
        }
        else
        {
            result = SL_NO_MEM;
        }
    }
    else
    {
        result = SL_ZERO_SIZE;
    }

    return result;
}


int add_last_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size)
{
    int result = SL_SUCCESS;
    nix_single_linked_list_t *end_seeker = NULL;

    assert(item != NULL);

    if (item == NULL)
    {
        result = insert_single_linked_list_item(item, tag, object, size);
    }
    else
    {
        end_seeker = item;
        while (end_seeker->next != NULL)
        {
            end_seeker = end_seeker->next;
        }
        result = insert_single_linked_list_item(end_seeker, tag, object, size);
    }

    return result;
}


int update_single_linked_list_item(nix_single_linked_list_t *item, int new_tag, void *new_object, size_t new_size)
{
    int result = SL_SUCCESS;
    void *p;
  
    if (new_size > 0)
    {
        p = realloc(item->object, new_size);
        if (p != NULL)
        {
            item->object = p;
            memmove(item->object, new_object, new_size);
            item->tag = new_tag;
            item->size = new_size;
        }
        else
        {
            result = SL_NO_MEM;
        }
    }
    else
    {
        result = SL_ZERO_SIZE;
    }

    return result;
}


void *get_data_single_linked_list_item(nix_single_linked_list_t *item, int *tag, size_t *size)
{
    void *p = NULL;

    if (item != NULL)
    {
        if (tag != NULL)
        {
            *tag = item->tag;
        }
        if (size != NULL)
        {
            *size = item->size;
        }
        p = item->object;
    }

    return p;
}


nix_single_linked_list_t *delete_single_linked_list_item(nix_single_linked_list_t *item)
{
    nix_single_linked_list_t *next = NULL;

    if (item != NULL)
    {
        next = item->next;

        if (item->object != NULL)
        {
            free(item->object);
        }
        free(item);
    }

  return next;
}

nix_single_linked_list_t *remove_single_linked_list_item(nix_single_linked_list_t *list, unsigned int index)
{
    nix_single_linked_list_t *item = list;
    nix_single_linked_list_t *prev = list;

    while ((item != NULL) && (index > 0))
    {
        prev = item;
        item = item->next;
        index--;
    }
    prev->next = item->next;
    item->next = NULL;
    return item;
}


BOOL delete_next_single_linked_list_item(nix_single_linked_list_t *item)
{
    BOOL result = FALSE;

    if ((item != NULL) && (item->next != NULL))
    {
        item->next = delete_single_linked_list_item(item->next);
        result = TRUE;
    }
    return result;
}


BOOL destroy_single_linked_list(nix_single_linked_list_t *list)
{
    BOOL result;
    nix_single_linked_list_t *next = NULL;

    if (list != NULL)
    {
        next = list;
        do
        {
            next = delete_single_linked_list_item(next);
        } while(next != NULL);

        list = NULL;
        result = TRUE;
    }
    return result;
}

int walk_single_linked_list(nix_single_linked_list_t *list, int (*func)(int, void *, void *), void *args)
{
    nix_single_linked_list_t *this_item;
    int result = 0;

    for(this_item = list; (result == 0) && (this_item != NULL); this_item = this_item->next)
    {
        result = (*func)(this_item->tag, this_item->object, args);
    }

    return result;
}

unsigned int get_count_single_linked_list(nix_single_linked_list_t *list)
{
    unsigned int items = 0;
    nix_single_linked_list_t *next = list;

    if (list != NULL)
    {
        ++items;
        while ((next = next->next) != NULL)
            ++items;
    }

    return items;
}

nix_single_linked_list_t *get_single_linked_list_item(nix_single_linked_list_t *list, unsigned int index)
{
    nix_single_linked_list_t *result = NULL;

    if (index == 0)
    {
        result = list;
    }
    else
        if (list != NULL)
        {
            result = get_single_linked_list_item(list->next, index - 1);
        }

    return result;
}

nix_single_linked_list_t *get_single_linked_list_last_item(nix_single_linked_list_t *list)
{
    nix_single_linked_list_t *result = NULL;

    if (list != NULL)
        if (list->next == NULL)
            result = list;
        else
            result = get_single_linked_list_last_item(list->next);

    return result;
}

nix_single_linked_list_t *find_item_single_linked_list_by_tag(nix_single_linked_list_t *item, int tag)
{
    nix_single_linked_list_t *result = NULL;

    if (item != NULL)
    {
        if (item->tag == tag)
            result = item;
        else
            result = find_item_single_linked_list_by_tag(item->next, tag);
    }

    return result;
}


/* end of sllist.c */
