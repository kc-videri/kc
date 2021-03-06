/**
 * @file        kc-linked-list.h
 * @brief       Functions for a linked list (Header file)
 * @author      K-C Videri <kc.videri@gmail.com>
 *
 * copyright:   (C) 2016 by K-C Videri
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef __KC_LINKED_LIST_H__
#define __KC_LINKED_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <kc-mutex.h>
#include <kc.h>

// Forward declaration
struct kc_linked_list_item;
struct kc_linked_list;
/**
 * Iterator for the linked List
 */
struct kc_linked_list_iterator {
    void *data;
};

typedef struct kc_linked_list_item* KCLinkedListItem;
typedef struct kc_linked_list* KCLinkedList;
typedef struct kc_linked_list_iterator KCLinkedListIterator;

/**
 * Create a new linked list
 * @return New linked list or NULL on error
 */
KCLinkedList kc_linked_list_new();
/**
 * Free linked list, no linked element will be freed
 * @param obj Linked list
 * @return 0 => successful
 */
int kc_linked_list_free(KCLinkedList obj);

/**
 * Add new element on the end of the list
 * @param obj Linked obj
 * @param element Data to add
 * @return 0 => successful
 */
int kc_linked_list_add(KCLinkedList obj, void *element);
/**
 * Remove first element which will found or do nothing
 * @param obj Linked list
 * @param element Data to remove
 * @return >= 0 => position in array, -1 => cannot find element
 */
int kc_linked_list_remove(KCLinkedList obj, void *element);
/**
 * Clear and free the current existing list; do not free data
 * @param obj Linked list
 * @return 0 => successful
 */
int kc_linked_list_clear(KCLinkedList obj);

/**
 * Get first item of the list (not thread saved)
 * @param obj Linked list
 * @return First item in list
 */
KCLinkedListIterator kc_linked_list_item_get_first(KCLinkedList obj);
/**
 * Is this iterator the last item in the list (not thread saved)
 * @param obj Linked list
 * @param iterator
 * @return TRUE -> is last
 */
kcbool kc_linked_list_item_is_last(KCLinkedList obj,
                                   KCLinkedListIterator iterator);
/**
 * Get next item in list (not thread saved);
 * @param iterator Current iterator
 * @return Next item in list
 */
KCLinkedListIterator kc_linked_list_item_get_next(KCLinkedListIterator
                                                  iterator);
/**
 * Get data from the current element
 * @param iterator Iterator object
 * @return Pointer to data
 */
void *kc_linked_list_item_get_data(KCLinkedListIterator iterator);

#ifdef __cplusplus
}
#endif

#endif                          /* __KC_LINKED_LIST_H__ */
