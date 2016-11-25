/**
 * @file        kc-string.c
 * @brief       Implementation for all string operations
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

#include <kc-object.h>
#include <kc-string.h>
#include <kc-string_private.h>

// TODO MOT: test application
KCString kc_string_new()
{
    return kc_string_new_with_string(NULL, 1);
}

KCString kc_string_new_with_string(const kcchar *value, size_t length)
{
    KCString obj;

    obj = (KCString) kc_object_new(sizeof(struct kc_string));
    if (obj == NULL) {
        goto kc_sting_create_exit;
    }

    obj->string = (kcchar *) malloc((length + 1) * sizeof(kcchar));
    if (value != NULL) {
        memcpy(obj->string, value, length);
        obj->pos = obj->length = length;
        obj->string[length] = '\0';
    } else {
        obj->pos = obj->length = 0;
    }

  kc_sting_create_exit:
    return obj;
}
 
int kc_string_free(KCString obj)
{
    free(obj->string);
    kc_object_free((KCObject) obj);

    return 0;
}

#if 0
int kc_string_add(KCString, char *value, ...)
{
    return 0;
}

int kc_string_add_char(KCString, char value)
{
    return 0;
}

#endif

kcchar *kc_string_get_string(KCString obj)
{
    return kc_string_get_string_from_pos(obj, 0);
}

kcchar *kc_string_get_string_from_pos(KCString obj, size_t pos)
{
    kcchar *result = NULL;

    if (pos < 0 || pos >= kc_string_get_length(obj)) {
        return result;
    }

    result = obj->string;
    result += pos;

    return result;
}

kcchar *kc_string_get_string_from_current_pos(KCString obj)
{
    return kc_string_get_string_from_pos(obj, kc_string_get_pos(obj));
}

int kc_string_set_pos(KCString obj, size_t pos)
{
    if (pos < 0 || pos >= kc_string_get_length(obj)) {
        return -1;
    }

    return 0;
}

size_t kc_string_get_pos(KCString obj)
{
    return obj->pos;
}

size_t kc_string_get_length(KCString obj)
{
    return obj->length;
}
