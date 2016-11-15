/**
 * @file        kc-linked-list.c
 * @brief       Functions for a linked list (Implementation)
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

#include <stdlib.h>
#include <stdio.h>

#include <kc.h>
#include <kc-object.h>
#include <kc-linked-list.h>
#include <kc-linked-list_private.h>
#include <kc-mutex.h>

KCLinkedList kc_linked_list_new()
{
    KCLinkedList obj;

    obj = (KCLinkedList) kc_object_new(sizeof(struct kc_linked_list));
    if (obj != NULL) {
        if (kc_mutex_item_init((KCMutexItem) obj) != 0) {
            goto new_error;

        }
        obj->items = NULL;
        obj->last = NULL;
    }

    return obj;

  new_error:
    kc_object_free((KCObject) obj);
    return NULL;
}

int kc_linked_list_free(KCLinkedList obj)
{
    int retval;

    kc_linked_list_clear(obj);

    retval = kc_mutex_item_unlock((KCMutexItem) obj);

    return retval;
}

int kc_linked_list_add(KCLinkedList obj, void *element)
{
    int retval = 0;
    kc_mutex_item_lock((KCMutexItem) obj);

    // Initialise list if not exists
    if (obj->last == NULL) {
        obj->items = (KCLinkedListItem) kc_object_new(sizeof(KCLinkedListItem));
        if (obj->items == NULL) {
            retval = -1;
            goto add_error;
        }
        obj->last = obj->items;
    } else {
        obj->last->next =
            (KCLinkedListItem) kc_object_new(sizeof(KCLinkedListItem));
        if (obj->items->next == NULL) {
            retval = -1;
            goto add_error;
        }
        obj->last = obj->last->next;
    }
    obj->last->next = NULL;
    obj->last->data = element;

  add_error:
    kc_mutex_item_unlock((KCMutexItem) obj);
    return retval;
}

int kc_linked_list_remove(KCLinkedList obj, void *element)
{
    int retval;
    kcbool found_one = FALSE;
    KCLinkedListItem current, last = obj->items;
    KCLinkedListIterator iterator;

    kc_mutex_item_lock((KCMutexItem) obj);

    for (iterator = kc_linked_list_item_get_first(obj), retval = 0;
         !kc_linked_list_item_is_last(obj, iterator);
         iterator = kc_linked_list_item_get_next(iterator), retval++) {
        current = (KCLinkedListItem) iterator.data;
        if (kc_linked_list_item_get_data(iterator) == element) {
            if (((KCLinkedListItem) iterator.data)->next == NULL) {
                last->next = NULL;
            } else {
                last->next = current->next;
            }

            kc_object_free((KCObject) current);
            found_one = TRUE;

            break;
        }
        last = current;
    }

    kc_mutex_item_unlock((KCMutexItem) obj);
    if (found_one == FALSE) {
        retval = -1;
    }
    return retval;
}

int kc_linked_list_clear(KCLinkedList obj)
{
    int retval = 0;
    KCLinkedListItem current, next;

    kc_mutex_item_lock((KCMutexItem) obj);

    current = obj->items;
    while (current) {
        next = current->next;
        kc_object_free((KCObject) current);
        current = next;
    }

    kc_mutex_item_unlock((KCMutexItem) obj);

    return retval;
}

KCLinkedListIterator kc_linked_list_item_get_first(KCLinkedList obj)
{
    KCLinkedListIterator iterator;

    iterator.data = obj->items;

    return iterator;
}

KCLinkedListIterator kc_linked_list_item_get_last(KCLinkedList obj)
{
    KCLinkedListIterator iterator;

    iterator.data = obj->last;
    return iterator;

}

kcbool kc_linked_list_item_is_last(KCLinkedList obj,
                                   KCLinkedListIterator iterator)
{
    if (iterator.data == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }

}

KCLinkedListIterator kc_linked_list_item_get_next(KCLinkedListIterator
                                                  iterator)
{
    KCLinkedListIterator obj;

    obj.data = ((KCLinkedListItem) iterator.data)->next;

    return obj;
}

void *kc_linked_list_item_get_data(KCLinkedListIterator iterator)
{
    return ((KCLinkedListItem) iterator.data)->data;
}
