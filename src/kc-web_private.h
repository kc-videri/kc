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

#include <kc-linked-list.h>
#include <kc-string.h>

/*
 * Private structure declaration
 * */

/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
struct kc_web_content_type {
    KCWebContentType type;      ///< Content type
    KCString type_string;       ///< String to send to define type
    KCString endings[3];        ///< String to send to define type
};

/*
 * Private variable declaration
 * */

// TODO: add all useful content types
 KCWebContentTypeDef content_types[] = {
    {KC_WEB_CONTENT_HTML, "text/html", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_XHTML, "text/xhtml", {"xhtml", NULL}},
    {KC_WEB_CONTENT_JSON, "application/json", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/text", {"txt", NULL}},
    {KC_WEB_CONTENT_ICO, "image/x-icon", {"ico", NULL}},
    {KC_WEB_CONTENT_UNDEF, NULL, {NULL}}
};

/*
 * Private function declaration
 * */

/**
 * Parse a received string (query, content, ...)
 * @param web Pointer to KC Web structure
 * @param query_string String to parse
 * @param length Length of the value
 * @param type Type of request
 * @return
 */
int kc_web_parse_query_string(KCWeb * web, const char *query_string,
                              KCWebParameterType type);

/**
 * Create a new KCWebParameter
 * @return Item or NULL on error
 */
KCWebParameter *kc_web_parameter_new();
int kc_web_parameter_free(KCWebParameter *item);
int kc_web_parameter_set_key(KCWebParameter *item, KCString key);
int kc_web_parameter_set_value(KCWebParameter *item, KCString value);
int kc_web_parameter_set_type(KCWebParameter * item, KCWebParameterType type);
int kc_web_parameter_add_item(KCWebParameter * item);

#endif /* __KC_WEB_PRIVATE_H__ */
