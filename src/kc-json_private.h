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

/**
 * Structure KCWeb: Structure to save all important web information
 */
struct kc_json {
    json_object *object;                        ///< JSON object
    enum json_tokener_error error_no;           ///< Error number
    KCString error_desc;                        ///< Error description
};

kcbool kc_json_new_obj(KCJson *obj);

#endif /* __KC_JSON_PRIVATE_H__ */
