/**
 * @file        kc-web.c
 * @brief       Some web stuff (Implementation)
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

#include <kc-web.h>
#include <kc-web_private.h>
#include <kc-string.h>

/**
 * Private variable declaration
 */

extern char **environ;

/**
 * Public function definition
 * */

KCWeb kc_web_init()
{
    return kc_web_init_type(KC_WEB_CONTENT_HTML);
}

KCWeb kc_web_init_type(KCWebContentType type)
{
    KCWeb result;
    KCWebContentTypeDef content_type;
    KCString buffer;
    char **env, **key;
    kcbool found_one;
    int i;

    result = (KCWeb) malloc(sizeof(struct kc_web));
    if (result == NULL) {
        return NULL;
    }
    // Default settings
    result->content_type = NULL;

    result->parameter = kc_linked_list_new();
    if (result->parameter == NULL) {
        goto kc_web_init_failed_memory;
    }

    for (content_type = content_types;
         content_type->type != KC_WEB_CONTENT_UNDEF; content_type++) {
        if (type == content_type->type) {
            result->content_type = content_type;
        }
    }
    if (result->content_type == NULL) {
        fprintf(stderr, "%s(%d): Content type not implemented yet\n",
                __func__, __LINE__);
        goto kc_web_init_failed_memory;
    }
    // GET parameter
    buffer = getenv("QUERY_STRING");
    if (buffer != NULL && strlen(buffer) > 0) {
        kc_web_parse_query_string(result, buffer, KC_WEB_PARAMETER_GET);
    }
    // POST parameter
    buffer = getenv("CONTENT_LENGTH");
    if (buffer != NULL) {
        size_t post_length;
        char *post_content;

        post_length = atoi(buffer);
        if (post_length != 0) {
            post_content =
                (char *) malloc((post_length + 1) * sizeof(char));
            if (post_content != NULL) {
                fgets(post_content, post_length + 1, stdin);

                kc_web_parse_query_string(result, post_content,
                                          KC_WEB_PARAMETER_POST);
            }
        }
    }
    // HTTP variables
    for (env = environ; *env; ++env) {
        if (!strncmp(*env, KC_WEB_HTTP_PREFIX, strlen(KC_WEB_HTTP_PREFIX))) {
            found_one = FALSE;
            for (key = kc_web_http_keys; *key; key++) {
                if (!strncmp(*key, *env, strlen(*key))) {
                    found_one = TRUE;
                    break;
                }
            }

            if (found_one == FALSE) {
                KCWebParameter item;

                item =
                    kc_web_parameter_new_from_string(*env +
                                                     strlen
                                                     (KC_WEB_HTTP_PREFIX),
                                                     strlen(*env), type);
                if (item != NULL) {
                    KCString buffer;

                    buffer = kc_web_parameter_get_key(item);
                    for (i = 0; buffer[i]; i++) {
                        buffer[i] = tolower(buffer[i]);
                    }
                    kc_web_parameter_list_add_item(result, item);
                }
            }
        }
    }

    return result;

  kc_web_init_failed_memory:
    free(result);
    return NULL;
}

KCWeb kc_web_init_from_ending()
{
    KCString buffer;
    KCWebContentType type;

    buffer = getenv("SCRIPT_NAME");
    type = kc_web_get_content_type_from_ending(buffer);
    if (type == KC_WEB_CONTENT_UNDEF) {
        return NULL;
    }

    return kc_web_init_type(type);
}

int kc_web_free(KCWeb web)
{
    KCLinkedList list;
    KCLinkedListIterator iterator;
    KCWebParameter parameter;

    list = kc_web_get_parameter_list(web);
    kc_mutex_item_lock((KCMutexItem *) list);
    for (iterator = kc_linked_list_item_get_first(list);
         kc_linked_list_item_is_last(list, iterator);
         iterator = kc_linked_list_item_get_next(iterator)) {
        parameter =
            (KCWebParameter) kc_linked_list_item_get_data(iterator);
        kc_web_parameter_free(parameter);
    }
    kc_mutex_item_unlock((KCMutexItem *) web->parameter);
    kc_linked_list_free(web->parameter);

    return 0;
}

void kc_web_print_content_type(KCWeb web)
{
    printf("Content-type: %s\r\n\r\n",
           kc_web_get_content_type_string(web));
}

int kc_web_print_image(KCWeb web, KCString file_name)
{
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

KCWebContentType kc_web_parse_content_type()
{
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

KCWebContentType kc_web_get_content_type(KCWeb web)
{
    return web->content_type->type;
}

KCString kc_web_get_content_type_string(KCWeb web)
{
    return content_types[kc_web_get_content_type(web)].type_string;
}

KCWebContentType kc_web_get_content_type_from_ending(KCString str)
{
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

KCString kc_web_convert_value_string(const char *value, size_t length)
{
    char *result;
    size_t _length;
    size_t i, j;

    result = kc_string_create(value, length);
    if (result == NULL) {
        return NULL;
    }

    _length = length;

    for (i = 0; i < _length; i++) {
        switch (result[i]) {
        case '+':
            result[i] = ' ';
            break;
        case '%':
            if (isxdigit(result[i + 1]) && isxdigit(result[i + 2])) {
                char buffer[3], c;

                buffer[0] = result[i + 1];
                buffer[1] = result[i + 2];
                buffer[2] = '\0';

                c = (uint8_t) strtol(buffer, NULL, 16);
                result[i] = c;
                for (j = i + 1; j < _length - 2; j++) {
                    result[j] = result[j + 2];
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
    result[_length] = '\0';

    return result;
}

KCLinkedList kc_web_get_parameter_list(KCWeb web)
{
    return web->parameter;
}

KCWebParameter kc_web_parameter_get(KCWeb web, KCString search_string)
{
    KCLinkedList list;
    KCLinkedListIterator iterator;
    KCWebParameter parameter;

    list = kc_web_get_parameter_list(web);
    kc_mutex_item_lock((KCMutexItem *) list);
    for (iterator = kc_linked_list_item_get_first(list);
         kc_linked_list_item_is_last(list, iterator);
         iterator = kc_linked_list_item_get_next(iterator)) {
        parameter =
            (KCWebParameter) kc_linked_list_item_get_data(iterator);
        if (!strcmp(search_string, kc_web_parameter_get_key(parameter))) {
            kc_mutex_item_unlock((KCMutexItem *) web->parameter);

            return parameter;
        }
    }

    kc_mutex_item_unlock((KCMutexItem *) web->parameter);

    return NULL;
}

KCString kc_web_parameter_get_key(KCWebParameter item)
{
    return item->key;
}

KCString kc_web_parameter_get_value(KCWebParameter item)
{
    if (item->value == NULL) {
        return "";
    } else {
        return item->value;
    }
}

KCWebParameterType kc_web_parameter_get_type(KCWebParameter item)
{
    return item->type;
}

/**
 * Private function definition
 * */

int kc_web_parse_query_string(KCWeb web,
                              const char *query_string,
                              KCWebParameterType type)
{
    int result = 0;
    char *buffer;
    size_t string_length;
    size_t current_length;
    //int i;

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

        item =
            kc_web_parameter_new_from_string(buffer, current_length, type);
        if (item != NULL) {
            kc_web_parameter_list_add_item(web, item);
        }

        if (current_length == string_length) {
            break;
        }

        buffer += current_length;
        buffer++;
    }

    return result;
}

KCWebParameter kc_web_parameter_new()
{
    KCWebParameter result;

    result = (KCWebParameter) malloc(sizeof(KCWebParameter));
    if (result != NULL) {
        result->key = NULL;
        result->value = NULL;
    }

    return result;
}

KCWebParameter kc_web_parameter_new_from_string(KCString string,
                                                 size_t length,
                                                 KCWebParameterType type)
{
    KCWebParameter result = NULL;
    int i;

    for (i = 0; i < length; i++) {
        if (string[i] == '=') {
            break;
        }
    }

    if (i > 0) {
        result = kc_web_parameter_new();
        if (result == NULL) {
            return result;
        }
        kc_web_parameter_set_type(result, type);

        kc_web_parameter_set_key(result, kc_string_create(string, i));

        if (i != length) {
            KCString value;

            value =
                kc_web_convert_value_string(string + i + 1,
                                            length - i - 1);
            kc_web_parameter_set_value(result, value);
        }
    }

    return result;
}

int kc_web_parameter_free(KCWebParameter item)
{
    if (item->key != NULL) {
        free(item->key);
    }
    if (item->value != NULL) {
        free(item->value);
    }
    free(item);

    return 0;
}

int kc_web_parameter_set_key(KCWebParameter item, KCString key)
{
    item->key = key;

    return 0;
}

int kc_web_parameter_set_value(KCWebParameter item, KCString value)
{
    item->value = value;

    return 0;
}

int kc_web_parameter_set_type(KCWebParameter item,
                              KCWebParameterType type)
{
    item->type = type;

    return 0;
}

int kc_web_parameter_list_add_item(KCWeb web, KCWebParameter item)
{
    kc_linked_list_add(web->parameter, item);

    return 0;
}
