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

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif                          // __KC_WEB_H__
