/**
 * @file        kc-object.h
 * @brief       Main object (Header file)
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

#ifndef __KC_OBJECT_H__
#define __KC_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <kc-string.h>

// Forward declaration
struct kc_object;

/**
 * Structure KCObject: Main class
 */
typedef struct kc_object* KCObject;

/**
 * Create a new KC object
 * @param size Size of the object
 * @return KCObject or NULL on error
 */
KCObject kc_object_new(size_t size);
/**
 * Free object
 * @param obj Object to free
 * @return 0 => successful
 */
int kc_object_free(KCObject obj);

#ifdef __cplusplus
}
#endif

#endif                          /* __KC_OBJECT_H__ */
