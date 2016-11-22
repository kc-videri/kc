 /**
 * @file        kc-json.h
 * @brief       A simple class to handle JSON structure
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

#ifndef __KC_JSON_H__
#define __KC_JSON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <kc-string.h>

// Forward declaration
struct kc_json;
struct kc_json_object;
struct kc_json_array;

/// Structure to handle JSON stuff
typedef struct kc_json* KCJson;
/// JSON object
typedef struct kc_json_object* KCJsonObject;
/// JSON array list
typedef struct kc_json_array* KCJsonArray;

/**
 * Create a new empty JSON object
 * @return Pointer to object or NULL on error
 */
KCJson kc_json_new();
/**
 * Create a JSON object from a string; testing if the string conversation
 * works using kc_json_get_error_no(obj) == 0
 * @param json_string String to parse
 * @return NULL when memory allocation failed,
 */
KCJson kc_json_new_from_string(KCString json_string);
/**
 * Free allocated memory
 * @param obj object to free
 * @return 0 => successful
 */
int kc_json_free(KCJson obj);

/**
 * Get error code
 * @param obj JSON object
 * @return Error code
 */
int kc_json_get_error_no(KCJson obj);
/**
 * Get error description from error code
 * @param obj JSON object
 * @return Error description
 */
KCString kc_json_get_error_description(KCJson obj);

/**
 * Get JSON string from JSON object
 * @param obj JSON object
 * @param nice Nice outlook of the string
 * @return JSON object as string
 */
KCString kc_json_get_json_string(KCJson obj, kcbool nice);

#if 0
struct lh_table * kc_json_get_object(KCJsonObject obj);
int json_object_object_length(KCJsonObject obj);
#endif
/**
 * Add JSON object
 * @param obj JSON object
 * @param key Key
 * @param value Value
 * @return 0 => successful
 */
int kc_json_add_object(KCJson obj, const KCString key, KCJsonObject value);
#if 0
kcbool json_object_object_get_ex(KCJsonObject obj, const KCString key,
                                 KCJsonObject value);
void json_object_object_del(KCJsonObject obj, const KCString key);
#endif
/**
 * Create a new empty JSON array
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_array_new(void);
/**
 * Get the arraylist
 * @param obj JSON object
 * @return Array list
 */
KCJsonArray kc_json_array_get(KCJsonObject obj);
/**
 * Get the length of the array
 * @param obj JSON object
 * @return Length of the array
 */
int kc_json_array_get_length(KCJsonObject obj);
#if 0
void kc_json_array_sort(KCJsonObject jso,
                            int (*sort_fn)(const void *, const void *));
#endif
/**
 * Add an element to the end of the array
 * @param obj JSON object
 * @param value Element to add
 * @return
 */
int kc_json_array_add(KCJsonObject obj, KCJsonObject value);
/**
 * Insert or replace an element at a specified index in an array
 * @param obj JSON object
 * @param index Array index where the element have to set
 * @param value Element to set
 * @return 0 => successful
 */
int kc_json_array_put_index(KCJsonObject obj, int index, KCJsonObject value);
/**
 *
 * @param obj JSON object
 * @param index Array index where the element have to set
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_array_get_index(KCJsonObject obj, int index);
/**
 * Create a JSON object from boolean
 * @param value Boolean value
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_boolean(kcbool value);
/**
 * Get the boolean value of the object
 * @param obj JSON object
 * @return Boolean value
 */
kcbool kc_json_get_boolean(KCJsonObject obj);
/**
 * Create a JSON object from int32
 * @param value Int32 value
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_int(int32_t value);
/**
 * Create a JSON object from int64
 * @param value Int64 value
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_int64(int64_t value);
/**
 * Get the int32 value of the object
 * @param obj JSON object
 * @return Int32 value or errno in error
 */
int32_t kc_json_get_int(KCJsonObject obj);
/**
 * Get the int64 value of the object
 * @param obj JSON object
 * @return Int64 value or errno in error
 */
int64_t kc_json_get_int64(KCJsonObject obj);
/**
 * Create a JSON object from double
 * @param value Double value
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_double(double value);
/**
 * Get the double value of the object
 * @param obj JSON object
 * @return Double value or errno in error
 */
double kc_json_get_double(KCJsonObject obj);
/**
 * Create a JSON object from string
 * A copy of the string is made and the memory is managed by the class
 * @param value String to use
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_string(const KCString value);
/**
 * Create a JSON object from string
 * A copy of the string is made and the memory is managed by the class
 * @param value String to use
 * @param len Length of the string
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_string_len(const KCString value, int len);
/**
 * Get the string value of a JSON object
 * @param obj JSON object
 * @return String; If the passed object is not of type string then the JSON
 * representation of the object is returned; The returned string memory is
 * managed by the json_object
 */
const KCString kc_json_get_string(KCJsonObject obj);
/**
 * Get the string length of a JSON object
 * @param obj JSON object
 * @return Length or 0 if the passed object is not of type string
 */
int kc_json_get_string_len(KCJsonObject obj);

#ifdef __cplusplus
}
#endif

#endif /* __KC_JSON_H__ */
