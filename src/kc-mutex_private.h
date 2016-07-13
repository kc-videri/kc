/**
 * @file        kc_mutex_private.h
 * @brief       Mutex implemenation for KC framework (Private header
 *              file)
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

#ifndef __KC_MUTEX_PRIVATE_H__
#define __KC_MUTEX_PRIVATE_H__

#include <pthread.h>

#include <kc-object.h>

struct kc_mutex_item {
    KCObject object;
    pthread_mutex_t mutex;
};

#endif                          /* __KC_MUTEX_PRIVATE_H__ */
