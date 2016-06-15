/**
 * @file        kc-web.c
 * @brief       
 * @author      Michael Ott <michael@king-coder.de>
 *
 * copyright:   (C) 2016 by Michael Ott
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
#include <kc-string.h>

/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
struct kc_web_content_type {
    KCWebContentType type;      ///< Content type
    KCString type_string;       ///< String to send to define type
    KCString endings[3];        ///< String to send to define type
};

// TODO: add all useful content types
KCWebContentTypeDef content_types[] = {
    {KC_WEB_CONTENT_HTML, "text/html", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_XHTML, "text/xhtml", {"xhtml", NULL}},
    {KC_WEB_CONTENT_JSON, "application/json", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/text", {"txt", NULL}},
    {KC_WEB_CONTENT_ICO, "image/x-icon", {"ico", NULL}},
    {KC_WEB_CONTENT_UNDEF, NULL, {NULL}}
};

/**
 * Parse a received string (query, content, ...)
 * @param web Pointer to KC Web structure
 * @param query_string String to parse
 * @param length Length of the value
 * @param type Type of request
 * @return
 */
int kc_web_parse_query_string(KCWeb * web, const char *query_string,
                              KCWebRequestType type);

KCWeb *kc_web_init()
{
    return kc_web_init_type(KC_WEB_CONTENT_HTML);
}

KCWeb *kc_web_init_type(KCWebContentType type)
{
    KCWeb *result;
    KCWebContentTypeDef *content_type;

    result = (KCWeb *)malloc(sizeof(KCWeb));
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
        fprintf(stderr, "Content type not implemented yet");
        goto kc_web_init_failed_memory;
    }
    // TODO Handle POST and GET variables
    fprintf(stderr, "Handle POST and GET variables\n");  // DELETE
    return result;

  kc_web_init_failed_memory:free(result);
    return NULL;
}

KCWeb *kc_web_init_from_ending()
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

void kc_web_print_content_type(KCWeb * web)
{
    printf("Content-type: %s\r\n\r\n",
           kc_web_get_content_type_string(web));
}

int kc_web_print_image(KCWeb * web, KCString file_name)
{
    int file;
    size_t length = 1024;
    //kc_uchar byte;
    kcuchar byte[1024];

    file = open(file_name, O_RDONLY);
    if (file == -1) {
        fprintf(stderr, "Cannot read file: %s (%d)\n", strerror(errno), errno);
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

KCWebContentType kc_web_get_content_type(KCWeb * web)
{
    return web->content_type->type;
}

KCString kc_web_get_content_type_string(KCWeb * web)
{
    return content_types[kc_web_get_content_type(web)].type_string;
}

KCWebContentType kc_web_get_content_type_from_ending(KCString str)
{
    KCWebContentType type = KC_WEB_CONTENT_UNDEF;
    KCString buffer;
    KCString *ending;

    if (str == NULL) {
        return type;
    }

    buffer = rindex(str, '.');
    if (buffer == NULL || strlen(buffer) < 2) {
        fprintf(stderr, "Cannot find ending");
        return type;
    }
    buffer++;

    KCWebContentTypeDef *content_type;
    for (content_type = content_types;
         content_type->type != KC_WEB_CONTENT_UNDEF; content_type++) {
        for (ending = content_type->endings; *ending != NULL; ending++) {
            if (!strcmp(buffer, *ending)) {
                type = content_type->type;
            }
        }
    }
    if (type == KC_WEB_CONTENT_UNDEF) {
        fprintf(stderr, "Unknown content type");
    }

    return type;
}

int kc_web_parse_query_string(KCWeb * web, const char *query_string,
                              KCWebRequestType type)
{
    int result = 0;
    char *buffer;
    size_t string_length;
    size_t current_length;
    int i;

    buffer = (char *) query_string;
    while (1) {
        KCWebParameter *item;

        item = kc_web_parameter_new();
        if (item == NULL) {
            return -1;
        }
        kc_web_parameter_set_type(item, type);

        string_length = strlen(buffer);

        for (current_length = 0; current_length < strlen(buffer);
             current_length++) {
            if (buffer[current_length] == '&') {
                break;
            }
        }

        for (i = 0; i < current_length; i++) {
            if (buffer[i] == '=') {
                break;
            }
        }

        if (i > 0) {
            kc_web_parameter_set_key(item, kc_string_create(buffer, i));
            if (i == current_length) {
                goto parse_query_string_error;
            }

            if (i != current_length) {
                kc_web_parameter_set_value(item,
                                           kc_web_convert_value_string
                                           (buffer + i + 1,
                                            current_length - i - 1));

            }
        }

        if (current_length == string_length) {
            break;
        }

      parse_query_string_error:buffer += current_length;
        buffer++;
    }

    return result;
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

                c = (uint8_t)strtol(buffer, NULL, 16);
                fprintf(stderr, "c: %c (%.2x)<br />\n", c, c); // DELETE
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

    return result;
}

KCWebParameter *kc_web_parameter_new()
{
    KCWebParameter *result;

    result = (KCWebParameter*)malloc(sizeof(KCWebParameter));
    if (result != NULL) {
        result->key = NULL;
        result->value = NULL;
    }

    return result;
}

int kc_web_parameter_free(KCWebParameter *item)
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

int kc_web_parameter_set_key(KCWebParameter *item, KCString key)
{
    item->key = key;

    return 0;
}

KCString kc_web_parameter_get_key(KCWebParameter *item)
{
    return item->key;
}

int kc_web_parameter_set_value(KCWebParameter *item, KCString value)
{
    item->value = value;

    return 0;
}

KCString kc_web_parameter_get_value(KCWebParameter *item)
{
    return item->value;
}

int kc_web_parameter_set_type(KCWebParameter *item, KCWebRequestType type)
{
    item->type = type;

    return 0;
}

KCWebRequestType kc_web_parameter_get_type(KCWebParameter *item)
{
    return item->type;
}
