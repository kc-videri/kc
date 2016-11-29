/**
 * @file        kc-wstring.h
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

#ifndef __KC_WSTRING_H__
#define __KC_WSTRING_H__

#include <stdlib.h>

#include <kc.h>

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
struct kc_wstring;

/// Definition KCWString
typedef struct kc_wstring* KCWString;

/**
 * Create a string
 * @return New created string or NULL on error
 */
KCWString kc_wstring_new();
/**
 * Create a string
 * @param value Value to copy into created string
 * @return New created string or NULL on error
 */
KCWString kc_wstring_new_with_string(const char *value, ...);
/**
 * Create a string
 * @param value Value to copy into created string
 * @return New created string or NULL on error
 */
KCWString kc_wstring_new_with_wstring(const wchar_t *value, ...);
/**
 * Create a string
 * @param value Value to copy into created string
 * @param length Length of the value
 * @return New created string or NULL on error
 */
KCWString kc_wstring_new_with_string_length(const char *value, size_t length);
/**
 * Create a string
 * @param value Value to copy into created string
 * @param length Length of the value
 * @return New created string or NULL on error
 */
KCWString kc_wstring_new_with_wstring_length(const wchar_t *value, size_t length);
/**
 * Free string
 * @param string String to free
 * @return 0 => successful
 */
int kc_wstring_free(KCWString string);

#if 0
int kc_wstring_append(KCWString, char *value, ...); 
int kc_wstring_append_char(KCWString, char value);
int kc_wstring_append_wchar(KCWString, wchar_t value);
#endif

/**
 * Get string as copy
 * @param obj KCWString object
 * @return String
 */
kcchar *kc_wstring_get_string(KCWString obj);
/**
 * Get string as copy
 * @param obj KCWString object
 * @return String
 */
kcwchar *kc_wstring_get_wstring(KCWString obj);
/**
 * Get string
 * @param obj KCWString object
 * @return String
 */
kcwchar *kc_wstring_get_string_pointer(KCWString obj);
/**
 * Get string as copy from position
 * @param obj KCWString object
 * @param pos Position to use
 * @return String
 */
kcchar *kc_wstring_get_string_from_pos(KCWString obj, size_t pos);
/**
 * Get string as copy from position
 * @param obj KCWString object
 * @param pos Position to use
 * @return String
 */
kcwchar *kc_wstring_get_wstring_from_pos(KCWString obj, size_t pos);
/**
 * Get string from position
 * @param obj KCWString object
 * @param pos Position to use
 * @return String
 */
kcwchar *kc_wstring_get_string_pointer_from_pos(KCWString obj, size_t pos);
/**
 * Get string as copy from current position
 * @param obj KCWString object
 * @return String
 */
kcchar *kc_wstring_get_string_from_current_pos(KCWString obj);
/**
 * Get string as copy from current position
 * @param obj KCWString object
 * @return String
 */
kcwchar *kc_wstring_get_wstring_from_current_pos(KCWString obj);
/**
 * Get string from current position
 * @param obj KCWString object
 * @return String
 */
kcwchar *kc_wstring_get_string_pointer_from_current_pos(KCWString obj);
/**
 * Set current string position
 * @param obj KCWString object
 * @param pos position to use
 * @return 0 => successful
 */
int kc_wstring_set_pos(KCWString obj, size_t pos);
/**
 * Get current string position
 * @param obj KCWString object
 * @return Current position
 */
size_t kc_wstring_get_pos(KCWString obj);
/**
 * Set string length
 * @param obj KCWString object
 * @param pos position to use
 * @return Length of the string
 */
int kc_wstring_set_length(KCWString obj, size_t length);
/**
 * Get string length
 * @param obj KCWString object
 * @return Length of the string
 */
size_t kc_wstring_get_length(KCWString obj);

#ifdef __cplusplus
}
#endif

#endif /* __KC_WSTRING_H__ */
