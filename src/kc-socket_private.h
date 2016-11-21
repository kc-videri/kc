/**
 * @file        kc-socket_private.h
 * @brief       Socket object (Private header)
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

#ifndef __KC_SOCKET_PRIVATE_H__
#define __KC_SOCKET_PRIVATE_H__

#include <kc-object_private.h>
#include <kc-socket.h>

/*
 * Private structure declaration
 * */

/**
 * Structure struct kc_web_content_type: Structure to handle different content types
 */
struct kc_socket {
    struct kc_object object;    ///< Parent object
    int fd;                     ///< Socket file handle
    int domain;                 ///< Domain type
    int type;                   ///< Socket type
    int protocol;               ///< Protocol type
    struct sockaddr_in *addr;   ///< Address structure
};

/*
 * Private function declaration
 * */

/**
 * Initialise the KCSocket object 
 * @param domain Domain type
 * @param type Socket type
 * @param protocol Protocol type
 * @return KCSocke object or NULL on error
 */
KCSocket kc_socket_init(int domain, int type, int protocol);
/**
 * Free KCSocket object
 * @param obj KCSocket object to free
 * @return 0 => successful
 */
int kc_socket_free(KCSocket obj);

#endif                          /* __KC_SOCKET_PRIVATE_H__ */
