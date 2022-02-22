/*  dllist.h
 *
 *  DLLIST - Double-Linked List Library
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

#ifndef __DLLIST_H
#define __DLLIST_H

#define DL_SUCCESS      0
#define DL_NO_MEM       1
#define DL_ZERO_SIZE    2
#define DL_NULL_POINTER 3

typedef struct 
{
    int tag;
    struct nix_double_linked_list_t *prev;
    struct nix_double_linked_list_t *next;
    void *object;
    size_t size;
} nix_double_linked_list_t;

nix_double_linked_list_t *create_double_linked_list_item(int tag, void *object, size_t size);

/* Insert existing item into list, just
 * before the item provided.
 */
int insert_before_double_linked_list_item(nix_double_linked_list_t *existing_item, nix_double_linked_list_t *new_item);

/* Insert existing item into list, just
 * after the item provided.
 */
int insert_after_double_linked_list_item(nix_double_linked_list_t *existing_item, nix_double_linked_list_t *new_item);

/* Add item at start of list */
int add_first_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size);

/* Add item at end of list */
int add_last_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size);

/* Add new item immediately after current item */
int add_after_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size);

/* Add new item immediately before current item */
int add_before_double_linked_list_item(nix_double_linked_list_t **item, int tag, void *object, size_t size);

/* Update one item */
int update_double_linked_list_item(nix_double_linked_list_t *item, int new_tag, void *new_object, size_t new_size);

/* Get a pointer to the data */
void *get_data_double_linked_list_item(nix_double_linked_list_t *item, int *tag, size_t *size);

/* Extract one item from the
 * list, without destroying it.
 */
nix_double_linked_list_t *extract_double_linked_list_item(nix_double_linked_list_t *item);

/* Delete one item in the list */
void delete_double_linked_list_item(nix_double_linked_list_t *item);

/* Exchange two items. Both must be non-NULL. */
int exchange_double_linked_list_items(nix_double_linked_list_t *item1, nix_double_linked_list_t *item2);

/* Destroy the entire list */
void destroy_double_linked_list(nix_double_linked_list_t **list);

/* List navigation functions */
nix_double_linked_list_t *get_prev_double_linked_list_item(nix_double_linked_list_t *item);
nix_double_linked_list_t *get_next_double_linked_list_item(nix_double_linked_list_t *item);
nix_double_linked_list_t *get_first_double_linked_list_item(nix_double_linked_list_t *item);
nix_double_linked_list_t *get_last_double_linked_list_item(nix_double_linked_list_t *item);

nix_double_linked_list_t *join_double_linked_list_item(nix_double_linked_list_t *left, nix_double_linked_list_t *right);

unsigned int get_count_double_linked_list(nix_double_linked_list_t *list);

/* Walk the list */
int walk_double_linked_list(nix_double_linked_list_t *list, int (*func)(int, void *, void *), void *args);

#endif /*__DLLIST_H*/
