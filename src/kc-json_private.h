 /**
 * @file        kc-json_private.h
 * @brief       A simple JSON wrapper (Private header)
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

#ifndef __KC_JSON_PRIVATE_H__
#define __KC_JSON_PRIVATE_H__

#include <json.h>

#include <kc-object.h>
#include <kc-json.h>

/**
 * Structure KCWeb: Structure to save all important web information
 */
struct kc_json {
    KCObject object;                            ///< Parent object
    struct json_object *json_object;            ///< JSON object
    enum json_tokener_error error_no;           ///< Error number
    KCString error_desc;                        ///< Error description
};

struct kc_json_object {
    KCObject object;                            ///< Parent object
    struct json_object *json_object;            ///< JSON object
};

/**
 * Create a new JSON object
 * @return JSON object or NULL on error
 */
KCJsonObject kc_json_object_new();
/**
 * Free JSON object and all children
 * @param obj
 * @return
 */
int kc_json_object_free(KCJsonObject obj);
/**
 * Free only the header of the JSON object
 * @param obj
 * @return
 */
int kc_json_object_free_header(KCJsonObject obj);

#endif /* __KC_JSON_PRIVATE_H__ */
