/*  nix_double_linked_list_t.c - Double linked list library source
 *
 *  nix_double_linked_list_t - Double-Linked List Library
 *
 *  Copyright (C) 2000  Richard Heathfield
 *                      Eton Computer Systems Ltd
 *                      Macmillan Computer Publishing
 *
 *  This program is free software; you can redistribute it
 *  and/or modify it under the terms of the GNU General
 *  Public License as published by the Free Software
 *  Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will
 *  be useful, but WITHOUT ANY WARRANTY; without even the
 *  implied warranty of MERCHANTABILITY or FITNESS FOR A
 *  PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General
 *  Public License along with this program; if not, write
 *  to the Free Software Foundation, Inc., 675 Mass Ave,
 *  Cambridge, MA 02139, USA.
 *
 *  Richard Heathfield may be contacted by email at:
 *     binary@eton.powernet.co.uk
 *
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "dllist.h"


nix_double_linked_list_t *create_double_linked_list_item(int tag, void *object, size_t size)
{
    nix_double_linked_list_t *new_item;

    new_item = malloc(sizeof *new_item);
    if(new_item != NULL)
    {
        new_item->prev = new_item->next = NULL;
        new_item->tag = tag;
        new_item->size = size;
        new_item->object = malloc(size);
        if (new_item->object != NULL)
        {
            memcpy(new_item->object, object, size);
        }
        else
        {
            free(new_item);
            new_item = NULL;
        }
    }

    return new_item;
}

int insert_before_double_linked_list_item(nix_double_linked_list_t *existing_item, nix_double_linked_list_t *new_item)
{
    int result = DL_SUCCESS;

    if ((existing_item != NULL) && (new_item != NULL))
    {
        new_item->next = existing_item;
        new_item->prev = existing_item->prev;
        existing_item->prev = new_item;
        if (new_item->prev != NULL)
        {
            new_item->prev->next = new_item;
        }
    }
    else
    {
        result = DL_NULL_POINTER;
    }

    return result;
}

int insert_after_double_linked_list_item(nix_double_linked_list_t *existing_item, nix_double_linked_list_t *new_item)
{
    int result = DL_SUCCESS;

    if ((existing_item != NULL) && (new_item != NULL))
    {
        new_item->prev = existing_item;
        new_item->Next = existing_item->Next;
        existing_item->Next = new_item;
        if (new_item->Next != NULL)
        {
            new_item->Next->Prev = new_item;
        }
    }
    else
    {
        result = DL_NULL_POINTER;
    }

    return result;
}

int add_first_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size)
{
    int result = DL_SUCCESS;
    nix_double_linked_list_t *p;
    nix_double_linked_list_t *start;

    assert(item != NULL);

    p = create_double_linked_list_item(tag, object, size);

    if (p != NULL)
    {
        if (*item == NULL)
        {
            *item = p;
        }
        else
        {
            start = get_first_double_linked_list_item(*item);
            insert_before_double_linked_list_item(start, p);
        }
    }
    else
    {
        result = DL_NO_MEM;
    }

    return result;
}

int add_last_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size)
{
    int result = DL_SUCCESS;
    nix_double_linked_list_t *p;
    nix_double_linked_list_t *end;

    assert(item != NULL);

    p = create_double_linked_list_item(tag, object, size);

    if (p != NULL)
    {
        if (*item == NULL)
        {
            *item = p;
        }
        else
        {
            end = get_last_double_linked_list_item(*item);
            insert_after_double_linked_list_item(end, p);
        }
    }
    else
    {
        result = DL_NO_MEM;
    }

    return result;
}


/* Add new item immediately after current item */
int add_after_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size)
{
    int result = DL_SUCCESS;
    nix_double_linked_list_t *p;

    assert(item != NULL);

    p = create_double_linked_list_item(tag, object, size);

    if( p != NULL)
    {
        if (*item == NULL)
        {
            *item = p;
        }
        else
        {
            insert_after_double_linked_list_item(*item, p);
        }
    }
    else
    {
        result = DL_NO_MEM;
    }

    return result;
}

/* Add new item immediately before current item */
int add_before_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size)
{
    int result = DL_SUCCESS;
    nix_double_linked_list_t *p;

    assert(item != NULL);

    p = create_double_linked_list_item(tag, object, size);

    if (p != NULL)
    {
        if (*item == NULL)
        {
            *item = p;
        }
        else
        {
            insert_before_double_linked_list_item(*item, p);
        }
    }
    else
    {
        result = DL_NO_MEM;
    }

    return result;
}

int update_double_linked_list_item(nix_double_linked_list_t *item, int new_tag, void *new_object, size_t new_size)
{
    int result = DL_SUCCESS;
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
            result = DL_NO_MEM;
        }
    }
    else
    {
        result = DL_ZERO_SIZE;
    }

    return result;
}

void *get_data_double_linked_list_item(nix_double_linked_list_t *item, int *tag, size_t *size)
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

nix_double_linked_list_t *extract_double_linked_list_item(nix_double_linked_list_t *item)
{
    if (item != NULL)
    {
        if (item->prev != NULL)
        {
            item->prev->next = item->next;
        }
        if (item->next != NULL)
        {
            item->next->prev = item->prev;
        }
        item->prev = NULL;
        item->next = NULL;
    }
    return item;
}

void delete_double_linked_list_item(nix_double_linked_list_t *item)
{
    if (item != NULL)
    {
        extract_double_linked_list_item(item);

        if (item->object != NULL)
        {
            free(item->object);
        }
        free(item);
    }
}

/* Exchange two items. Both must be non-NULL. */
int exchange_doble_linked_list_items(nix_double_linked_list_t *item1, nix_double_linked_list_t *item2)
{
    int result = DL_SUCCESS;
    nix_double_linked_list_t *t0;
    nix_double_linked_list_t *t1;
    nix_double_linked_list_t *t2;
    nix_double_linked_list_t *t3;

    if ((item1 != NULL) && (item2 != NULL))
    {
        if (item1->next == item2)
        {
            extract_double_linked_list_item(item1);
            insert_after_double_linked_list_item(item2, item1);
        }
        else if (item2->next == item1)
        {
            extract_double_linked_list_item(item2);
            insert_after_double_linked_list_item(item1, item2);
        }
        else
        {
            t0 = item1->prev;
            t1 = item1->next;
            t2 = item2->prev;
            t3 = item2->next;

            extract_double_linked_list_item(item1);
            extract_double_linked_list_item(item2);

            if (t2 != NULL)
            {
                insert_after_double_linked_list_item(t2, item1);
            }
            else
            {
                insert_before_double_linked_list_item(t3, item1);
            }

            if (t0 != NULL)
            {
                insert_after_double_linked_list_item(t0, item2);
            }
            else
            {
                insert_before_double_linked_list_item(t1, item2);
            }
        }
    }
    else
    {
        result = DL_NULL_POINTER;
    }

    return result;
}

void destroy_double_linked_list(nix_double_linked_list_t **list)
{
    nix_double_linked_list_t *marker;
    nix_double_linked_list_t *prev;
    nix_double_linked_list_t *next;

    if(*list != NULL)
    {
        /* First, destroy all previous items */
        prev = (*list)->prev;
        while (prev != NULL)
        {
            marker = prev->prev;
            delete_double_linked_list_item(prev);
            prev = marker;
        }

        next = *list;
        do
        {
            marker = next->next;
            delete_double_linked_list_item(next);
            next = marker;
        } while (next != NULL);
        *list = NULL;
    }
}

nix_double_linked_list_t *get_prev_double_linked_list_item(nix_double_linked_list_t *item)
{
    if (item != NULL)
    {
        item = item->prev;
    }

    return item;
}

nix_double_linked_list_t *get_next_double_linked_list_item(nix_double_linked_list_t *item)
{
    if (item != NULL)
    {
        item = item->next;
    }

    return item;
}

nix_double_linked_list_t *get_first_double_linked_list_item(nix_double_linked_list_t *item)
{
    if (item != NULL)
    {
        while (item->prev != NULL)
        {
            item = item->prev;
        }
    }
    return item;
}

nix_double_linked_list_t *get_last_double_linked_list_item(nix_double_linked_list_t *item)
{
    if (item != NULL)
    {
        while (item->next != NULL)
        {
            item = item->next;
        }
    }
    return item;
}

nix_double_linked_list_t *join_double_linked_list_item(nix_double_linked_list_t *left, nix_double_linked_list_t *right)
{
    if ((left != NULL) && (right != NULL))
    {
        left = get_last_double_linked_list_item(left);
        right = get_first_double_linked_list_item(right);

        left->next = right;
        right->prev = left;
    }

    return get_first_double_linked_list_item(left);
}

unsigned int get_count_double_linked_list(nix_double_linked_list_t *list)
{
    unsigned int items = 0;
    nix_double_linked_list_t *prev = list;
    nix_double_linked_list_t *next = list;

    if (list != NULL)
    {
        ++items;
        while ((prev = get_prev_double_linked_list_item(prev)) != NULL)
        {
            ++items;
        }
        while ((next = get_next_double_linked_list_item(next)) != NULL)
        {
            ++items;
        }
    }

    return items;
}

int walk_double_linked_list(nix_double_linked_list_t *list, int(*func)(int, void *, void *), void *args)
{
    nix_double_linked_list_t *this_item = list;
    int result = 0;

    if (list != NULL)
    {
        for (this_item = get_first_double_linked_list_item(list); (result == 0) && (this_item != NULL); this_item = this_item->next)
        {
            result = (*func)(this_item->tag, this_item->object, args);
        }
    }
    return result;
}

/* end of nix_double_linked_list_t.c */
