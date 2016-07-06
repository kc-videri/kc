/**
 * @file        kc-json.c
 * @brief       A simple JSON wrapper
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

#include <kc-json.h>
#include <kc-json_private.h>

KCJson kc_json_new()
{
    KCJson result;

    result = (KCJson)malloc(sizeof(struct kc_json));
    if (result == NULL) {
        return result;
    }

    result->counter = 1;

    return result;
}

KCJson kc_json_new_from_string(KCString json_string)
{
    KCJson result;

    result = kc_json_new();
    if (result == NULL) {
        return result;
    }

    return result;
}

int kc_json_get_counter(KCJson json)
{
    return json->counter;
}
