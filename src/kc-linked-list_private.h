/**
 * @file        kc-linked-list_private.h
 * @brief       Functions for a linked list (Private header file)
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

#ifndef __KC_LINKED_LIST_PRIVATE_H__
#define __KC_LINKED_LIST_PRIVATE_H__

#include <kc-mutex.h>
#include <kc-linked-list.h>

/**
 * structure KCLinkedListItem: Structure for a list item
 */
struct kc_linked_list_item {
    void *data;                         ///< Linked data
    KCLinkedListItem next;              ///< Next item
};

/**
 * Structure KCLinkedList: Structure for a linked list
 */
struct kc_linked_list {
    KCMutexItem mutex_item;             ///< Mutex item for the thread save part of the linked list
    KCLinkedListItem items;             ///< Linked Items
    KCLinkedListItem last;              ///< Last element in list
};

#endif /* __KC_LINKED_LIST_PRIVATE_H__ */
