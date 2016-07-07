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
#include <stdio.h>

#include <kc-json.h>
#include <kc-json_private.h>

/*
 * Private function definition
 * */

KCJson kc_json_new()
{
    KCJson obj;

    obj = (KCJson) malloc(sizeof(struct kc_json));
#if 0
    if (obj == NULL) {
        return obj;
    }
#endif
    obj->error_no = json_tokener_success;
    obj->error_desc = (KCString) json_tokener_error_desc(obj->error_no);

    return obj;
}

int kc_json_new_from_string(KCJson * obj, KCString json_string)
{
    if (kc_json_new_obj(obj) == FALSE) {
        return -1;
    }

    (*obj)->object =
        json_tokener_parse_verbose(json_string, &(*obj)->error_no);
    if ((*obj)->object == NULL) {
        (*obj)->error_desc =
            (KCString) json_tokener_error_desc((*obj)->error_no);
        fprintf(stderr, "Cannot parse content: %s (%d)\n",
                json_tokener_error_desc((*obj)->error_no),
                (*obj)->error_no);
    }

    return (*obj)->error_no;
}

int kc_json_get_error_no(KCJson obj)
{
    return obj->error_no;
}

KCString kc_json_get_error_description(KCJson obj)
{
    return obj->error_desc;
}

/*
 * Private function definition
 * */
kcbool kc_json_new_obj(KCJson * obj)
{
    *obj = (KCJson) malloc(sizeof(struct kc_json));
    if (*obj == NULL) {
        return FALSE;
    }
    (*obj)->error_no = json_tokener_success;
    (*obj)->error_desc =
        (KCString) json_tokener_error_desc((*obj)->error_no);

    return TRUE;
}
