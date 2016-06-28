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

#include <kc-linked-list.h>
#include <kc-string.h>

/**
 * Enumeration for different types of giving parameter
 */
typedef enum {
    KC_WEB_PARAMETER_GET,       ///< Parameter comes using GET
    KC_WEB_PARAMETER_POST,      ///< Parameter comes using POST
    KC_WEB_PARAMETER_HTTP,      ///< Parameter comes using HTTP
} KCWebParameterType;

/**
 * Enumeration for different types of receiving data
 */
typedef enum {
    KC_WEB_REQUEST_GET,         ///< Request type GET
    KC_WEB_REQUEST_POST,        ///< Request type POST
    KC_WEB_REQUEST_PUT,         ///< Request type PUT
    KC_WEB_REQUEST_DELETE,      ///< Request type DELETE
} KCWebRequestType;

/**
 * Enumeration for different types of receiving data
 */
typedef enum {
    KC_WEB_CONTENT_HTML = 0,    ///< Content type text/html
    KC_WEB_CONTENT_XHTML,       ///< Content type text/xhtml
    KC_WEB_CONTENT_JSON,        ///< Content type application/json
    KC_WEB_CONTENT_TEXT,        ///< Content type text
    KC_WEB_CONTENT_ICO,         ///< Content type favicon
    KC_WEB_CONTENT_UNDEF        ///< Last element or undefined type
} KCWebContentType;

/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
typedef struct kc_web_content_type_def {
    KCWebContentType type;      ///< Content type
    KCString type_string;       ///< String to send to define type
    KCString endings[3];        ///< String to send to define type
} KCWebContentTypeDef;

/**
 * Structure KCWebParameter: Structure to save received parameter item
 */
typedef struct kc_web_parameter {
    KCWebParameterType type;    ///< On which way does the parameter come
    KCString key;               ///< Key of a parameter
    KCString value;             ///< Value of a parameter
} KCWebParameter;

/**
 * Structure KCWeb: Structure to save all important web information
 */
typedef struct kc_web {
#if 0
    char *uri;                  ///< URI
    char *get_query_string;     ///< Get query string
#endif
    KCLinkedList *parameter;    ///< parameter list
    KCWebRequestType request_type;  ///< request type
    KCWebContentTypeDef *content_type;  ///< Content type structure
} KCWeb;

/**
 * Initialise the KCWeb structure for a HTML document
 * @return Pointer to KCWeb structure or NULL on error
 */
KCWeb *kc_web_init();
/**
 * Initialise the KCWeb structure
 * @param type Content Type
 * @return Pointer to KCWeb structure or NULL on error
 */
KCWeb *kc_web_init_type(KCWebContentType type);
/**
 * Initialise the KCWeb structure for a HTML document
 * Using SCRIPT_NAME value
 * @return Pointer to KCWeb structure or NULL on error
 */
KCWeb *kc_web_init_from_ending();
/**
 * Free allocated memory
 * @param web Pointer to KCWeb structure
 * @return 0 => successful
 */
int kc_web_free(KCWeb *web);

/**
 * Print content type
 * @param web Pointer to KCWeb structure
 */
void kc_web_print_content_type(KCWeb *web);
/**
 * Print image
 * @param web Pointer to KCWeb structure
 * @param file_name File to print, File name with path
 * @return 0 => successful
 */
int kc_web_print_image(KCWeb *web, KCString file_name);

/**
 * Get content type
 * @param web Pointer to KCWeb structure
 * @return Content type
 */
KCWebContentType kc_web_get_content_type(KCWeb * web);
/**
 * Get content type string
 * @param web Pointer to KCWeb structure
 * @return String of content type
 */
KCString kc_web_get_content_type_string(KCWeb * web);
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
 * Get first entry of the parameter list (not thread saved)
 * @param web Pointer to KCWeb structure
 * @return First item in list
 */
KCLinkedListIterator kc_web_parameter_list_get_first(KCWeb *web);
/**
 * Get parameter item from string
 * @param web Pointer to KCWeb structure
 * @param search_string Key string to search for
 * @return Pointer to item or NULL when not found
 */
KCWebParameter *kc_web_parameter_get(KCWeb *web, KCString search_string);
/**
* Get key from KCWebParameter item
* @param item Pointer to KCWebParameter object
* @return Pointer to key
*/
KCString kc_web_parameter_get_key(KCWebParameter *item);
/**
* Get value from KCWebParameter item
* @param item Pointer to KCWebParameter object
* @return Pointer to value
*/
KCString kc_web_parameter_get_value(KCWebParameter *item);
/**
* Get type from KCWebParameter item
* @param item Pointer to KCWebParameter object
* @return Parameter type
*/
KCWebParameterType kc_web_parameter_get_type(KCWebParameter *item);

#endif /* __KC_WEB_H__ */
