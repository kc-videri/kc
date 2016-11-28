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
#include <stdarg.h>

#include <kc-object.h>
#include <kc-string.h>
#include <kc-string_private.h>

#define BUFFER_LENGTH 1024

/*
 * Public function definition
 * */

// TODO MOT: test application
KCString kc_string_new()
{
    return kc_string_new_with_string_length(NULL, BUFFER_LENGTH);
}

KCString kc_string_new_with_string(const kcchar * value, ...)
{
    KCString obj;
    kcchar *buffer = NULL;
    va_list list;
    size_t length;

    va_start(list, value);
    buffer = kc_string_create_string(&length, value, list);
    va_end(list);
    if (buffer == NULL) {
        goto kc_string_new_with_string_buffer_error;
        return NULL;
    }

    obj = kc_string_new_with_string_length(value, length);
    if (obj == NULL) {
        goto kc_string_new_with_string_obj_error;
    }

    return obj;

  kc_string_new_with_string_obj_error:
    free(buffer);

  kc_string_new_with_string_buffer_error:
    return NULL;
}

KCString kc_string_new_with_string_length(const char *value, size_t length)
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
        obj->pos = 0;
        obj->length = length;
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
int kc_string_append(KCString, char *value, ...)
{
    return 0;
}

int kc_string_append_char(KCString, char value)
{
    return 0;
}

#endif

kcchar *kc_string_get_string(KCString obj)
{
    return kc_string_get_string_from_pos(obj, 0);
}

kcchar *kc_string_get_string_pointer(KCString obj)
{
    return kc_string_get_string_pointer_from_pos(obj, 0);
}

kcchar *kc_string_get_string_from_pos(KCString obj, size_t pos)
{
    kcchar *result = NULL;
    kcchar *buffer = NULL;
    size_t length;

    if (pos < 0 || pos >= kc_string_get_length(obj)) {
        return result;
    }

    buffer = obj->string;
    buffer += pos;
    length = strlen(buffer);
    fprintf(stderr, "buffer: %s %d", buffer, length); // DELETE

    result = (kcchar *)malloc((length + 1) * sizeof(kcchar));
    if (result == NULL) {
        return result;
    }
    snprintf(result, length + 1, buffer);
    fprintf(stderr, "buffer: %s %d", result, length); // DELETE

    return result;
}

kcchar *kc_string_get_string_pointer_from_pos(KCString obj, size_t pos)
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

kcchar *kc_string_get_string_pointer_from_current_pos(KCString obj)
{
    return kc_string_get_string_pointer_from_pos(obj, kc_string_get_pos(obj));
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

int kc_string_set_length(KCString obj, size_t length)
{
    obj->string = (char *) realloc(obj->string, length + 1);
    if (obj->string == NULL) {
        return -1;
    }

    obj->length = length;
    if (kc_string_get_pos(obj) > obj->length) {
        kc_string_set_pos(obj, obj->length);
    }

    return 0;
}

size_t kc_string_get_length(KCString obj)
{
    return obj->length;
}

/*
 * Private function definition
 * */

kcchar *kc_string_create_string(size_t * length, const char *str,
                                va_list list)
{
    size_t retval;
    char *result = NULL;
    kcbool do_it_again = FALSE;

    *length = BUFFER_LENGTH + 1;

    while (1) {
        result = (char *) realloc(result, *length);
        if (result == NULL) {
            fprintf(stderr, "Cannot create memory\n");
            *length = 0;
        }

        retval = vsnprintf(result, *length, str, list);
        if (do_it_again == TRUE) {
            break;
        }
        if (retval > *length) {
            *length = retval + 1;
            do_it_again = TRUE;
        } else {
            break;
        }
    }

    return result;

}
