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

#include <kc-mutex.h>
#include <kc.h>

/**
 * structure KCLinkedListItem: Structure for a list item
 */
typedef struct kc_linked_list_item {
    void *data;                         ///< Linked data
    struct kc_linked_list_item *next;   ///< Next item
} KCLinkedListItem;

/**
 * Structure KCLinkedList: Structure for a linked list
 */
typedef struct kc_linked_list {
    KCMutexItem mutex_item;             ///< Mutex item for the thread save part of the linked list
    KCLinkedListItem *items;            ///< Linked Items
    KCLinkedListItem *last;             ///< Last element in list
} KCLinkedList;

/**
 * Iterator for the linked List
 */
typedef struct kc_linked_list_iterator {
    void *data;
} KCLinkedListIterator;

/**
 * Create a new linked list
 * @return New linked list or NULL on error
 */
KCLinkedList *kc_linked_list_new();
/**
 * Free linked list, no linked element will be freed
 * @param list Linked list
 * @return 0 => successful
 */
int kc_linked_list_free(KCLinkedList *list);

/**
 * Add new element on the end of the list
 * @param list Linked list
 * @param element Data to add
 * @return 0 => successful
 */
int kc_linked_list_add(KCLinkedList *list, void *element);
/**
 * Remove first element which will found or do nothing
 * @param list Linked list
 * @param element Data to remove
 * @return >= 0 => position in array, -1 => cannot find element
 */
int kc_linked_list_remove(KCLinkedList *list, void *element);
/**
 * Clear and free the current existing list; do not free data
 * @param list Linked list
 * @return 0 => successful
 */
int kc_linked_list_clear(KCLinkedList *list);

/**
 * Get first item of the list (not thread saved)
 * @param list Linked list
 * @return First item in list
 */
KCLinkedListIterator kc_linked_list_get_first(KCLinkedList * list);
/**
 * Is this iterator the last item in the list (not thread saved)
 * @param iterator
 * @return TRUE -> is last
 */
kcbool kc_linked_list_is_last(KCLinkedListIterator iterator);
/**
 * Get next item in list (not thread saved);
 * @param iterator Current iterator
 * @return Next item in list
 */
KCLinkedListIterator kc_linked_list_get_next(KCLinkedListIterator iterator);
/**
 * Get data from the current element
 * @param element Linked list item
 * @return Pointer to data
 */
void *kc_linked_list_element_get_data(KCLinkedListIterator iterator);

#endif /* __KC_LINKED_LIST_H__ */
