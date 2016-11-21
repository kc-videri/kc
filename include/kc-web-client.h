/**
 * @file        kc-web-client.h
 * @brief       Some web client stuff (Header file)
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

#ifndef __KC_WEB_CLIENT_H__
#define __KC_WEB_CLIENT_H__

#include <stdint.h>

#include <kc.h>
#include <kc-web.h>

#ifdef __cplusplus
extern "C" {
#endif

#if 0
#include <kc-linked-list.h>
#include <kc-string.h>
#endif

// forward declaration
struct kc_web_client;

typedef struct kc_web_client *KCWebClient;

/**
 * Initialise the KCWebClient object for a HTML document
 * @return KCWebClient object or NULL on error
 */
KCWebClient kc_web_client_init();
/**
 * Set port
 * @param port Port to use; default 80 / 443
 * @return 0 ==> successful
 */
int kc_web_client_set_port(uint16_t port);
/**
 * Use a secure connection
 * @param secure TRUE => use secure communication; default: false
 * @return 0 ==> successful
 */
int kc_web_client_set_secure(kcbool secure);
/**
 * Set host name
 * @param host Host name to use
 * @return 0 ==> successful
 */
int kc_web_client_set_host(char *host);
/**
 * Set path
 * @param path Path to use; default: index.html
 * @return 0 ==> successful
 */
int kc_web_client_set_path(char *path);
/**
 * Set query
 * @param query Query to use; default: empty
 * @return 0 ==> successful
 */
int kc_web_client_set_query(char *query);
/**
 * Set fragment
 * @param fragment Fragment to use; default: empty
 * @return 0 ==> successful
 */
int kc_web_client_set_fragment(char *fragment);
/**
 * Set request type
 * @param request Request type to use; default: GET
 * @return 0 ==> successful
 */
int kc_web_client_set_request(KCWebRequestType request);
/**
 * Set content type
 * @param content_type Content type to use; default: XHTML
 * @return 0 ==> successful
 */
int kc_web_client_set_content_type(KCWebContentType content_type);
/**
 * Set header value pair
 * @param key Key to set
 * @param value Value to set
 * @return 0 ==> successful
 */
int kc_web_client_set_header(char *key, char *value);
/**
 * Set content message
 * @param content Content message
 * @return 0 ==> successful
 */
int kc_web_client_set_content(char* content);

#if 0
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
#endif

#ifdef __cplusplus
}
#endif

#endif                          /* __KC_WEB_CLIENT_H__ */
