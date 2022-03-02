/*  sllist.h - header for single linked list lib
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

#ifndef __SLLIST_H
#define __SLLIST_H

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
* Create new item
* 
*/
nix_single_linked_list_t *create_single_linked_list_item(int tag, void *object, size_t size);

/**
 *  Add new item immediately after current item 
 */
int insert_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size);

/* 
* Add item to front of list. Care: if you pass
* this function any node other than the first,
* you will get Y-branches in your list:
*
*    oldroot-->-
*               \  
*                >->-passeditem-->-->--oldnext
*               /
*    newitem-->-
*
* This would be a Bad Thing.
*/
// int add_first_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size);

/* Add new item right at the end of the list */
int add_last_single_linked_list_item(nix_single_linked_list_t *item, int tag, void *object, size_t size);

/* Replace existing data */
int update_single_linked_list_item(nix_single_linked_list_t *item, int new_tag, void *new_object, size_t new_size);

/* Retrieve data from this node */
void *get_data_single_linked_list_item(nix_single_linked_list_t *item, int *tag, size_t *size);

/** 
* Delete this item. Returns pointer to
* next item - caller's responsibility
* to maintain list integrity.
*/
nix_single_linked_list_t *delete_single_linked_list_item(nix_single_linked_list_t *item);

/** 
* Delete item immediately following
* the one passed in. List integrity
* maintained automatically.
*/
BOOL delete_next_single_linked_list_item(nix_single_linked_list_t *item);

/* Destroy the entire list */
BOOL destroy_single_linked_list(nix_single_linked_list_t *list);

/* Call func(Tag, ThisItem, Args) for each item */
int walk_single_linked_list(nix_single_linked_list_t *list, int (*func)(int, void *, void *), void *args);

unsigned int get_count_single_linked_list(nix_single_linked_list_t *list);

/**
 * Get the item single linked list by index
 * 
 * @param list 
 * @param index 
 * @return nix_single_linked_list_t* 
 */
nix_single_linked_list_t *get_item_single_linked_list(nix_single_linked_list_t *list, unsigned int index);

/**
 * Find the item single linked list by tag value
 * 
 * @param list 
 * @param index 
 * @return nix_single_linked_list_t* 
 */
nix_single_linked_list_t *find_item_single_linked_list_by_tag(nix_single_linked_list_t *item, int tag);

#endif /*__SLLIST_H*/
