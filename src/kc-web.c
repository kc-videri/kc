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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#if 0
#include <fcgi_stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#include <kc-web.h>
#include <kc-object.h>
#include <kc-web.h>
#include <kc-web_private.h>
#if 0
#include <kc-string.h>
#endif

/*
 * Private variable declaration
 * */

// TODO MOT: add all useful content types
struct kc_web_content_type_def content_types[] = {
//content_types = {
    {KC_WEB_CONTENT_HTML, "text/html", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_XHTML, "text/xhtml", {"xhtml", NULL}},
    {KC_WEB_CONTENT_JSON, "application/json", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/text", {"txt", NULL}},
    {KC_WEB_CONTENT_ICO, "image/x-icon", {"ico", NULL}},
    {KC_WEB_CONTENT_HTML, "application/x-www-form-urlencoded", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/xml", {"xml", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/atom+xml", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/form - data", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/alternative", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/mixed", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "application / base64 ", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "application / octet - stream ", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/plain ", {"txt", NULL}},
    {KC_WEB_CONTENT_UNDEF, "text/css ", {"css", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/javascript", {"js", NULL}},
    {KC_WEB_CONTENT_UNDEF, NULL, {NULL}}
};

/**
 * Public function definition
 * */

KCWebContentType kc_web_get_content_type(KCWeb obj)
{
    return ((KCWeb) obj)->content_type->type;
}

KCString kc_web_get_content_type_string(KCWeb obj)
{
    return content_types[kc_web_get_content_type(obj)].type_string;
}

KCLinkedList kc_web_get_parameter_list(KCWeb obj)
{
    return obj->parameter;
}

KCWebParameter kc_web_parameter_get(KCWeb obj, KCString search_string)
{
    KCLinkedList list;
    KCLinkedListIterator iterator;
    KCWebParameter parameter;

    list = kc_web_get_parameter_list(obj);
    kc_mutex_item_lock((KCMutexItem) list);
    for (iterator = kc_linked_list_item_get_first(list);
         kc_linked_list_item_is_last(list, iterator);
         iterator = kc_linked_list_item_get_next(iterator)) {
        parameter =
            (KCWebParameter) kc_linked_list_item_get_data(iterator);
        if (!strcmp(search_string, kc_web_parameter_get_key(parameter))) {
            kc_mutex_item_unlock((KCMutexItem) obj->parameter);

            return parameter;
        }
    }

    kc_mutex_item_unlock((KCMutexItem) obj->parameter);

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

KCWeb kc_web_new()
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
    KCWeb obj;

    obj = (KCWeb) kc_object_new(sizeof(KCWeb));
    if (obj == NULL) {
        fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
        return NULL;
    }
    // Default settings
    obj->parameter = kc_linked_list_new();
    if (obj->parameter == NULL) {
        fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
        goto kc_web_init_failed_memory;
    }

    return obj;

  kc_web_init_failed_memory:
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
    kc_object_free((KCObject) obj);
    return NULL;
}

KCWebContentTypeDef kc_web_get_content_type_def_from_type(KCWebContentType
                                                          type)
{
    KCWebContentTypeDef content_type;

    for (content_type = content_types;
         content_type->type != KC_WEB_CONTENT_UNDEF; content_type++) {
        if (type == content_type->type) {
            return content_type;
        }
    }

    return NULL;
}

KCWebContentTypeDef kc_web_get_content_type_def_from_string(char *str)
{
    kcbool found_one = FALSE;
    KCWebContentTypeDef content_type;

    for (content_type = content_types;
         content_type->type_string != NULL; content_type++) {
        if (!strcmp(str, content_type->type_string)) {
            found_one = TRUE;
            break;
        }
    }
    if (content_type->type == KC_WEB_CONTENT_UNDEF || found_one == FALSE) {
        fprintf(stderr, "%s(%d): Unknown content type: %s\n", __func__,
                __LINE__, str);
        content_type = NULL;
    }

    return content_type;
}

KCWebParameter kc_web_parameter_new()
{
    KCWebParameter obj;

    obj = (KCWebParameter)
        kc_object_new(sizeof(struct kc_web_parameter));
    if (obj != NULL) {
        obj->key = NULL;
        obj->value = NULL;
    }

    return obj;
}

int kc_web_parameter_free(KCWebParameter item)
{
    if (item->key != NULL) {
        free(item->key);
    }
    if (item->value != NULL) {
        free(item->value);
    }
    kc_object_free((KCObject) item);

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

int kc_web_parameter_set_type(KCWebParameter item, KCWebParameterType type)
{
    item->type = type;

    return 0;
}

int kc_web_parameter_list_add_item(KCWeb obj, KCWebParameter item)
{
    kc_linked_list_add(obj->parameter, item);

    return 0;
}
