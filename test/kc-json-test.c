/**
 * @file        kc-json-test.c
 * @brief       Test the simple JSON wrapper
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

#include <stdio.h>
#include <stdlib.h>

#include <kc-json.h>

#define JSON_STRING \
    "{\"sitename\":\"joys of programming\",\"tags\":[\"c\",[\"c\",\"c++\"]," \
    "\"java\",\"PHP\"],\"author-details\":{\"name\":\"Joys of Programming\"," \
    "\"Number of Posts\":10},\"price\":7.99,\"orderable\":true,}"
#define JSON_STRING_NOT_WORKING "asdf"

int main(int argc, char **argv)
{
    int retval;
    KCJson json = NULL;

    retval = kc_json_new_from_string(&json, JSON_STRING);
    retval = kc_json_new_from_string(&json, JSON_STRING_NOT_WORKING);
    if (retval > 0) {
        fprintf(stderr, "Cannot parse content: %s (%d)\n",
                kc_json_get_error_description(json),
                kc_json_get_error_no(json));
    }

    return EXIT_SUCCESS;
}
