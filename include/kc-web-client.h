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
struct kc_web_client_recv_msg;

/// Main structure for communicate with a web server
typedef struct kc_web_client *KCWebClient;
/// Save data from received message
typedef struct kc_web_client_recv_msg *KCWebClientRecvMsg;

/**
 * Initialise the KCWebClient object for a HTML document
 * @return KCWebClient object or NULL on error
 */
KCWebClient kc_web_client_new();
/**
 * Free object
 * @param obj KCWebClient object
 * @return 0 ==> successful
 */
int kc_web_client_free(KCWebClient obj);

/**
 * Set port
 * @param obj KCWebClient object
 * @param port Port to use; default 80 / 443
 * @return 0 ==> successful
 */
int kc_web_client_set_port(KCWebClient obj, uint16_t port);
/**
 * Use a secure connection
 * @param obj KCWebClient object
 * @param secure TRUE => use secure communication; default: false
 * @return 0 ==> successful
 */
int kc_web_client_set_secure(KCWebClient obj, kcbool secure);
/**
 * Set host name
 * @param obj KCWebClient object
 * @param host Host name to use
 * @return 0 ==> successful
 */
int kc_web_client_set_host(KCWebClient obj, char *host);
/**
 * Set path
 * @param obj KCWebClient object
 * @param path Path to use; default: index.html
 * @return 0 ==> successful
 */
int kc_web_client_set_path(KCWebClient obj, char *path);
/**
 * Set query
 * @param obj KCWebClient object
 * @param query Query to use; default: empty
 * @return 0 ==> successful
 */
int kc_web_client_set_query(KCWebClient obj, char *query);
/**
 * Set fragment
 * @param obj KCWebClient object
 * @param fragment Fragment to use; default: empty
 * @return 0 ==> successful
 */
int kc_web_client_set_fragment(KCWebClient obj, char *fragment);
/**
 * Set request type
 * @param obj KCWebClient object
 * @param request Request type to use; default: GET
 * @return 0 ==> successful
 */
int kc_web_client_set_request(KCWebClient obj, KCWebRequestType request);
/**
 * Set content type
 * @param obj KCWebClient object
 * @param content_type Content type to use; default: XHTML
 * @return 0 ==> successful
 */
int kc_web_client_set_content_type(KCWebClient obj,
                                   KCWebContentType content_type);

/**
 * Set header value pair
 * @param obj KCWebClient object
 * @param key Key to set
 * @param value Value to set
 * @return 0 ==> successful
 */
int kc_web_client_set_header(KCWebClient obj, char *key, char *value);
/**
 * Set content message
 * @param obj KCWebClient object
 * @param content Content message
 * @return 0 ==> successful
 */
int kc_web_client_set_content(KCWebClient obj, char *content);

/**
 * Send message to web server
 * @param obj KCWebClient object
 * @return Received message object
 */
KCWebClientRecvMsg kc_web_client_send(KCWebClient obj);

#ifdef __cplusplus
}
#endif
#endif                          /* __KC_WEB_CLIENT_H__ */
