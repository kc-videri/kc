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
        KCWeb web;
        KCLinkedList list;
        KCLinkedListIterator iterator;

        web = kc_web_init_type(KC_WEB_CONTENT_JSON);
        kc_web_print_content_type(web);

        printf("\r\n== DEBUG ==\r\n");
        list = kc_web_get_parameter_list(web);
        for (iterator = kc_linked_list_item_get_first(list);
             !kc_linked_list_item_is_last(list, iterator);
             iterator = kc_linked_list_item_get_next(iterator)) {
            KCWebParameter entry;
            entry =
                (KCWebParameter) kc_linked_list_item_get_data(iterator);
            printf("%02x: type: %02x; key: %-20s; value: %s\n", i++,
                   kc_web_parameter_get_type(entry),
                   kc_web_parameter_get_key(entry),
                   kc_web_parameter_get_value(entry));
        }
        printf("\n");

        printf("\r\nEnvironment:\r\n");
        for (env = environ, i = 0; *env; ++env, i++) {
            printf("%d: %s\n", i, *env);
        }
        printf("\n");
    }

    return 0;
}
