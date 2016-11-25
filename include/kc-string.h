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
 * @return New created string or NULL on error
 */
KCString kc_string_new();
/**
 * Create a string
 * @param value Value to copy into created string
 * @return New created string or NULL on error
 */
KCString kc_string_new_with_string(const char *value, ...);
/**
 * Free string
 * @param string String to free
 * @return 0 => successful
 */
int kc_string_free(KCString string);

#if 0
int kc_string_append(KCString, char *value, ...); 
int kc_string_append_char(KCString, char value);
#endif

/**
 * Get string
 * @param obj KCString object
 * @return String
 */
kcchar *kc_string_get_string(KCString obj);
/**
 * Get string from position
 * @param obj KCString object
 * @param pos Position to use
 * @return String
 */
kcchar *kc_string_get_string_from_pos(KCString obj, size_t pos);
/**
 * Get string from current position
 * @param obj KCString object
 * @return String
 */
kcchar *kc_string_get_string_from_current_pos(KCString obj);
/**
 * Set current string position
 * @param obj KCString object
 * @param pos position to use
 * @return 0 => successful
 */
int kc_string_set_pos(KCString obj, size_t pos);
/**
 * Get current string position
 * @param obj KCString object
 * @return Current position
 */
size_t kc_string_get_pos(KCString obj);
/**
 * Set string length
 * @param obj KCString object
 * @param pos position to use
 * @return Length of the string
 */
int kc_string_set_length(KCString obj, size_t length);
/**
 * Get string length
 * @param obj KCString object
 * @return Length of the string
 */
size_t kc_string_get_length(KCString obj);

#ifdef __cplusplus
}
#endif

#endif /* __KC_STRING_H__ */
