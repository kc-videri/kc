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
#include <kc-string.h>

#if 0
#include <kc-linked-list.h>
#include <kc-json.h>
#endif

/*
 * Private define declaration
 */

#define KC_WEB_CLIENT_DEFAULT_PORT        80    ///< Default HTTP port
#define KC_WEB_CLIENT_DEFAULT_SECURE_PORT 443   ///< Default HTTPS port
#define KC_WEB_CLIENT_DEFAULT_PATH        "index.html"  //Default path

/*
 * Private structure declaration
 * */

/// Structure to save all important web information
struct kc_web_client {
    struct kc_web object;       ///< Parent object
    KCSocket socket;            ///< KCSocket object
    uint16_t port;              ///< Port to use
    kcbool secure;              ///< Using secure communication
    kcchar *host;                 ///< Host to use
    kcchar *path;                 ///< Path to use
    kcchar *query;                ///< Query to use
    kcchar *fragment;             ///< Fragement ???
    kcchar *content;              ///< Content to send
};

struct kc_web_client_recv_msg {
    struct kc_web object;       ///< Parent object
    KCWebHTTPVersion version;   ///< HTTP Protocol version
    int error_code;             ///< HTTP error code
    KCString error_comment;     ///< HTTP error comment
    KCString content;           ///< content
};

KCString kc_web_client_create_query(KCWebClient obj);

#endif                          /* __KC_WEB_CLIENT_PRIVATE_H__ */
