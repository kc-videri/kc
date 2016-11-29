/**
 * @file        kc.h
 * @brief       Default header file for KC framework
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

#ifndef __KC_H__
#define __KC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <wchar.h>

#include "kc-mutex.h"

#define TRUE            1                       ///< TRUE
#define FALSE           0                       ///< FALSE

typedef uint32_t        kcbool;                 ///< Basic type boolean

typedef char            kcchar;                 ///< Basic type kcchar
typedef unsigned char   kcuchar;                ///< Basic type kcuchar
typedef wchar_t         kcwchar;                ///< Basic type kcwchar

typedef uint16_t        kcushort;               ///< Basic type u16_t

#ifdef __cplusplus
}
#endif

#endif                          /* __KC_H__ */
