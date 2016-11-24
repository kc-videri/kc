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

int *kc_string_set_pos(KCString obj, size_t pos);
kcchar *kc_string_get(KCString obj);
kcchar *kc_string_get_pos(KCString obj);
#endif
