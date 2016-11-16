#include <fcgi_stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>

#include <kc-web.h>

extern char **environ;
#define HTTP_MAX_PARAMS 1024

/* some of the HTTP variables we are interest in */
#define MAX_VARS 31
char *vars[MAX_VARS] = {
    "SCRIPT_NAME",
    "REQUEST_URI",
    "CONTENT_LENGTH",
    "DOCUMENT_ROOT",
    "GATEWAY_INTERFACE",
    "HTTP_ACCEPT",
    "HTTP_ACCEPT_ENCODING",
    "HTTP_ACCEPT_LANGUAGE",
    "HTTP_CACHE_CONTROL",
    "HTTP_CONNECTION",
    "HTTP_HOST",
    "HTTP_PRAGMA",
    "HTTP_RANGE",
    "HTTP_REFERER",
    "HTTP_TE",
    "HTTP_USER_AGENT",
    "HTTP_X_FORWARDED_FOR",
    "PATH",
    "QUERY_STRING",
    "REMOTE_ADDR",
    "REMOTE_HOST",
    "REMOTE_PORT",
    "REQUEST_METHOD",
    "SCRIPT_FILENAME",
    "SERVER_ADDR",
    "SERVER_ADMIN",
    "SERVER_NAME",
    "SERVER_PORT",
    "SERVER_PROTOCOL",
    "SERVER_SIGNATURE",
    "SERVER_SOFTWARE"
};

int main(void)
{
    //int count = 0;
    char **env;

    while (FCGI_Accept() >= 0) {
        int i;
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

        char *buffer;
        for (i = 0; i < MAX_VARS; ++i) {
            buffer = getenv(vars[i]);
            if (buffer == NULL)
                printf("%s\r\n", vars[i]);
            else
                printf("%s: %s\r\n", vars[i], buffer);
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
