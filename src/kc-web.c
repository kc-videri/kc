/**
 * @file        kc-web.c
 * @brief       Some web stuff (Implementation)
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
#include <stdio.h>
#include <unistd.h>
#if 0
#include <fcgi_stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

#include <kc-web.h>
#include <kc-object.h>
#include <kc-web.h>
#include <kc-web_private.h>
#if 0
#include <kc-string.h>
#endif

/*
 * Private variable declaration
 * */

// TODO MOT: add all useful content types
struct kc_web_content_type_def content_types[] = {
    {KC_WEB_CONTENT_HTML, "text/html", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_XHTML, "text/xhtml", {"xhtml", NULL}},
    {KC_WEB_CONTENT_JSON, "application/json", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/text", {"txt", NULL}},
    {KC_WEB_CONTENT_ICO, "image/x-icon", {"ico", NULL}},
    {KC_WEB_CONTENT_HTML, "application/x-www-form-urlencoded", {"htm", "html", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/xml", {"xml", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/atom+xml", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/form - data", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/alternative", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "mulitpart/mixed", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "application / base64 ", {NULL}},
    {KC_WEB_CONTENT_UNDEF, "application / octet - stream ", {NULL}},
    {KC_WEB_CONTENT_TEXT, "text/plain ", {"txt", NULL}},
    {KC_WEB_CONTENT_UNDEF, "text/css ", {"css", NULL}},
    {KC_WEB_CONTENT_UNDEF, "application/javascript", {"js", NULL}},
    {KC_WEB_CONTENT_UNDEF, NULL, {NULL}}
};

struct kc_web_html_chars html_chars[] = {
    {0x00, 0, NULL, "Null char"},
    {0x01, 0, NULL, "Start of Heading"},
    {0x02, 0, NULL, "Start of Text"},
    {0x03, 0, NULL, "End of Text"},
    {0x04, 0, NULL, "End of Transmission"},
    {0x05, 0, NULL, "Enquiry"},
    {0x06, 0, NULL, "Acknowledgment"},
    {0x07, 0, NULL, "Bell"},
    {0x08, 0, NULL, "Back Space"},
    {0x09, 0, NULL, "Horizontal Tab"},
    {0x0a, 0, NULL, "Line Feed"},
    {0x0b, 0, NULL, "Vertical Tab"},
    {0x0c, 0, NULL, "Form Feed"},
    {0x0d, 0, NULL, "Carriage Return"},
    {0x0e, 0, NULL, "Shift Out / X-On"},
    {0x0f, 0, NULL, "Shift In / X-Off"},
    {0x10, 0, NULL, "Data Line Escape"},
    {0x11, 0, NULL, "Device Control 1 (oft. XON)"},
    {0x12, 0, NULL, "Device Control 2"},
    {0x13, 0, NULL, "Device Control 3 (oft. XOFF)"},
    {0x14, 0, NULL, "Device Control 4"},
    {0x15, 0, NULL, "Negative Acknowledgement"},
    {0x16, 0, NULL, "Synchronous Idle"},
    {0x17, 0, NULL, "End of Transmit Block"},
    {0x18, 0, NULL, "Cancel"},
    {0x19, 0, NULL, "End of Medium"},
    {0x1a, 0, NULL, "Substitute"},
    {0x1b, 0, NULL, "Escape"},
    {0x1c, 0, NULL, "File Separator"},
    {0x1d, 0, NULL, "Group Separator"},
    {0x1e, 0, NULL, "Record Separator"},
    {0x1f, 0, NULL, "Unit Separator"},
    {0x20, ' ', "&nbsp;", "Space"},
    {0x21, '!', "!", "Exclamation mark"},
    {0x22, '"', "&quot;", "Double quotes (or speech marks)"},
    {0x23, '#', "#", "Number"},
    {0x24, '$', "$", "Dollar"},
    {0x25, '%', "%", "Procenttecken"},
    {0x26, '&', "&amp;", "Ampersand"},
    {0x27, '\'', "'", "Single quote"},
    {0x28, '(', "(", "Open parenthesis (or open bracket)"},
    {0x29, ')', ")", "Close parenthesis (or close bracket)"},
    {0x2a, '*', "*", "Asterisk"},
    {0x2b, '+', "+", "Plus"},
    {0x2c, ',', ",", "Comma"},
    {0x2d, '-', "-", "Hyphen"},
    {0x2e, '.', ".", "Period, dot or full stop"},
    {0x2f, '/', "/", "Slash or divide"},
    {0x30, '0', "0", "Zero"},
    {0x31, '1', "1", "One"},
    {0x32, '2', "2", "Two"},
    {0x33, '3', "3", "Three"},
    {0x34, '4', "4", "Four"},
    {0x35, '5', "5", "Five"},
    {0x36, '6', "6", "Six"},
    {0x37, '7', "7", "Seven"},
    {0x38, '8', "8", "Eight"},
    {0x39, '9', "9", "Nine"},
    {0x3a, ':', ":", "Colon"},
    {0x3b, ';', ";", "Semicolon"},
    {0x3c, '<', "&lt;", "Less than (or open angled bracket)"},
    {0x3d, '=', "=", "Equals"},
    {0x3e, '>', "&gt;", "Greater than (or close angled bracket)"},
    {0x3f, '?', "?", "Question mark"},
    {0x40, '@', "@", "At symbol"},
    {0x41, 'A', "A", "Uppercase A"},
    {0x42, 'B', "B", "Uppercase B"},
    {0x43, 'C', "C", "Uppercase C"},
    {0x44, 'D', "D", "Uppercase D"},
    {0x45, 'E', "E", "Uppercase E"},
    {0x46, 'F', "F", "Uppercase F"},
    {0x47, 'G', "G", "Uppercase G"},
    {0x48, 'H', "H", "Uppercase H"},
    {0x49, 'I', "I", "Uppercase I"},
    {0x4a, 'J', "J", "Uppercase J"},
    {0x4b, 'K', "K", "Uppercase K"},
    {0x4c, 'L', "L", "Uppercase L"},
    {0x4d, 'M', "M", "Uppercase M"},
    {0x4e, 'N', "N", "Uppercase N"},
    {0x4f, 'O', "O", "Uppercase O"},
    {0x50, 'P', "P", "Uppercase P"},
    {0x51, 'Q', "Q", "Uppercase Q"},
    {0x52, 'R', "R", "Uppercase R"},
    {0x53, 'S', "S", "Uppercase S"},
    {0x54, 'T', "T", "Uppercase T"},
    {0x55, 'U', "U", "Uppercase U"},
    {0x56, 'V', "V", "Uppercase V"},
    {0x57, 'W', "W", "Uppercase W"},
    {0x58, 'X', "X", "Uppercase X"},
    {0x59, 'Y', "Y", "Uppercase Y"},
    {0x5a, 'Z', "Z", "Uppercase Z"},
    {0x5b, '[', "[", "Opening bracket"},
    {0x5c, '\\', "\\", "Backslash"},
    {0x5d, ']', "]", "Closing bracket"},
    {0x5e, '^', "^", "Caret - circumflex"},
    {0x5f, '_', "_", "Underscore"},
    {0x60, '`', "`", "Grave accent"},
    {0x61, 'a', "a", "Lowercase a"},
    {0x62, 'b', "b", "Lowercase b"},
    {0x63, 'c', "c", "Lowercase c"},
    {0x64, 'd', "d", "Lowercase d"},
    {0x65, 'e', "e", "Lowercase e"},
    {0x66, 'f', "f", "Lowercase f"},
    {0x67, 'g', "g", "Lowercase g"},
    {0x68, 'h', "h", "Lowercase h"},
    {0x69, 'i', "i", "Lowercase i"},
    {0x6a, 'j', "j", "Lowercase j"},
    {0x6b, 'k', "k", "Lowercase k"},
    {0x6c, 'l', "l", "Lowercase l"},
    {0x6d, 'm', "m", "Lowercase m"},
    {0x6e, 'n', "n", "Lowercase n"},
    {0x6f, 'o', "o", "Lowercase o"},
    {0x70, 'p', "p", "Lowercase p"},
    {0x71, 'q', "q", "Lowercase q"},
    {0x72, 'r', "r", "Lowercase r"},
    {0x73, 's', "s", "Lowercase s"},
    {0x74, 't', "t", "Lowercase t"},
    {0x75, 'u', "u", "Lowercase u"},
    {0x76, 'v', "v", "Lowercase v"},
    {0x77, 'w', "w", "Lowercase w"},
    {0x78, 'x', "x", "Lowercase x"},
    {0x79, 'y', "y", "Lowercase y"},
    {0x7a, 'z', "z", "Lowercase z"},
    {0x7b, '{', "{", "Opening brace"},
    {0x7c, '|', "|", "Vertical bar"},
    {0x7d, '}', "}", "Closing brace"},
    {0x7e, '~', "~", "Equivalency sign - tilde"},
    {0x7f, 0, NULL, "Delete"},
    {0x80, '€', "&euro;", "Euro sign"},
    {0x81, 0, NULL, "not defined"},
    {0x82, 0, "&sbquo;", "Single low-9 quotation mark"},
    {0x83, 0, "&fnof;", "Latin small letter f with hook"},
    {0x84, 0, "&bdquo;", "Double low-9 quotation mark"},
    {0x85, 0, "&hellip;", "Horizontal ellipsis"},
    {0x86, 0, "&dagger;", "Dagger"},
    {0x87, 0, "&Dagger;", "Double dagger"},
    {0x88, 0, "&circ;", "Modifier letter circumflex accent"},
    {0x89, 0, "&permil;", "Per mille sign"},
    {0x8a, 0, "&Scaron;", "Latin capital letter S with caron"},
    {0x8b, 0, "&lsaquo;", "Single left-pointing angle quotation"},
    {0x8c, 'Œ', "&OElig;", "Latin capital ligature OE"},
    {0x8d, 0, NULL, ""},
    {0x8e, 'Ž', "Ž", "Latin captial letter Z with caron"},
    {0x8f, 0, NULL, ""},
    {0x90, 0, NULL, ""},
    {0x91, 0, "&lsquo;", "Left single quotation mark"},
    {0x92, 0, "&rsquo;", "Right single quotation mark"},
    {0x93, 0, "&ldquo;", "Left double quotation mark"},
    {0x94, 0, "&rdquo;", "Right double quotation mark"},
    {0x95, 0, "&bull;", "Bullet"},
    {0x96, 0, "&ndash;", "En dash"},
    {0x97, 0, "&mdash;", "Em dash"},
    {0x98, 0, "&tilde;", "Small tilde"},
    {0x99, 0, "&trade;", "Trade mark sign"},
    {0x9a, 0, "&scaron;", "Latin small letter S with caron"},
    {0x9b, 0, "&rsaquo;", "Single right-pointing angle quotation mark"},
    {0x9c, 'œ', "&oelig;", "Latin small ligature oe"},
    {0x9d, 0, NULL, ""},
    {0x9e, 'ž', "ž", "Latin small letter z with caron"},
    {0x9f, 'ÿ', "&Yuml;", "Latin capital letter Y with diaeresis"},
    {0xa0, ' ', "&nbsp;", "Non-breaking space"},
    {0xa1, '¡', "&iexcl;", "Inverted exclamation mark"},
    {0xa2, '¢', "&cent;", "Cent sign"},
    {0xa3, '£', "&pound;", "Pound sign"},
    {0xa4, '¤', "&curren;", "Currency sign"},
    {0xa5, '¥', "&yen;", "Yen sign"},
    {0xa6, '¦', "&brvbar;", "Pipe, Broken vertical bar"},
    {0xa7, '§', "&sect;", "Section sign"},
    {0xa8, '¨', "&uml;", "Spacing diaeresis - umlaut"},
    {0xa9, '©', "&copy;", "Copyright sign"},
    {0xaa, 'ª', "&ordf;", "Feminine ordinal indicator"},
    {0xab, '«', "&laquo;", "Left double angle quotes"},
    {0xac, '¬', "&not;", "Not sign"},
    {0xad, '­', "&shy;", "Soft hyphen"},
    {0xae, '®', "&reg;", "Registered trade mark sign"},
    {0xaf, '¯', "&macr;", "Spacing macron - overline"},
    {0xb0, '°', "&deg;", "Degree sign"},
    {0xb1, '±', "&plusmn;", "Plus-or-minus sign"},
    {0xb2, '²', "&sup2;", "Superscript two - squared"},
    {0xb3, '³', "&sup3;", "Superscript three - cubed"},
    {0xb4, '´', "&acute;", "Acute accent - spacing acute"},
    {0xb5, 'µ', "&micro;", "Micro sign"},
    {0xb6, '¶', "&para;", "Pilcrow sign - paragraph sign"},
    {0xb7, '·', "&middot;", "Middle dot - Georgian comma"},
    {0xb8, '¸', "&cedil;", "Spacing cedilla"},
    {0xb9, '¹', "&sup1;", "Superscript one"},
    {0xba, 'º', "&ordm;", "Masculine ordinal indicator"},
    {0xbb, '»', "&raquo;", "Right double angle quotes"},
    {0xbc, '¼', "&frac14;", "Fraction one quarter"},
    {0xbd, '½', "&frac12;", "Fraction one half"},
    {0xbe, '¾', "&frac34;", "Fraction three quarters"},
    {0xbf, '¿', "&iquest;", "Inverted question mark"},
    {0xc0, 'À', "&Agrave;", "Latin capital letter A with grave"},
    {0xc1, 'Á', "&Aacute;", "Latin capital letter A with acute"},
    {0xc2, 'Â', "&Acirc;", "Latin capital letter A with circumflex"},
    {0xc3, 'Ã', "&Atilde;", "Latin capital letter A with tilde"},
    {0xc4, 'Ä', "&Auml;", "Latin capital letter A with diaeresis"},
    {0xc5, 'Å', "&Aring;", "Latin capital letter A with ring above"},
    {0xc6, 'Æ', "&AElig;", "Latin capital letter AE"},
    {0xc7, 'Ç', "&Ccedil;", "Latin capital letter C with cedilla"},
    {0xc8, 'È', "&Egrave;", "Latin capital letter E with grave"},
    {0xc9, 'É', "&Eacute;", "Latin capital letter E with acute"},
    {0xca, 'Ê', "&Ecirc;", "Latin capital letter E with circumflex"},
    {0xcb, 'Ë', "&Euml;", "Latin capital letter E with diaeresis"},
    {0xcc, 'Ì', "&Igrave;", "Latin capital letter I with grave"},
    {0xcd, 'Í', "&Iacute;", "Latin capital letter I with acute"},
    {0xce, 'Î', "&Icirc;", "Latin capital letter I with circumflex"},
    {0xcf, 'Ï', "&Iuml;", "Latin capital letter I with diaeresis"},
    {0xd0, 'Ð', "&ETH;", "Latin capital letter ETH"},
    {0xd1, 'Ñ', "&Ntilde;", "Latin capital letter N with tilde"},
    {0xd2, 'Ò', "&Ograve;", "Latin capital letter O with grave"},
    {0xd3, 'Ó', "&Oacute;", "Latin capital letter O with acute"},
    {0xd4, 'Ô', "&Ocirc;", "Latin capital letter O with circumflex"},
    {0xd5, 'Õ', "&Otilde;", "Latin capital letter O with tilde"},
    {0xd6, 'Ö', "&Ouml;", "Latin capital letter O with diaeresis"},
    {0xd7, '×', "&times;", "Multiplication sign"},
    {0xd8, 'Ø', "&Oslash;", "Latin capital letter O with slash"},
    {0xd9, 'Ù', "&Ugrave;", "Latin capital letter U with grave"},
    {0xda, 'Ú', "&Uacute;", "Latin capital letter U with acute"},
    {0xdb, 'Û', "&Ucirc;", "Latin capital letter U with circumflex"},
    {0xdc, 'Ü', "&Uuml;", "Latin capital letter U with diaeresis"},
    {0xdd, 'Ý', "&Yacute;", "Latin capital letter Y with acute"},
    {0xde, 'Þ', "&THORN;", "Latin capital letter THORN"},
    {0xdf, 'ß', "&szlig;", "Latin small letter sharp s - ess-zed"},
    {0xe0, 'à', "&agrave;", "Latin small letter a with grave"},
    {0xe1, 'á', "&aacute;", "Latin small letter a with acute"},
    {0xe2, 'â', "&acirc;", "Latin small letter a with circumflex"},
    {0xe3, 'ã', "&atilde;", "Latin small letter a with tilde"},
    {0xe4, 'ä', "&auml;", "Latin small letter a with diaeresis"},
    {0xe5, 'å', "&aring;", "Latin small letter a with ring above"},
    {0xe6, 'æ', "&aelig;", "Latin small letter ae"},
    {0xe7, 'ç', "&ccedil;", "Latin small letter c with cedilla"},
    {0xe8, 'è', "&egrave;", "Latin small letter e with grave"},
    {0xe9, 'é', "&eacute;", "Latin small letter e with acute"},
    {0xea, 'ê', "&ecirc;", "Latin small letter e with circumflex"},
    {0xeb, 'ë', "&euml;", "Latin small letter e with diaeresis"},
    {0xec, 'ì', "&igrave;", "Latin small letter i with grave"},
    {0xed, 'í', "&iacute;", "Latin small letter i with acute"},
    {0xee, 'î', "&icirc;", "Latin small letter i with circumflex"},
    {0xef, 'ï', "&iuml;", "Latin small letter i with diaeresis"},
    {0xf0, 'ð', "&eth;", "Latin small letter eth"},
    {0xf1, 'ñ', "&ntilde;", "Latin small letter n with tilde"},
    {0xf2, 'ò', "&ograve;", "Latin small letter o with grave"},
    {0xf3, 'ó', "&oacute;", "Latin small letter o with acute"},
    {0xf4, 'ô', "&ocirc;", "Latin small letter o with circumflex"},
    {0xf5, 'õ', "&otilde;", "Latin small letter o with tilde"},
    {0xf6, 'ö', "&ouml;", "Latin small letter o with diaeresis"},
    {0xf7, '÷', "&divide;", "Division sign"},
    {0xf8, 'ø', "&oslash;", "Latin small letter o with slash"},
    {0xf9, 'ù', "&ugrave;", "Latin small letter u with grave"},
    {0xfa, 'ú', "&uacute;", "Latin small letter u with acute"},
    {0xfb, 'û', "&ucirc;", "Latin small letter u with circumflex"},
    {0xfc, 'ü', "&uuml;", "Latin small letter u with diaeresis"},
    {0xfd, 'ý', "&yacute;", "Latin small letter y with acute"},
    {0xfe, 'þ', "&thorn;", "Latin small letter thorn"},
    {0xff, 'ÿ', "&yuml;", "Latin small letter y with diaeresis"},
};


/**
 * Public function definition
 * */

KCWebContentType kc_web_get_content_type(KCWeb obj)
{
    return ((KCWeb) obj)->content_type->type;
}

kcchar *kc_web_get_content_type_string(KCWeb obj)
{
    return content_types[kc_web_get_content_type(obj)].type_string;
}

KCLinkedList kc_web_get_parameter_list(KCWeb obj)
{
    return obj->parameter;
}

KCWebParameter kc_web_parameter_get(KCWeb obj, char *search_string)
{
    KCLinkedList list;
    KCLinkedListIterator iterator;
    KCWebParameter parameter;

    list = kc_web_get_parameter_list(obj);
    kc_mutex_item_lock((KCMutexItem) list);
    for (iterator = kc_linked_list_item_get_first(list);
         kc_linked_list_item_is_last(list, iterator);
         iterator = kc_linked_list_item_get_next(iterator)) {
        parameter =
            (KCWebParameter) kc_linked_list_item_get_data(iterator);
        if (!strcmp(search_string, kc_web_parameter_get_key(parameter))) {
            kc_mutex_item_unlock((KCMutexItem) obj->parameter);

            return parameter;
        }
    }

    kc_mutex_item_unlock((KCMutexItem) obj->parameter);

    return NULL;
}

kcchar *kc_web_parameter_get_key(KCWebParameter item)
{
    return item->key;
}

kcchar *kc_web_parameter_get_value(KCWebParameter item)
{
    if (item->value == NULL) {
        return "";
    } else {
        return item->value;
    }
}

KCWebParameterType kc_web_parameter_get_type(KCWebParameter item)
{
    return item->type;
}

/**
 * Private function definition
 * */

KCWeb kc_web_new()
{
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
    KCWeb obj;

    obj = (KCWeb) kc_object_new(sizeof(KCWeb));
    if (obj == NULL) {
        fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
        return NULL;
    }
    // Default settings
    obj->parameter = kc_linked_list_new();
    if (obj->parameter == NULL) {
        fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
        goto kc_web_init_failed_memory;
    }

    return obj;

  kc_web_init_failed_memory:
    fprintf(stderr, "%s::%s(%d): \n", __FILE__, __FUNCTION__, __LINE__);    // DELETE
    kc_object_free((KCObject) obj);
    return NULL;
}

int kc_web_free(KCWeb obj)
{
    KCLinkedList list;
    KCLinkedListIterator iterator;
    KCWebParameter parameter;

    list = kc_web_get_parameter_list((KCWeb) obj);
    kc_mutex_item_lock((KCMutexItem) list);
    for (iterator = kc_linked_list_item_get_first(list);
         kc_linked_list_item_is_last(list, iterator);
         iterator = kc_linked_list_item_get_next(iterator)) {
        parameter =
            (KCWebParameter) kc_linked_list_item_get_data(iterator);
        kc_web_parameter_free(parameter);
    }
    kc_mutex_item_unlock((KCMutexItem) ((KCWeb) obj)->parameter);
    kc_linked_list_free(((KCWeb) obj)->parameter);

    kc_object_free((KCObject) obj);
    return 0;
}

KCWebContentTypeDef kc_web_get_content_type_def_from_type(KCWebContentType
                                                          type)
{
    KCWebContentTypeDef content_type;

    for (content_type = content_types;
         content_type->type != KC_WEB_CONTENT_UNDEF; content_type++) {
        if (type == content_type->type) {
            return content_type;
        }
    }

    return NULL;
}

KCWebContentTypeDef kc_web_get_content_type_def_from_string(char *str)
{
    kcbool found_one = FALSE;
    KCWebContentTypeDef content_type;

    for (content_type = content_types;
         content_type->type_string != NULL; content_type++) {
        if (!strcmp(str, content_type->type_string)) {
            found_one = TRUE;
            break;
        }
    }
    if (content_type->type == KC_WEB_CONTENT_UNDEF || found_one == FALSE) {
        fprintf(stderr, "%s(%d): Unknown content type: %s\n", __func__,
                __LINE__, str);
        content_type = NULL;
    }

    return content_type;
}

int kc_web_set_content_type(KCWeb obj, KCWebContentType type)
{
    obj->content_type =
        kc_web_get_content_type_def_from_type(KC_WEB_CONTENT_XHTML);

    return 0;
}

int kc_web_set_request_type(KCWeb obj, KCWebRequestType type)
{
    obj->request_type = KC_WEB_REQUEST_GET;

    return 0;
}

int kc_web_set_http_version(KCWeb obj, KCWebHTTPVersion version)
{
    obj->version = version;

    return 0;
}

KCWebParameter kc_web_parameter_new()
{
    KCWebParameter obj;

    obj = (KCWebParameter)
        kc_object_new(sizeof(struct kc_web_parameter));
    if (obj != NULL) {
        obj->key = NULL;
        obj->value = NULL;
    }

    return obj;
}

int kc_web_parameter_free(KCWebParameter item)
{
    if (item->key != NULL) {
        free(item->key);
    }
    if (item->value != NULL) {
        free(item->value);
    }
    kc_object_free((KCObject) item);

    return 0;
}

int kc_web_parameter_set_key(KCWebParameter item, char *key)
{
    item->key = key;

    return 0;
}

int kc_web_parameter_set_value(KCWebParameter item, char *value)
{
    item->value = value;

    return 0;
}

int kc_web_parameter_set_type(KCWebParameter item, KCWebParameterType type)
{
    item->type = type;

    return 0;
}

int kc_web_parameter_list_add_item(KCWeb obj, KCWebParameter item)
{
    kc_linked_list_add(obj->parameter, item);

    return 0;
}
