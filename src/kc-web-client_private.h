/**
 * @file        kc-web-client_private.h
 * @brief       Some web client stuff (Private header file)
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

#ifndef __KC_WEB_CLIENT_PRIVATE_H__
#define __KC_WEB_CLIENT_PRIVATE_H__

#include <kc-socket_private.h>

#if 0
#include <kc-linked-list.h>
#include <kc-string.h>
#include <kc-json.h>
#endif

/*
 * Private define declaration
 */

#define KC_WEB_CLIENT_DEFAULT_PORT          80  ///< Default HTTP port
#define KC_WEB_CLIENT_DEFAULT_SECURE_PORTR  443 ///< Default HTTPS port
#define KC_WEB_CLIENT_DEFAULT_PATH          "index.html" //Default path

/*
 * Private structure declaration
 * */

/**
 * Structure KCWeb: Structure to save all important web information
 */
struct kc_web_client {
    struct kc_socket object;                    ///< Parent object
    KCSocket socket;                            ///< KCSocket object
    uint16_t port;
    kcbool secure;
    KCString host;
    KCString path;
    KCString query;
    KCString fragment;
    KCWebRequestType request;
    KCWebContentType content_type;
    //int kc_web_client_set_header(char *key, char *value;
    KCString content;
};

#if 0

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
 * @param obj KCWeb object
 * @param query_string String to parse
 * @param type Type of request
 * @return
 */
int kc_web_parse_query_string(KCWeb obj, const char *query_string,
                              KCWebParameterType type);

/**
 * Create a new KCWebParameter
 * @return Item or NULL on error
 */
KCWebParameter kc_web_parameter_new();
/**
 * Create a new KCWebParameter
 * @param string String to check
 * @param length Length of string
 * @param type Type to set
 * @return Item or NULL on error
 */
KCWebParameter kc_web_parameter_new_from_string(KCString string,
                                                 size_t length,
                                                 KCWebParameterType type);
/**
 * Free parameter entry
 * @param obj Object to free
 * @return 0 => successful
 */
int kc_web_parameter_free(KCWebParameter obj);
/**
 * Set key
 * @param obj KCWebParameter pointer object
 * @param key Key to set
 * @return 0 => successful
 */
int kc_web_parameter_set_key(KCWebParameter obj, KCString key);
/**
 * Set value
 * @param obj KCWebParameter pointer Object
 * @param value Value to set
 * @return 0 => successful
 */
int kc_web_parameter_set_value(KCWebParameter obj, KCString value);
/**
 * Set type
 * @param obj KCWebParameter pointer Object
 * @param type Type to set
 * @return 0 => successful
 */
int kc_web_parameter_set_type(KCWebParameter obj,
                              KCWebParameterType type);
/**
 * Add item to parameter list
 * @param obj KCWeb object
 * @param item Parameter item to add
 * @return 0 => successfull
 */
int kc_web_parameter_list_add_item(KCWeb obj, KCWebParameter item);
#endif

#endif                          /* __KC_WEB_CLIENT_PRIVATE_H__ */
