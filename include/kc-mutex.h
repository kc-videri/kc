/**
 * @file        kc-mutex.h
 * @brief       Mutex implemenation for KC framework (Header file)
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

#ifndef __KC_MUTEX_H__
#define __KC_MUTEX_H__

#ifdef __cplusplus
extern "C" {
#endif

// Forward declaration
struct kc_mutex_item;

/// Main mutex structure
typedef struct kc_mutex_item *KCMutexItem;

/**
 * Initialise mutex
 * @param obj Mutex item to initialise
 * @return 0 => success, ! 0 => errno is set
 */
int kc_mutex_item_init(KCMutexItem obj);
/**
 * Destroy mutex
 * @param obj Mutex item to destroy
 * @return 0 => success, ! 0 => errno is set
 */
int kc_mutex_item_destroy(KCMutexItem obj);
/**
 * Lock mutext
 * @param obj Mutex item to lock
 * @return 0 => success
 * @return
 */
int kc_mutex_item_lock(KCMutexItem obj);
/**
 * Unlock mutext
 * @param obj Mutex item to lock
 * @return 0 => success
 * @return
 */
int kc_mutex_item_unlock(KCMutexItem obj);

#ifdef __cplusplus
}
#endif

#endif                          /* __KC_MUTEX_H__ */
