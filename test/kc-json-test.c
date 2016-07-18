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
    KCJsonObject value;

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
    fprintf(stderr, "%d: inside\n", __LINE__); // DELETE 
#if 0
    json_object *obj, *value, *array, *array_2;

    /*Creating a json object */
    obj = json_object_new_object();

    /* Creating a json array */
    array = json_object_new_array();
    array_2 = json_object_new_array();

    /* Creating json strings */
    value = json_object_new_string("c");
    /* Adding the above created json strings to the array */
    json_object_array_add(array, value);
    json_object_array_add(array_2, value);
    value = json_object_new_string("c++");
    json_object_array_add(array_2, value);
    json_object_array_add(array, array_2);
    value = json_object_new_string("php");
    json_object_array_add(array, value);

    /* Form the json object */
    /* Each of these is like a key value pair */
#endif

    /* Creating a json string */
#if 0
    value = json_object_new_string("Joys of Programming");
    json_object_object_add(obj, "Site Name", value);
#endif
    fprintf(stderr, "%d: inside\n", __LINE__); // DELETE 
    value = kc_json_new_string("Joys of Programming");
    fprintf(stderr, "%d: inside\n", __LINE__); // DELETE 
    kc_json_add_object(json, "Site Name", value);
    fprintf(stderr, "%d: inside\n", __LINE__); // DELETE 

#if 0
    /* Creating a json boolean */
    value = json_object_new_boolean(1);
    json_object_object_add(obj, "Technical blog", value);

    /* Creating a json double */
    value = json_object_new_double(2.14);
    json_object_object_add(obj, "Average posts per day", value);

    /* Creating a json integer */
    value = json_object_new_int(10);
    json_object_object_add(obj, "Number of posts", value);

    json_object_object_add(obj, "Categories", array);
#endif
    printf("Output nice:\n%s\n", kc_json_get_json_string(json, TRUE));

    return EXIT_SUCCESS;
}
