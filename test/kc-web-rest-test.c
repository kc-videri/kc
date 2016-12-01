/**
 * @file        kc-web-rest-test.c
 * @brief       Web server fcgi test application
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

#include <fcgi_stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>

#include <kc-web-server.h>

extern char **environ;
#define HTTP_MAX_PARAMS 1024

/* some of the HTTP variables we are interest in */

int main(void)
{
    //int count = 0;
    char **env;

    while (FCGI_Accept() >= 0) {
        int i = 0;
        KCWebServer web;
        KCLinkedList list;
        KCLinkedListIterator iterator;

        //printf("Content-type: application/json\r\n\r\n");
        web = kc_web_server_new_from_type(KC_WEB_CONTENT_JSON);
        if (web == NULL) {
            printf("No web server object received");
            continue;
        }
        kc_web_server_print_content_type(web);

        printf("\r\n== DEBUG ==\r\n");
        list = kc_web_get_parameter_list((KCWeb)web);
        for (iterator = kc_linked_list_item_get_first(list);
             !kc_linked_list_item_is_last(list, iterator);
             iterator = kc_linked_list_item_get_next(iterator)) {
            KCWebParameter entry;
            KCWString buffer;
            kcchar *key, *value;
            entry =
                (KCWebParameter) kc_linked_list_item_get_data(iterator);
            
            buffer = kc_web_parameter_get_key(entry);
            key = kc_wstring_get_char_string(buffer);
            buffer = kc_web_parameter_get_value(entry);
            value = kc_wstring_get_char_string(buffer);
            printf("%02x: type: %02x; key: %-20s; value: %s\n", i++, 
                   kc_web_parameter_get_type(entry), key, value);
            free(key);
            free(value);
        }
        printf("\n");

#if 0
#endif
        printf("\r\nEnvironment:\r\n");
        for (env = environ, i = 0; *env; ++env, i++) {
            printf("%d: %s\n", i, *env);
        }
        printf("\n");
    }

    return 0;
}
