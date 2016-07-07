 /**
 * @file        kc-json.h
 * @brief       A simple class to handle json structure
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

/**
 * Structure KCWeb: Structure to save all important web information
 */
typedef struct kc_json* KCJson;

/**
 * Create a new empty JSON object
 * @return Pointer to object or NULL on error
 */
KCJson kc_json_new();
/**
 * Create a json object from a string
 * @param obj Empty pointer to fill
 * @param json_string String to parse
 * @return 0 => successful, -1 => no memory; > 0 => handled by error function
 */
int kc_json_new_from_string(KCJson *obj, KCString json_string);
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

#ifdef __cplusplus
}
#endif

#endif /* __KC_JSON_H__ */
