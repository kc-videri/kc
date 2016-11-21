/**
 * @file        kc-web-server_private.h
 * @brief       Some web server stuff (Private header file)
 * @author      Michael Ott <kc.videri@gmail.com>
 *
 * copyright:   (C) 2016 by Michael Ott
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

#ifndef __KC_WEB_SERVER_PRIVATE_H__
#define __KC_WEB_SERVER_PRIVATE_H__

#include <kc-web_private.h>
#include <kc-linked-list.h>
#include <kc-string.h>
#include <kc-json.h>

/*
 * Private define declaration
 */

#define KC_WEB_HTTP_PREFIX "HTTP_"

/*
 * Private structure declaration
 * */

#if 0
/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
struct kc_web_content_type_def {
    KCWebContentType type;      ///< Content type
    KCString type_string;       ///< String to send to define type
    KCString endings[3];        ///< String to send to define type
};

typedef struct kc_web_content_type_def *KCWebContentTypeDef;
#endif

/**
 * Structure KCWebServer: Structure to save all important web information
 */
struct kc_web_server {
    struct kc_web object;       ///< Parent object
#if 0
    char *uri;                  ///< URI
    char *get_query_string;     ///< Get query string
    KCLinkedList parameter;     ///< parameter list
#endif
    KCWebRequestType request_type;  ///< request type
    KCWebContentTypeDef content_type;   ///< Content type structure
    KCJson json;                ///< JSON object
};

/*
 * Private variable declaration
 * */

char *kc_web_http_keys[] = {
    "HTTP_HOST",
    "HTTP_USER_AGENT",
    "HTTP_ACCEPT",
    "HTTP_ACCEPT_LANGUAGE",
    "HTTP_ACCEPT_ENCODING",
    "HTTP_DNT",
    "HTTP_COOKIE",
    "HTTP_CONNECTION",
    NULL,
};

/*
 * Private function declaration
 * */

/**
 * Parse a received string (query (get), content (post), ...)
 * @param obj KCWebServer object
 * @param query_string String to parse
 * @param type Type of request
 * @return
 */
int kc_web_server_parse_query_string(KCWebServer obj,
                                     const char *query_string,
                                     KCWebParameterType type);

/**
 * Create a new KCWebParameter
 * @return Item or NULL on error
 */
KCWebParameter kc_web_server_parameter_new();
/**
 * Create a new KCWebParameter
 * @param string String to check
 * @param length Length of string
 * @param type Type to set
 * @return Item or NULL on error
 */
KCWebParameter kc_web_server_parameter_new_from_string(KCString string,
                                                       size_t length,
                                                       KCWebParameterType type);

#endif                          /* __KC_WEB_SERVER_PRIVATE_H__ */
