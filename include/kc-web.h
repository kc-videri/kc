/**
 * @file        kc-web.h
 * @brief       Some web stuff (Header file)
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

#ifdef __cplusplus
extern "C" {
#endif

#include <kc-linked-list.h>
#include <kc-string.h>

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

// forward declaration
struct kc_web;
struct kc_web_parameter;

typedef struct kc_web *KCWeb;
typedef struct kc_web_parameter *KCWebParameter;

/**
 * Initialise the KCWeb object for a HTML document
 * @return KCWeb object or NULL on error
 */
KCWeb kc_web_init();
/**
 * Initialise the KCWeb object
 * @param type Content Type
 * @return KCWeb object or NULL on error
 */
KCWeb kc_web_init_type(KCWebContentType type);
/**
 * Initialise the KCWeb object from content type
 * Using CONTENT_TYPE value
 * @return KCWeb object or NULL on error
 */
KCWeb kc_web_init_from_content_type();
/**
 * Initialise the KCWeb object for a HTML document
 * Using SCRIPT_NAME value
 * @return KCWeb object or NULL on error
 */
KCWeb kc_web_init_from_ending();
/**
 * Free allocated memory
 * @param obj KCWeb object
 * @return 0 => successful
 */
int kc_web_free(KCWeb obj);

/**
 * Print content type
 * @param obj KCWeb object
 */
void kc_web_print_content_type(KCWeb obj);
/**
 * Print image
 * @param obj KCWeb object
 * @param file_name File to print, File name with path
 * @return 0 => successful
 */
int kc_web_print_image(KCWeb obj, KCString file_name);

/**
 * Get content type
 * @return Content type
 */
KCWebContentType kc_web_parse_content_type();
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
 * Get content type
 * @param str String to parse
 * @return Content type or
 */
KCWebContentType kc_web_get_content_type_from_ending(KCString str);

/**
 * Convert value from query format to ascii format
 * @param value Value to parse
 * @param length Length of the value
 * @return Created string
 */
KCString kc_web_convert_value_string(const char *value, size_t length);

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

#endif                          /* __KC_WEB_H__ */
