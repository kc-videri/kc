/**
 * @file        kc-json.c
 * @brief       A simple JSON wrapper
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

#include <kc-json.h>
#include <kc-json_private.h>

/*
 * Private function definition
 * */

KCJson kc_json_new()
{ 
    KCJson obj;

    obj = (KCJson) kc_object_new(sizeof(struct kc_json));
    if (obj == NULL) {
        return obj;
    }
    obj->error_no = json_tokener_success;
    obj->error_desc = (KCString) json_tokener_error_desc(obj->error_no);
    obj->json_object = NULL;

    return obj;
}

KCJson kc_json_new_from_string(KCString json_string)
{
    KCJson obj;

    obj = kc_json_new();
    if (obj == NULL) {
        return NULL;
    }

    obj->json_object = json_tokener_parse_verbose(json_string, &obj->error_no);
    if (obj->json_object == NULL) {
        obj->error_desc =
            (KCString) json_tokener_error_desc(obj->error_no);
        fprintf(stderr, "Cannot parse content: %s (%d)\n",
                json_tokener_error_desc(obj->error_no), obj->error_no);
    }

    return obj;
}

int kc_json_free(KCJson obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to implement\n", __FILE__, __FUNCTION__, __LINE__);

    return 0;
}

int kc_json_get_error_no(KCJson obj)
{
    return obj->error_no;
}

KCString kc_json_get_error_description(KCJson obj)
{
    return obj->error_desc;
}

KCString kc_json_get_json_string(KCJson obj, kcbool nice)
{
    int flag = 0;
    if (obj->json_object == NULL) {
        return NULL;
    }

    if (nice == TRUE) {
        flag = JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY;
    }

    return (KCString)json_object_to_json_string_ext(obj->json_object, flag);
}

int kc_json_add_object(KCJson obj, const KCString key, KCJsonObject value)
{
    if (obj->json_object == NULL) {
        obj->json_object = json_object_new_object();
    }

    json_object_object_add(obj->json_object, key, value->json_object);
    kc_json_object_free_header(value);

    return 0;
}

KCJsonObject kc_json_new_string(const KCString str)
{
    KCJsonObject obj;

    obj = kc_json_object_new();
    if (obj == NULL) {
        return obj;
    }

    obj->json_object = json_object_new_string(str);
    
    return obj;
}

KCJsonObject kc_json_new_string_len(const KCString str, int len)
{
    KCJsonObject obj;

    obj = kc_json_object_new();
    if (obj == NULL) {
        return obj;
    }
    
    obj->json_object = json_object_new_string_len(str, len);

    return obj;
}

const KCString kc_json_get_string(KCJsonObject obj)
{
    return (const KCString)json_object_get_string(obj->json_object);
}

int kc_json_get_string_len(KCJsonObject obj)
{
    return json_object_get_string_len(obj->json_object);
}

/*
 * Private function definition
 * */

KCJsonObject kc_json_object_new()
{
    KCJsonObject obj;

    obj = (KCJsonObject) kc_object_new(sizeof(struct kc_json_object));
    if (obj == NULL) {
        return obj;
    }

    obj->json_object = NULL;

    return obj;
}

int kc_json_object_free(KCJsonObject obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to implement\n", __FILE__, __FUNCTION__, __LINE__);

    return 0;
}

int kc_json_object_free_header(KCJsonObject obj)
{
    kc_object_free((KCObject)obj);

    return 0;
}
