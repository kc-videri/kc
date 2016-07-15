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

/**
 * Structure KCJson: Structure to handle JSON stuff
 */
typedef struct kc_json* KCJson;
/**
 * Structure KCJsonObject: JSON object
 */
typedef struct kc_json_object* KCJsonObject;

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
KCString kc_json_get_json_string(KCJson obji, kcbool nice);

#if 0
struct lh_table * json_object_get_object(KCJsonObject obj);
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
KCJsonObject json_object_new_array(void);
struct array_list * json_object_get_array(KCJsonObject obj);
int json_object_array_length(KCJsonObject obj);
void json_object_array_sort(KCJsonObject jso,
                            int (*sort_fn)(const void *, const void *));
int json_object_array_add(KCJsonObject obj, KCJsonObject val);
int json_object_array_put_idx(KCJsonObject obj, int idx, KCJsonObject val);
KCJsonObject json_object_array_get_idx(KCJsonObject obj, int idx);
KCJsonObject json_object_new_boolean(kcbool b);
kcbool json_object_get_boolean(KCJsonObject obj);
KCJsonObject json_object_new_int(int32_t i);
KCJsonObject json_object_new_int64(int64_t i);
int32_t json_object_get_int(KCJsonObject obj);
int64_t json_object_get_int64(KCJsonObject obj);
KCJsonObject json_object_new_double(double d);
KCJsonObject json_object_new_double_s(double d, const KCString ds);
double json_object_get_double(KCJsonObject obj);
#endif 
/**
 * Create a JSON object from string
 * A copy of the string is made and the memory is managed by the class
 * @param str String to use
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_string(const KCString str);
/**
 * Create a JSON object from string
 * A copy of the string is made and the memory is managed by the class
 * @param str String to use
 * @param len Length of the string
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_new_string_len(const KCString str, int len);
#if 0
const KCString  json_object_get_string(KCJsonObject obj);
int json_object_get_string_len(KCJsonObject obj);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KC_JSON_H__ */
