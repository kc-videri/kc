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
struct kc_web_server;

/// Structure to communicate with a web server
typedef struct kc_web_server *KCWebServer;

/**
 * Initialise the KCWebServer object for a HTML document
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_new();
/**
 * Initialise the KCWebServer object
 * @param type Content Type
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_new_from_type(KCWebContentType type);
/**
 * Initialise the KCWebServer object from content type
 * Using CONTENT_TYPE value
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_new_using_content_type();
/**
 * Initialise the KCWebServer object for a HTML document
 * Using SCRIPT_NAME value
 * @return KCWebServer object or NULL on error
 */
KCWebServer kc_web_server_new_from_ending();
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
int kc_web_server_print_image(KCWebServer obj, char *file_name);

/**
 * Get content type
 * @return Content type
 */
KCWebContentType kc_web_server_parse_content_type();
/**
 * Get content type
 * @param str String to parse
 * @return Content type or
 */
KCWebContentType kc_web_server_get_content_type_from_ending(char *str);

/**
 * Convert value from query format to ascii format
 * @param value Value to parse
 * @param length Length of the value
 * @return Created string
 */
KCWString kc_web_server_convert_value_string(const char *value, size_t length);

#ifdef __cplusplus
}
#endif
#endif                          /* __KC_WEB_SERVER_H__ */
