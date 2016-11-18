/**
 * @file        kc-tcp-socket.h
 * @brief       Header file for ipv4 tcp socket stuff
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

#ifndef __KC_TCP_SOCKET_H__
#define __KC_TCP_SOCKET_H__

#include <kc-socket.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialise the KCSocket object 
 * @return KCSocket object or NULL on error
 */
KCSocket kc_tcp_socket_init();

#ifdef __cplusplus
}
#endif

#endif                          /* __KC_TCP_SOCKET_H__ */
