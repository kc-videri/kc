/**
 * @file        kc-string.h
 * @brief       Header file for all string operations
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

#ifndef __KC_STRING_H__
#define __KC_STRING_H__

#include <stdlib.h>

#include <kc.h>

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
struct kc_string;

/// Definition KCString
typedef struct kc_string* KCString;

/**
 * Create a string
 * @param value Value to copy into created string
 * @param length Length of the value
 * @return New created string or NULL on error
 */
KCString kc_string_new();
/**
 * Create a string
 * @param value Value to copy into created string
 * @param length Length of the value
 * @return New created string or NULL on error
 */
KCString kc_string_new_with_string(const char *value, size_t length);
/**
 * Free string
 * @param string String to free
 * @return 0 => successful
 */
int kc_string_free(KCString string);

#if 0
int kc_string_add(KCString, char *value, ...); 
int kc_string_add_char(KCString, char value);

int *kc_string_set_pos(KCString obj, size_t pos);
kcchar *kc_string_get(KCString obj);
kcchar *kc_string_get_pos(KCString obj);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KC_STRING_H__ */
