/**
 * @file        kc-json.h
 * @brief       A simple class to handle json structure
 * @author      Michael Ott <michael@king-coder.de>
 *
 * copyright:   (C) 2016 by Michael Ott
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

#ifndef __KC_JSON_H__
#define __KC_JSON_H__

#include <json.h>

#include <kc-string.h>

typedef struct kc_json {
} KCJson;

KCJson *kc_json_new_from_string(KCString json);

#endif /* __KC_JSON_H__ */
