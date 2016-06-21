/**
 * @file        kc_string.c
 * @brief       Implementation for all string operations
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

#include <stdlib.h>
#include <string.h>

#include <kc-string.h>

// TODO test application
KCString kc_string_create(const char *value, size_t length)
{
    char *result;

    result = (char *) malloc((length + 3) * sizeof(char));
    if (result == NULL) {
        goto kc_sting_create_exit;
    }
    memcpy(result, value, length);
    result[length] = '\0';

  kc_sting_create_exit:
    return result;
}
