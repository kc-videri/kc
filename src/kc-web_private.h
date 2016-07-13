/**
 * @file        kc-web_private.h
 * @brief       Some web stuff (Private header file)
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

#ifndef __KC_WEB_PRIVATE_H__
#define __KC_WEB_PRIVATE_H__

#include <kc-object.h>
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

/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
struct kc_web_content_type {
    KCWebContentType type;                      ///< Content type
    KCString type_string;                       ///< String to send to define type
    KCString endings[3];                        ///< String to send to define type
};

/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
struct kc_web_content_type_def {
    KCWebContentType type;                      ///< Content type
    KCString type_string;                       ///< String to send to define type
    KCString endings[3];                        ///< String to send to define type
};

typedef struct kc_web_content_type_def *KCWebContentTypeDef;

/**
 * Structure KCWebParameter: Structure to save received parameter item
 */
struct kc_web_parameter {
    KCObject object;                            ///< Parent object
    KCWebParameterType type;                    ///< On which way does the parameter come
    KCString key;                               ///< Key of a parameter
    KCString value;                             ///< Value of a parameter
};

/**
 * Structure KCWeb: Structure to save all important web information
 */
struct kc_web {
    KCObject object;                            ///< Parent object
#if 0
    char *uri;                                  ///< URI
    char *get_query_string;                     ///< Get query string
#endif
    KCLinkedList parameter;                     ///< parameter list
    KCWebRequestType request_type;              ///< request type
    KCWebContentTypeDef content_type;           ///< Content type structure
    KCJson json;                                ///< JSON object
};

/*
 * Private variable declaration
 * */

// TODO MOT: add all useful content types
struct kc_web_content_type_def content_types[] = {
    {KC_WEB_CONTENT_HTML, "text/html", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_XHTML, "text/xhtml", {"xhtml", NULL}},
    {KC_WEB_CONTENT_JSON, "application/json", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/text", {"txt", NULL}},
    {KC_WEB_CONTENT_ICO, "image/x-icon", {"ico", NULL}},
    {KC_WEB_CONTENT_HTML, "application/x-www-form-urlencoded", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/xml", {"xml", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/atom+xml", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/form - data", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/alternative", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/mixed", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "application / base64 ", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "application / octet - stream ", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/plain ", {"txt", NULL}},
    {KC_WEB_CONTENT_UNDEF, "text/css ", {"css", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/javascript", {"js", NULL}},
    {KC_WEB_CONTENT_UNDEF, NULL, {NULL}}
};

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

#endif                          /* __KC_WEB_PRIVATE_H__ */
