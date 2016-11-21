/**
 * @file        kc-web-server.c
 * @brief       Some web server cgi stuff (Implementation)
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
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <kc-object.h>
#include <kc-web-server.h>
#include <kc-web-server_private.h>
#include <kc-web_private.h>
#include <kc-string.h>

/**
 * Private variable declaration
 */

extern char **environ;

/**
 * Public function definition
 * */

KCWebServer kc_web_server_init()
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return kc_web_server_init_type(KC_WEB_CONTENT_HTML);
}

KCWebServer kc_web_server_init_type(KCWebContentType type)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWebServer obj;
    KCWebContentTypeDef content_type;
    KCString buffer;
    char **env, **key;
    kcbool found_one;
    int i;

    obj = (KCWebServer) kc_web_new(sizeof(KCWebServer));
    if (obj == NULL) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
        return NULL;
    }
    // Default settings
    obj->content_type = NULL;

    ((KCWeb) obj)->parameter = kc_linked_list_new();
    if (((KCWeb) obj)->parameter == NULL) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
        goto kc_web_server_init_failed_memory;
    }

    for (content_type = content_types;
         content_type->type != KC_WEB_CONTENT_UNDEF; content_type++) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
        if (type == content_type->type) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
            obj->content_type = content_type;
            fprintf(stderr, "%s\n", content_type->type_string); // DELETE
        }
    }
    if (obj->content_type == NULL) {
        fprintf(stderr, "%s(%d): Content type not implemented yet\n",
                __func__, __LINE__);
        goto kc_web_server_init_failed_memory;
    }
    // GET parameter
    buffer = getenv("QUERY_STRING");
    if (buffer != NULL && strlen(buffer) > 0) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
        kc_web_server_parse_query_string(obj, buffer,
                                         KC_WEB_PARAMETER_GET);
    }
    // POST parameter
    buffer = getenv("CONTENT_LENGTH");
    if (buffer != NULL) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
        size_t post_length;
        char *post_content;

        post_length = atoi(buffer);
        if (post_length != 0) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
            post_content =
                (char *) malloc((post_length + 1) * sizeof(char));
            if (post_content != NULL) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
                fgets(post_content, post_length + 1, stdin);

                kc_web_server_parse_query_string(obj, post_content,
                                                 KC_WEB_PARAMETER_POST);
            }
        }
    }
    // HTTP variables
    for (env = environ; *env; ++env) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
        if (!strncmp(*env, KC_WEB_HTTP_PREFIX, strlen(KC_WEB_HTTP_PREFIX))) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
            fprintf(stderr, "%s\n", *env);  // DELETE 
            found_one = FALSE;
            for (key = kc_web_http_keys; *key; key++) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
                if (!strncmp(*key, *env, strlen(*key))) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
                    found_one = TRUE;
                    break;
                }
            }

            if (found_one == FALSE) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
                KCWebParameter item;

                item =
                    kc_web_server_parameter_new_from_string(*env +
                                                            strlen
                                                            (KC_WEB_HTTP_PREFIX),
                                                            strlen(*env),
                                                            type);
                if (item != NULL) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
                    KCString buffer;

                    buffer = kc_web_parameter_get_key(item);
                    for (i = 0; buffer[i]; i++) {
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
                        buffer[i] = tolower(buffer[i]);
                    }
                    kc_web_parameter_list_add_item((KCWeb) obj, item);
                }
            }
        }
    }

    return obj;

  kc_web_server_init_failed_memory:
    kc_object_free((KCObject) obj);
    return NULL;
}

KCWebServer kc_web_init_from_content_type()
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWebContentType type;

    type = kc_web_server_parse_content_type();
    if (type == KC_WEB_CONTENT_UNDEF) {
        return NULL;
    }

    return kc_web_server_init_type(type);
}

KCWebServer kc_web_server_init_from_ending()
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCString buffer;
    KCWebContentType type;

    buffer = getenv("SCRIPT_NAME");
    type = kc_web_server_get_content_type_from_ending(buffer);
    if (type == KC_WEB_CONTENT_UNDEF) {
        return NULL;
    }

    return kc_web_server_init_type(type);
}

int kc_web_server_free(KCWebServer obj)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCLinkedList list;
    KCLinkedListIterator iterator;
    KCWebParameter parameter;

    list = kc_web_get_parameter_list((KCWeb) obj);
    kc_mutex_item_lock((KCMutexItem) list);
    for (iterator = kc_linked_list_item_get_first(list);
         kc_linked_list_item_is_last(list, iterator);
         iterator = kc_linked_list_item_get_next(iterator)) {
        parameter =
            (KCWebParameter) kc_linked_list_item_get_data(iterator);
        kc_web_parameter_free(parameter);
    }
    kc_mutex_item_unlock((KCMutexItem)((KCWeb) obj)->parameter);
    kc_linked_list_free(((KCWeb) obj)->parameter);

    return 0;
}

void kc_web_server_print_content_type(KCWebServer obj)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    printf("Content-type: %s\r\n\r\n",
           kc_web_server_get_content_type_string(obj));
}

int kc_web_server_print_image(KCWebServer obj, KCString file_name)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    int file;
    size_t length = 1024;
    //kc_uchar byte;
    kcuchar byte[1024];

    file = open(file_name, O_RDONLY);
    if (file == -1) {
        fprintf(stderr, "%s(%d): Cannot read file: %s (%d)\n",
                __func__, __LINE__, strerror(errno), errno);
        return errno;
    }
#if 0
    while ((length = read(file, &byte, 1)) > 0) {
        fwrite(&byte, 1, 1, stdout);
    }
#endif
    while ((length = read(file, byte, length)) > 0) {
        fwrite(&byte, length, 1, stdout);
    }

    close(file);

    return 0;
}

KCWebContentType kc_web_server_parse_content_type()
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWebContentType type = KC_WEB_CONTENT_UNDEF;
    KCString buffer;
    kcbool found_one = FALSE;
    KCWebContentTypeDef content_type;

    buffer = getenv("CONTENT_TYPE");
    if (buffer == NULL) {
        fprintf(stderr, "%s(%d): Cannot find content-type\n",
                __func__, __LINE__);
        return KC_WEB_CONTENT_TEXT;
    }

    for (content_type = content_types;
         content_type->type_string != NULL; content_type++) {
        if (!strcmp(buffer, content_type->type_string)) {
            type = content_type->type;
            found_one = TRUE;
            break;
        }
    }
    if (type == KC_WEB_CONTENT_UNDEF || found_one == FALSE) {
        fprintf(stderr, "%s(%d): Unknown content type: %s\n",
                __func__, __LINE__, buffer);
    }

    return type;
}

KCWebContentType kc_web_server_get_content_type(KCWebServer obj)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return obj->content_type->type;
}

KCString kc_web_server_get_content_type_string(KCWebServer obj)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return content_types[kc_web_server_get_content_type(obj)].type_string;
}

KCWebContentType kc_web_server_get_content_type_from_ending(KCString str)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWebContentType type = KC_WEB_CONTENT_UNDEF;
    KCString buffer;
    KCString *ending;
    KCWebContentTypeDef content_type;

    if (str == NULL) {
        return type;
    }

    buffer = rindex(str, '.');
    if (buffer == NULL || strlen(buffer) < 2) {
        fprintf(stderr, "%s(%d): Cannot find ending\n", __func__,
                __LINE__);
        return type;
    }
    buffer++;

    for (content_type = content_types;
         content_type->type != KC_WEB_CONTENT_UNDEF; content_type++) {
        for (ending = content_type->endings; *ending != NULL; ending++) {
            if (!strcmp(buffer, *ending)) {
                type = content_type->type;
            }
        }
    }
    if (type == KC_WEB_CONTENT_UNDEF) {
        fprintf(stderr, "%s(%d): Unknown content type\n", __func__,
                __LINE__);
    }

    return type;
}

KCString kc_web_server_convert_value_string(const char *value,
                                            size_t length)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    char *obj;
    size_t _length;
    size_t i, j;

    obj = kc_string_create(value, length);
    if (obj == NULL) {
        return NULL;
    }

    _length = length;

    for (i = 0; i < _length; i++) {
        switch (obj[i]) {
        case '+':
            obj[i] = ' ';
            break;
        case '%':
            if (isxdigit(obj[i + 1]) && isxdigit(obj[i + 2])) {
                char buffer[3], c;

                buffer[0] = obj[i + 1];
                buffer[1] = obj[i + 2];
                buffer[2] = '\0';

                c = (uint8_t) strtol(buffer, NULL, 16);
                obj[i] = c;
                for (j = i + 1; j < _length - 2; j++) {
                    obj[j] = obj[j + 2];
                }
                _length -= 2;
            } else {
                return NULL;
            }

            break;
        default:
            ;
            break;
        }
    }
    obj[_length] = '\0';

    return obj;
}

/**
 * Private function definition
 * */

int kc_web_server_parse_query_string(KCWebServer obj,
                                     const char *query_string,
                                     KCWebParameterType type)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    int result = 0;
    char *buffer;
    size_t string_length;
    size_t current_length;

    buffer = (char *) query_string;
    while (1) {
        KCWebParameter item;

        string_length = strlen(buffer);

        for (current_length = 0; current_length < strlen(buffer);
             current_length++) {
            if (buffer[current_length] == '&') {
                break;
            }
        }

        fprintf(stderr, "%s\n", buffer);    // DELETE 
        item =
            kc_web_server_parameter_new_from_string(buffer, current_length, type);
        if (item != NULL) {
            kc_web_parameter_list_add_item((KCWeb) obj, item);
        }

        if (current_length == string_length) {
            break;
        }

        buffer += current_length;
        buffer++;
    }

    return result;
}

KCWebParameter kc_web_server_parameter_new_from_string(KCString string,
                                                       size_t length,
                                                       KCWebParameterType type)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWebParameter obj = NULL;
    int i;

    for (i = 0; i < length; i++) {
        if (string[i] == '=') {
            break;
        }
    }

    if (i > 0) {
        obj = kc_web_parameter_new();
        if (obj == NULL) {
            return obj;
        }
        kc_web_parameter_set_type(obj, type);

        kc_web_parameter_set_key(obj, kc_string_create(string, i));

        if (i != length) {
            KCString value;

            value =
                kc_web_server_convert_value_string(string + i + 1,
                                                   length - i - 1);
            kc_web_parameter_set_value(obj, value);
        }
    }

    return obj;
}
