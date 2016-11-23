/**
 * @file        kc-socket.h
 * @brief       Header file for socket stuff
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

#ifndef __KC_SOCKET_H__
#define __KC_SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
struct kc_socket;

// Main KC socket structure
typedef struct kc_socket *KCSocket;

/**
 * Set port
 * @param obj KCSocket object
 * @param port Port number
 * @return 0 => successful
 */
int kc_socket_set_port(KCSocket obj, int port);
/**
 * Set domain name
 * @param obj KCSocket object
 * @param host Host name
 * @return 0 => successful
 */
int kc_socket_set_host(KCSocket obj, char *host);
/**
 * Set IPv4 address
 * @param obj KCSocket object
 * @param ip_addr
 * @return 0 => successful
 */
int kc_socket_set_ipv4_addr(KCSocket obj, char *ip_addr);
/**
 * Set   IPv6 address
 * @param obj KCSocket object
 * @param ip_addr
 * @return
 * @return 0 => successful
 */
int kc_socket_set_ipv6_addr(KCSocket obj, char *ip_addr);

#ifdef __cplusplus
}
#endif
#endif                          /* __KC_SOCKET_H__ */
