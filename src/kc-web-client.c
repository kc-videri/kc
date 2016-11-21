/**
 * @file        kc-web-client .c
 * @brief       Some web client stuff (Implementation)
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

#include <stdio.h>

#include <kc-web.h>
#include <kc-web-client.h>
#include <kc-web-client_private.h>
#include <kc-tcp-socket.h>
#include <kc-object.h>

KCWebClient kc_web_client_init()
{
    KCWebClient obj;

    obj = (KCWebClient) kc_object_new(sizeof(KCWebClient));
    if (obj == NULL) {
        return NULL;
    }

    obj->socket = kc_tcp_socket_init();
    if (obj->socket == NULL) {
        goto kc_web_client_init_socket;
    }
    // default values
    obj->port = KC_WEB_CLIENT_DEFAULT_PORT;
    obj->secure = FALSE;
    obj->host = NULL;
    obj->path = NULL;
    obj->query = NULL;
    obj->fragment = NULL;
    obj->request = KC_WEB_REQUEST_GET;
    obj->content_type = KC_WEB_CONTENT_XHTML;
    obj->content = NULL;


    return obj;

    //kc_web_client_init_socket:

  kc_web_client_init_socket:
    kc_object_free((KCObject) obj);
    return NULL;
}

int kc_web_client_set_port(KCWebClient obj, uint16_t port)
{
    obj->port = port;

    return 0;
}

int kc_web_client_set_secure(KCWebClient obj, kcbool secure)
{
    obj->secure = secure;
    if (secure == TRUE) {
        obj->port = KC_WEB_CLIENT_DEFAULT_SECURE_PORT;
    } else {
        obj->port = KC_WEB_CLIENT_DEFAULT_PORT;
    }

    return 0;
}

int kc_web_client_set_host(KCWebClient obj, char *host)
{
    obj->host = host;

    return 0;
}

int kc_web_client_set_path(KCWebClient obj, char *path)
{
    obj->path = path;

    return 0;
}

int kc_web_client_set_query(KCWebClient obj, char *query)
{
    obj->query = query;

    return 0;
}

int kc_web_client_set_fragment(KCWebClient obj, char *fragment)
{
    obj->fragment = fragment;

    return 0;
}

int kc_web_client_set_request(KCWebClient obj, KCWebRequestType request)
{
    obj->request = request;

    return 0;
}

int kc_web_client_set_content_type(KCWebClient obj,
                                   KCWebContentType content_type)
{
    obj->content_type = content_type;

    return 0;
}

int kc_web_client_set_header(KCWebClient obj, char *key, char *value)
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
    KCWebParameter item;

    item = kc_web_parameter_new();
    if (item == NULL) {
        return -1;
    }

    kc_web_parameter_set_type(item, KC_WEB_PARAMETER_HTTP);
    kc_web_parameter_set_key(item, key);
    kc_web_parameter_set_value(item, value);
    kc_web_parameter_list_add_item((KCWeb) obj, item);

    return 0;
}

int kc_web_client_set_content(KCWebClient obj, char *content)
{
    obj->content = content;

    return 0;
}
