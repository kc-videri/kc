/**
 * @file        kc-web_private.h
 * @brief       Some web stuff (Private header file)
 * @author      Michael Ott <kc.videri@gmail.com>
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

#ifndef __KC_WEB_PRIVATE_H__
#define __KC_WEB_PRIVATE_H__

#include <kc-linked-list.h>
#include <kc-object_private.h>
#include <kc.h>

/*
 * Private define declaration
 */

/*
 * Private structure declaration
 * */

/// Structure struct kc_web_content_type: Structure to handle different content types
struct kc_web_content_type_def {
    KCWebContentType type;      ///< Content type
    kcchar *type_string;        ///< String to send to define type
    kcchar *endings[3];         ///< String to send to define type
};

typedef struct kc_web_content_type_def *KCWebContentTypeDef;

/// Structure KCWeb: Structure to save all important web information
struct kc_web {
    struct kc_object object;    ///< Parent object
    KCWebContentTypeDef content_type;   ///< Content type structure
    KCWebRequestType request_type;  ///< request type
    KCWebHTTPVersion version;   ///< HTTP version
    KCLinkedList parameter;     ///< parameter list
};

/// Structure KCWeb: Structure to save received parameter item
struct kc_web_parameter {
    struct kc_object object;    ///< Parent object
    KCWebParameterType type;    ///< On which way does the parameter come
    kcchar *key;                ///< Key of a parameter
    kcchar *value;              ///< Value of a parameter
};

/// Structure to encode and decode ASCII signs
struct kc_web_html_chars {
    uint8_t id;                 ///< Id
    wchar_t sign;               ///< ASCII Sign
    kcchar *symbol;             ///< HTML name
    kcchar *description;        ///< Description
};

/*
 * Private variable declaration
 * */

extern struct kc_web_content_type_def content_types[];
extern struct kc_web_html_chars html_chars[];

/*
 * Private function declaration
 * */

/**
 * Create a new KCWeb object
 * @return New KCWeb object or NULL on error
 */
KCWeb kc_web_new();
/**
 * Free allocated memory
 * @param obj KCWeb object
 * @return 0 => successful
 */
int kc_web_free(KCWeb obj);

/**
 * Set content type
 * @param obj KCWeb object
 * @param type Content type to set
 * @return 0 => successful
 */
int kc_web_set_content_type(KCWeb obj, KCWebContentType type);
/**
 * Get content type definition from content type
 * @param type Content type
 * @return KCWebContentTypeDef object or NULL on error
 */
KCWebContentTypeDef kc_web_get_content_type_def_from_type(KCWebContentType type);
/**
 * Get content type definition from content type
 * @param type Content type
 * @return KCWebContentTypeDef object or NULL on error
 */
KCWebContentTypeDef kc_web_get_content_type_def_from_string(char *str);

/**
 * Set request type
 * @param obj KCWeb object
 * @param type Request type to set
 * @return 0 => successful
 */
int kc_web_set_request_type(KCWeb obj, KCWebRequestType type);
/**
 * Set HTTP version
 * @param obj KCWeb object
 * @param version HTTP version to set
 * @return 0 => successful
 */
int kc_web_set_http_version(KCWeb obj, KCWebHTTPVersion version);

/**
 * Create a new KCWebParameter
 * @return Item or NULL on error
 */
KCWebParameter kc_web_parameter_new();
/**
 * Free parameter entry
 * @param obj Object to free
 * @return 0 => successful
 */
int kc_web_parameter_free(KCWebParameter obj);
/**
 * Set key
 * @param obj KCWebParameter pointer object
 * @param key Key to set
 * @return 0 => successful
 */
int kc_web_parameter_set_key(KCWebParameter obj, char *key);
/**
 * Set value
 * @param obj KCWebParameter pointer Object
 * @param value Value to set
 * @return 0 => successful
 */
int kc_web_parameter_set_value(KCWebParameter obj, char *value);
/**
 * Set type
 * @param obj KCWebParameter pointer Object
 * @param type Type to set
 * @return 0 => successful
 */
int kc_web_parameter_set_type(KCWebParameter obj, KCWebParameterType type);
/**
 * Add item to parameter list
 * @param obj KCWeb object
 * @param item Parameter item to add
 * @return 0 => successfull
 */
int kc_web_parameter_list_add_item(KCWeb obj, KCWebParameter item);

#endif                          /* __KC_WEB_PRIVATE_H__ */
