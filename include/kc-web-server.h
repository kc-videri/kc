/**
 * @file        kc-web-server.h
 * @brief       Some web server CGI stuff (Header file)
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

#ifndef __KC_WEB_SERVER_H__
#define __KC_WEB_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <kc-linked-list.h>
#include <kc-string.h>
#include <kc-web.h>

// forward declaration
struct kc_web;
struct kc_webserver_parameter;

typedef struct kc_web_server *KCWebServer;
typedef struct kc_web_server_parameter *KCWebParameter;

/**
 * Initialise the KCWebServer object for a HTML document
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_init();
/**
 * Initialise the KCWebServer object
 * @param type Content Type
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_init_type(KCWebContentType type);
/**
 * Initialise the KCWebServer object from content type
 * Using CONTENT_TYPE value
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_init_from_content_type();
/**
 * Initialise the KCWebServer object for a HTML document
 * Using SCRIPT_NAME value
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_init_from_ending();
/**
 * Free allocated memory
 * @param obj KCWebServer object
 * @return 0 => successful
 */
int kc_web_server_free(KCWebServer obj);

/**
 * Print content type
 * @param obj KCWebServer object
 */
void kc_web_server_print_content_type(KCWebServer obj);
/**
 * Print image
 * @param obj KCWebServer object
 * @param file_name File to print, File name with path
 * @return 0 => successful
 */
int kc_web_server_print_image(KCWebServer obj, KCString file_name);

/**
 * Get content type
 * @return Content type
 */
KCWebContentType kc_web_server_parse_content_type();
/**
 * Get content type
 * @param obj KCWebServer object
 * @return Content type
 */
KCWebContentType kc_web_server_get_content_type(KCWebServer obj);
/**
 * Get content type string
 * @param obj KCWebServer object
 * @return String of content type
 */
KCString kc_web_server_get_content_type_string(KCWebServer obj);
/**
 * Get content type
 * @param str String to parse
 * @return Content type or
 */
KCWebContentType kc_web_server_get_content_type_from_ending(KCString str);

/**
 * Convert value from query format to ascii format
 * @param value Value to parse
 * @param length Length of the value
 * @return Created string
 */
KCString kc_web_server_convert_value_string(const char *value, size_t length);

/**
 * Get the parameter list
 * @param obj KCWebServer object
 * @return Linked parameter list
 */
KCLinkedList kc_web_server_get_parameter_list(KCWebServer obj);
/**
 * Get parameter item from string
 * @param obj KCWebServer object
 * @param search_string Key string to search for
 * @return List object or NULL when not found
 */
KCWebParameter kc_web_server_parameter_get(KCWebServer obj,
                                           KCString search_string);
/**
 * Get key from KCWebParameter item
 * @param item KCWebParameter object
 * @return key object
 */
KCString kc_web_server_parameter_get_key(KCWebParameter item);
/**
 * Get value from KCWebParameter item
 * @param item KCWebParameter object
 * @return value object
 */
KCString kc_web_server_parameter_get_value(KCWebParameter item);
/**
 * Get type from KCWebParameter item
 * @param item KCWebParameter object
 * @return Parameter type
 */
KCWebParameterType kc_web_server_parameter_get_type(KCWebParameter item);

#ifdef __cplusplus
}
#endif
#endif                          /* __KC_WEB_SERVER_H__ */
