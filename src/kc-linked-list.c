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

#include <kc.h>
#include <kc-linked-list.h>
#include <kc-mutex.h>

KCLinkedList *kc_linked_list_new()
{
    KCLinkedList *result = NULL;

    result = (KCLinkedList *) malloc(sizeof(KCLinkedList));
    if (result != NULL) {
        if (kc_mutex_item_init((KCMutexItem *) result) != 0) {
            goto new_error;

        }
        result->items = NULL;
        result->last = NULL;
    }

    return result;

  new_error:
    free(result);
    return (NULL);
}

int kc_linked_list_free(KCLinkedList * list)
{
    int retval;

    kc_linked_list_clear(list);

    retval = kc_mutex_item_unlock((KCMutexItem *) list);

    return retval;
}

int kc_linked_list_add(KCLinkedList * list, void *element)
{
    int retval = 0;
    kc_mutex_item_lock((KCMutexItem *) list);

    // Initialise list if not exists
    if (list->last == NULL) {
        list->items =
            (KCLinkedListItem *) malloc(sizeof(KCLinkedListItem));
        if (list->items == NULL) {
            retval = -1;
            goto add_error;
        }
        list->last = list->items;
    } else {
        list->last->next =
            (KCLinkedListItem *) malloc(sizeof(KCLinkedListItem));
        if (list->items->next == NULL) {
            retval = -1;
            goto add_error;
        }
        list->last = list->last->next;
    }
    list->last->next = NULL;
    list->last->data = element;

  add_error:
    kc_mutex_item_unlock((KCMutexItem *) list);
    return retval;
}

int kc_linked_list_remove(KCLinkedList * list, void *element)
{
    int retval;
    kcbool found_one = FALSE;
    KCLinkedListItem *current, *last = list->items;
    KCLinkedListIterator iterator;

    kc_mutex_item_lock((KCMutexItem *) list);

    for (iterator = kc_linked_list_get_first(list), retval = 0;
         kc_linked_list_is_last(iterator);
         iterator = kc_linked_list_get_next(iterator), retval++) {
        if (kc_linked_list_element_get_data(iterator) == element) {
            if (((KCLinkedListItem *)iterator.data)->next == NULL) {
                last->next = NULL;
            } else {
                last->next = current->next;
            }

            free(current);
            found_one = TRUE;

            break;
        }
        last = current;
    }

    kc_mutex_item_unlock((KCMutexItem *) list);
    if (found_one == FALSE) {
        retval = -1;
    }
    return retval;
}

int kc_linked_list_clear(KCLinkedList * list)
{
    int retval = 0;
    KCLinkedListItem *current, *next;

    kc_mutex_item_lock((KCMutexItem *) list);

    current = list->items;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }

    kc_mutex_item_unlock((KCMutexItem *) list);

    return retval;
}

KCLinkedListIterator kc_linked_list_get_first(KCLinkedList * list)
{
    KCLinkedListIterator iterator;

    if (list->items != NULL) {
        iterator.data = list->items;
    }

    return iterator;
}

KCLinkedListIterator kc_linked_list_get_last(KCLinkedList * list)
{
    KCLinkedListIterator iterator;

    iterator.data = list->last;
    return iterator;

}

kcbool kc_linked_list_is_last(KCLinkedListIterator iterator)
{
    if (((KCLinkedListItem *) iterator.data)->next == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }

}

KCLinkedListIterator kc_linked_list_get_next(KCLinkedListIterator item)
{
    KCLinkedListIterator iterator;

    iterator.data = ((KCLinkedListItem *) iterator.data)->next;

    return iterator;
}

void *kc_linked_list_element_get_data(KCLinkedListIterator iterator)
{
    return ((KCLinkedListItem *) iterator.data)->data;
}
