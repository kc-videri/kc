/**
 * @file        kc-wstring.c
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
#include <kc-wstring.h>
#include <kc-wstring_private.h>

#define BUFFER_LENGTH 1024

/*
 * Public function definition
 * */

// TODO MOT: test application
KCWString kc_wstring_new()
{
    return kc_wstring_new_with_string_length(NULL, BUFFER_LENGTH);
}

KCWString kc_wstring_new_with_string(const kcchar * value, ...)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWString obj;
    kcchar *buffer = NULL;
    va_list list;
    size_t length;

    va_start(list, value);
    buffer = kc_wstring_create_string(&length, value, list);
    va_end(list);
    if (buffer == NULL) {
        goto kc_wstring_new_with_string_buffer_error;
        return NULL;
    }

    obj = kc_wstring_new_with_string_length(value, length);
    if (obj == NULL) {
        goto kc_wstring_new_with_string_obj_error;
    }

    return obj;

  kc_wstring_new_with_string_obj_error:
    free(buffer);

  kc_wstring_new_with_string_buffer_error:
    return NULL;
}

KCWString kc_wstring_new_with_wstring(const wchar_t *value, ...)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
#if 0
    KCWString obj;
    kcchar *buffer = NULL;
    va_list list;
    size_t length;

    va_start(list, value);
    buffer = kc_wstring_create_string(&length, value, list);
    va_end(list);
    if (buffer == NULL) {
        goto kc_wstring_new_with_string_buffer_error;
        return NULL;
    }

    obj = kc_wstring_new_with_string_length(value, length);
    if (obj == NULL) {
        goto kc_wstring_new_with_string_obj_error;
    }

    return obj;

  kc_wstring_new_with_string_obj_error:
    free(buffer);

  kc_wstring_new_with_string_buffer_error:
#endif 
    return NULL;
}

KCWString kc_wstring_new_with_string_length(const char *value, size_t length)
{
    KCWString obj;

    obj = kc_wstring_new_with_length(length);
    if (obj == NULL) {
        return obj;
    }

    if (value != NULL) {
        fprintf(stderr, "%s::%s(%d): // TODO MOT: to implement\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
#if 0
        memcpy(obj->string, value, length);
        obj->pos = obj->string_length = wcslen(value);
        obj->length = length;
        obj->string[length] = '\0';
#endif
    } else {
        obj->pos = obj->string_length = 0;
        obj->length = length;
    }

    return obj;
}

KCWString kc_wstring_new_with_wstring_length(const wchar_t *value, size_t length)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    KCWString obj;

    obj = kc_wstring_new_with_length(length);
    if (obj == NULL) {
        return obj;
    }

    if (value != NULL) {
        size_t len;

        len = wcslen(value);
        if (len > length) {
            len = length;
        }

        memcpy(obj->string, value, len);
        obj->pos = obj->string_length = len;
        obj->length = length;
        obj->string[len] = '\0';
    } else {
        obj->pos = obj->string_length = 0;
        obj->length = length;
    }

    return obj;
}

int kc_wstring_free(KCWString obj)
{
    free(obj->string);
    kc_object_free((KCObject) obj);

    return 0;
}

int kc_wstring_append(KCWString obj, kcwchar *value, ...)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_append_char_string(KCWString obj, kcchar *value, ...)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_append_char(KCWString obj, kcchar value)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_append_wchar(KCWString obj, kcwchar value)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_compare(KCWString string1, KCWString string2)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_compare_wchar(KCWString string1, kcwchar *string2)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_compare_char(KCWString string1, kcchar *string2)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_compare_size(KCWString string1, KCWString string2, size_t n)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

int kc_wstring_compare_size_wchar(KCWString string1, kcwchar *string2, size_t n)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return 0;
}

kcchar *kc_wstring_get_char_string(KCWString obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return kc_wstring_get_char_string_from_pos(obj, 0);
}

kcwchar *kc_wstring_get_string(KCWString obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return kc_wstring_get_string_from_pos(obj, 0);
}

kcwchar *kc_wstring_get_string_pointer(KCWString obj)
{
    return kc_wstring_get_string_pointer_from_pos(obj, 0);
}

kcchar *kc_wstring_get_char_string_from_pos(KCWString obj, size_t pos)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to implement\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 

    return NULL;
}

kcwchar *kc_wstring_get_string_from_pos(KCWString obj, size_t pos)
{
    kcwchar *result = NULL;
    kcwchar *buffer = NULL;
    size_t length;

    if (pos < 0 || pos >= kc_wstring_get_length(obj)) {
        return result;
    }

    buffer = obj->string;
    buffer += pos;
    length = wcslen(buffer);
    fprintf(stderr, "buffer: %ls %ld", buffer, length); // DELETE

    result = (kcwchar *)malloc((length + 1) * sizeof(kcwchar));
    if (result == NULL) {
        return result;
    }
    // TODO MOT: 
    //snprintf(result, length + 1, buffer);
    fprintf(stderr, "buffer: %ls %ld", result, length); // DELETE

    return result;
}

kcwchar *kc_wstring_get_string_pointer_from_pos(KCWString obj, size_t pos)
{
    kcwchar *result = NULL;

    if (pos < 0 || pos >= kc_wstring_get_length(obj)) {
        return result;
    }

    result = obj->string;
    result += pos;

    return result;
}

kcchar *kc_wstring_get_char_string_from_current_pos(KCWString obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return kc_wstring_get_char_string_from_pos(obj, kc_wstring_get_pos(obj));
}

kcwchar *kc_wstring_get_string_from_current_pos(KCWString obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return kc_wstring_get_string_from_pos(obj, kc_wstring_get_pos(obj));
}

kcwchar *kc_wstring_get_string_pointer_from_current_pos(KCWString obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return kc_wstring_get_string_pointer_from_pos(obj, kc_wstring_get_pos(obj));
}

int kc_wstring_set_pos(KCWString obj, size_t pos)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    if (pos < 0 || pos >= kc_wstring_get_length(obj)) {
        return -1;
    }

    return 0;
}

size_t kc_wstring_get_pos(KCWString obj)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    return obj->pos;
}

int kc_wstring_set_length(KCWString obj, size_t length)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
    obj->string = (kcwchar *) realloc(obj->string, length + 1);
    if (obj->string == NULL) {
        return -1;
    }

    obj->length = length;
    if (kc_wstring_get_pos(obj) > obj->length) {
        kc_wstring_set_pos(obj, obj->length);
    }

    return 0;
}

size_t kc_wstring_get_length(KCWString obj)
{
    return obj->length;
}

/*
 * Private function definition
 * */

KCWString kc_wstring_new_with_length(size_t length)
{
    KCWString obj;

    obj = (KCWString) kc_object_new(sizeof(struct kc_wstring));
    if (obj == NULL) {
        goto kc_string_new_with_string_length_exit;
    }
    obj->string = (kcwchar *) malloc((length + 1) * sizeof(kcwchar));
    if (obj->string == NULL) {
        goto kc_string_new_with_string_length_string;
    }

    return obj;

  kc_string_new_with_string_length_string:
    free(obj);
    obj = NULL;

  kc_string_new_with_string_length_exit:
    return obj;
}

kcchar *kc_wstring_create_string(size_t * length, const char *str,
                                va_list list)
{
    fprintf(stderr, "%s::%s(%d): // TODO MOT: to test\n", __FILE__, __FUNCTION__, __LINE__); // DELETE 
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

#if 0
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{

    //wchar_t string[100];
    wchar_t *umlauts = L"aäöü€¢ß诶";
    wchar_t sign = L'€';
    int string_length = wcslen(umlauts) * 3;
    char string[string_length];
    int i;
    size_t retval;

    setlocale(LC_ALL, "");

#if 0
    printf("Enter a string: ");
    scanf("%ls", string);
    printf("String Entered: %ls: length: %ld\n", string, wcslen(string));
#endif
    printf("sizeof(wchar_t): %ld (%ld)\n", sizeof(wchar_t), sizeof(char));

    printf("%ld: %ls: ", wcslen(umlauts), umlauts);
    for (i = 0; i < wcslen(umlauts); i++) {
        printf("%lc (%04x), ", umlauts[i], umlauts[i]);
    }
    printf("%lc \n", sign);

    retval = wcstombs(string, umlauts, string_length);
    printf("%ld: %s: ", retval, string);
    for (i = 0; i < retval; i++) {
        printf("%02x, ", (unsigned char)string[i]);
    }
    printf("\n");

    return 0;
}
#endif
