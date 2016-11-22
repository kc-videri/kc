/**
 * @file        kc-web.h
 * @brief       Common web stuff (Header file)
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

#ifndef __KC_WEB_H__
#define __KC_WEB_H__

#include <kc-linked-list.h>
#include <kc-string.h>

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
struct kc_web;
struct kc_web_parameter;

/// Main structure for all web stuff
typedef struct kc_web *KCWeb;
/// Structure to handle parameter or key / value
typedef struct kc_web_parameter *KCWebParameter;

/**
 * Enumeration for different types of giving parameter
 */
typedef enum {
    KC_WEB_PARAMETER_GET,                       ///< Parameter comes using GET
    KC_WEB_PARAMETER_POST,                      ///< Parameter comes using POST
    KC_WEB_PARAMETER_HTTP,                      ///< Parameter comes using HTTP
} KCWebParameterType;

/**
 * Enumeration for different types of receiving data
 */
typedef enum {
    KC_WEB_REQUEST_GET,                         ///< Request type GET
    KC_WEB_REQUEST_POST,                        ///< Request type POST
    KC_WEB_REQUEST_PUT,                         ///< Request type PUT
    KC_WEB_REQUEST_DELETE,                      ///< Request type DELETE
    KC_WEB_REQUEST_PATCH,                       ///< Request type PATCH
    KC_WEB_REQUEST_HEAD,                        ///< Request type HEAD
    KC_WEB_REQUEST_OPTIONS,                     ///< Request type OPTIONS
    KC_WEB_REQUEST_TRACE,                       ///< Request type TRACE
} KCWebRequestType;

/**
 * Enumeration for different types of receiving data
 */
typedef enum {
    KC_WEB_CONTENT_HTML = 0,                    ///< Content type text/html
    KC_WEB_CONTENT_XHTML,                       ///< Content type text/xhtml
    KC_WEB_CONTENT_JSON,                        ///< Content type application/json
    KC_WEB_CONTENT_TEXT,                        ///< Content type text
    KC_WEB_CONTENT_ICO,                         ///< Content type favicon
    KC_WEB_CONTENT_UNDEF                        ///< Last element or undefined type
} KCWebContentType;

/**
 * Get content type
 * @param obj KCWeb object
 * @return Content type
 */
KCWebContentType kc_web_get_content_type(KCWeb obj);
/**
 * Get content type string
 * @param obj KCWeb object
 * @return String of content type
 */
KCString kc_web_get_content_type_string(KCWeb obj);

/**
 * Get the parameter list
 * @param obj KCWeb object
 * @return Linked parameter list
 */
KCLinkedList kc_web_get_parameter_list(KCWeb obj);
/**
 * Get parameter item from string
 * @param obj KCWeb object
 * @param search_string Key string to search for
 * @return List object or NULL when not found
 */
KCWebParameter kc_web_parameter_get(KCWeb obj, KCString search_string);
/**
 * Get key from KCWebParameter item
 * @param item KCWebParameter object
 * @return key object
 */
KCString kc_web_parameter_get_key(KCWebParameter item);
/**
 * Get value from KCWebParameter item
 * @param item KCWebParameter object
 * @return value object
 */
KCString kc_web_parameter_get_value(KCWebParameter item);
/**
 * Get type from KCWebParameter item
 * @param item KCWebParameter object
 * @return Parameter type
 */
KCWebParameterType kc_web_parameter_get_type(KCWebParameter item);


#ifdef __cplusplus
}
#endif

#endif                          // __KC_WEB_H__
