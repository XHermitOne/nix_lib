/*  sllist.c - source for single linked list lib
 *
 *  SLLIST - Single-Linked List Library
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

#include "sllist.h"


int insert_single_linked_list_item(nix_single_linked_list_t **item, int tag, void *object, size_t size)
{
    nix_single_linked_list_t *new_item = NULL;
    int result = SL_SUCCESS;

    assert(item != NULL);

    if(size > 0)
    {
        new_item = malloc(sizeof *new_item);
        if(new_item != NULL)
        {
            new_item->tag = tag;
            new_item->size = size;
            new_item->object = malloc(size);

            if(new_item->object != NULL)
            {
                memcpy(new_item->object, object, size);
                /* Handle empty list */
                if (*item == NULL)
                {
                    new_item->next = NULL;
                    *item = new_item;
                }
                else /* Insert just after current item */
                {
                    new_item->next = (*item)->next;
                    (*item)->next = new_item;
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


int add_first_single_linked_list_item(nix_single_linked_list_t **item, int tag, void *object, size_t size)
{
    int result = SL_SUCCESS;
    nix_single_linked_list_t *p = NULL;

    assert(item != NULL);

    result = insert_single_linked_list_item(&p, tag, object, size);
    if (result == SL_SUCCESS)
    {
        p->next = *item;
        *item = p;
    }

    return result;
}


int add_last_single_linked_list_item(nix_single_linked_list_t **item, int tag, void *object, size_t size)
{
    int result = SL_SUCCESS;
    nix_single_linked_list_t *end_seeker;

    assert(item != NULL);

    if (*item == NULL)
    {
        result = insert_single_linked_list_item(item, tag, object, size);
    }
    else
    {
        end_seeker = *item;
        while(end_seeker->next != NULL)
        {
            end_seeker = end_seeker->next;
        }
        result = insert_single_linked_list_item(&end_seeker, tag, object, size);
    }

    return result;
}


int update_single_linked_list_item(nix_single_linked_list_t *item, int new_tag, void *new_object, size_t new_size)
{
    int result = SL_SUCCESS;
    void *p;
  
    if(new_size > 0)
    {
        p = realloc(item->object, new_size);
        if(p != NULL)
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

    if(item != NULL)
    {
        if(tag != NULL)
        {
            *tag = item->tag;
        }
        if(size != NULL)
        {
            *size = item->size;
        }
        p = item->object;
    }

    return p;
}


nix_single_linked_list_t *delete_single_linked_list_item(nix_single_linked_list_t *item)
{
  SLLIST *NextNode = NULL;

  if(Item != NULL)
  {
    NextNode = Item->Next;

    if(Item->Object != NULL)
    {
      free(Item->Object);
    }
    free(Item);
  }

  return NextNode;
}


void delete_next_single_linked_list_item(nix_single_linked_list_t *item)
{
    if(item != NULL && item->next != NULL)
    {
        item->next = delete_single_linked_list_item(item->next);
    }
}


void destroy_single_linked_list(nix_single_linked_list_t **list)
{
    nix_single_linked_list_t *next;

    if(*list != NULL)
    {
        next = *list;
        do
        {
            next = delete_single_linked_list_item(next);
        } while(next != NULL);
        *list = NULL;
    }
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
        while ((next = get_next_single_linked_list_item(next)) != NULL)
            ++items;
    }

    return items;
}

/* end of sllist.c */
