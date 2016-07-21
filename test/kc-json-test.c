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
    KCJson json = NULL;
    KCJsonObject value, array, array_2;

    json = kc_json_new_from_string(JSON_STRING);
    printf("Output nice:\n%s\n", kc_json_get_json_string(json, TRUE));
    printf("Output not nice:\n%s\n", kc_json_get_json_string(json, FALSE));
    kc_json_free(json);
    json = kc_json_new_from_string(JSON_STRING_NOT_WORKING);
    if (kc_json_get_error_no(json) != 0) {
        fprintf(stderr, "Cannot parse content: %s (%d)\n",
                kc_json_get_error_description(json),
                kc_json_get_error_no(json));
    }
    kc_json_free(json);

    json = kc_json_new();

    array = kc_json_array_new();
    array_2 = kc_json_array_new();

    value = kc_json_new_string("c");
    kc_json_array_add(array, value);
    kc_json_array_add(array_2, value);
    value = kc_json_new_string("c++");
    kc_json_array_add(array_2, value);
    value = kc_json_new_string("php");
    kc_json_array_add(array, value);
    value = kc_json_new_string("java");
    kc_json_array_add(array, value);

    value = kc_json_new_string("Joys of Programming");
    printf("Value: %s; Length: %d\n", kc_json_get_string(value),
           kc_json_get_string_len(value));
    kc_json_add_object(json, "Site Name", value);

    value = kc_json_new_boolean(1);
    printf("Value: %s\n", kc_json_get_boolean(value) == TRUE ? "true" : "false");
    kc_json_add_object(json, "Technical blog", value);

    value = kc_json_new_double(2.14);
    printf("Value: %f\n", kc_json_get_double(value));
    kc_json_add_object(json, "Average posts per day", value);

    value = kc_json_new_int(10);
    printf("Value: %d\n", kc_json_get_int(value));
    kc_json_add_object(json, "Number of posts", value);

    kc_json_add_object(json, "Categories", array);

    printf("Output nice:\n%s\n", kc_json_get_json_string(json, TRUE));

    return EXIT_SUCCESS;
}
