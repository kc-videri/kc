/**
 * @file        kc-wstring_private.h
 * @brief       Private Header file for all string operations
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

#ifndef __KC_WSTRING_PRIVATE_H__
#define __KC_WSTRING_PRIVATE_H__

#include <stdlib.h>

#include <kc-object_private.h>

/**
 * Structure to handle strings
 */
struct kc_wstring {
    struct kc_object object;    ///< Parent object
    kcchar *string;             ///< Real string
    size_t length;              ///< Length of the string
    size_t pos;                 ///< current position in string
};

/**
 * Create a string
 * @param [out] length Length of the string
 * @param str Main part of the string
 * @param list Parameter list
 * @return New created string or NULL on error
 */
char *kc_wstring_create_string(size_t * length, const char *str, va_list list);

#endif                          /* __KC_WSTRING_PRIVATE_H__ */
