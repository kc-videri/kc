/**
 * @file        kc-object.c
 * @brief       Main object
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

#include <kc-object.h>
#include <kc-object_private.h>

KCObject kc_object_new(size_t size)
{
    KCObject obj;

    obj = (KCObject)malloc(size);

    return obj;
}

int kc_object_free(KCObject obj)
{
    free(obj);

    return 0;
}