/**
 * @file        environment_test.c
 * @brief       Class to get environment variables (testing)
 * @author      K-C Videri <kc.videri@gmail.com>
 *
 * copyright:   (C) 2013 by K-C Videri
 *
 * Description : Uses shared library to print greeting
 * To run the resulting executable the LD_LIBRARY_PATH must be
 * set to ${project_loc}/kc/.libs
 * Alternatively, libtool creates a wrapper shell script in the
 * build directory of this program which can be used to run it.
 * Here the script will be called "environment".
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
#include <string.h>

#include <kc.h>
#include <kc-linked-list.h>

#define BUFFER_LENGTH 5
#define BUFFER_1 "asdf"
#define BUFFER_2 "qwer"
#define BUFFER_3 1234

void print_content(KCLinkedList list, kcbool content);

/**
 * Main function of testing environment
 */
int main(void) {
	KCLinkedList list;
	int retval, i, buffer3;
	char *buffer1, buffer2[BUFFER_LENGTH];

	buffer1 = BUFFER_1;
	memcpy(buffer2, BUFFER_2, strlen(BUFFER_2));
	buffer2[strlen(BUFFER_2)] = '\0';
    buffer3 = BUFFER_3;

	list = kc_linked_list_new();
	for (i = 0; i < 3; i++) {
        kc_linked_list_add(list, buffer1);
        kc_linked_list_add(list, buffer2);
        kc_linked_list_add(list, &buffer3);
	}
	print_content(list, TRUE);

	buffer1 = BUFFER_2;
	memcpy(buffer2, BUFFER_1, strlen(BUFFER_1));
	buffer2[strlen(BUFFER_1)] = '\0';
	buffer3 = 5678;
	print_content(list, TRUE);

	retval = 0;
	while (retval >= 0) {
        retval = kc_linked_list_remove(list, &buffer3);
        if (retval >= 0) {
            printf("Removed \"%d\" on position %d\n", buffer3, retval);
        }
	}
	print_content(list, FALSE);

	kc_linked_list_free(list);

	return (EXIT_SUCCESS);
}

void print_content(KCLinkedList list, kcbool content)
{
	KCLinkedListIterator iterator;
	int i;

	for (iterator = kc_linked_list_item_get_first(list), i = 0;
	     ! kc_linked_list_item_is_last(list, iterator);
	     iterator = kc_linked_list_item_get_next(iterator), i++) {
	    printf("%.2d: 0x%.8x: ", i, kc_linked_list_item_get_data(iterator));
	    if (content == TRUE) {
	    if ((i % 3) != 2) {
                printf("%s", (char *)kc_linked_list_item_get_data(iterator));
	    } else {
                printf("%d", *((int *)kc_linked_list_item_get_data(iterator)));
            }
	    } else {
            printf("%s", (char *)kc_linked_list_item_get_data(iterator));
	    }

	    printf("\n");
	}
	printf("\n");
}
