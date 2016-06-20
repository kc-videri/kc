/**
 * @file        kc-environment.h
 * @brief       Class to get environment variables (header file)
 * @author      Michael Ott <kc.videri@gmail.com>
 *
 * copyright:   (C) 2013 by Michael Ott
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

#ifndef __KC_ENVIRONMENT_H__
#define __KC_ENVIRONMENT_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Class KCEnvironment
 */
    typedef struct environment KCEnvironment;

/**
 * Initialise KCEnvironment
 * @return Object of KCEnvironment or NULL if error
 */
    KCEnvironment *kc_environment_new();
/**
 * Free KCEnvironment
 * @param environment Object of KCEnvironment
 */
    void kc_environment_free(KCEnvironment * environment);
/**
 * Get local host name
 * @param environment Object of KCEnvironment
 * @return Local host name
 */
    char *kc_environment_get_username(KCEnvironment * environment);
/**
 * Get user name
 * @param environment Object of KCEnvironment
 * @return User name
 */
    char *kc_environment_get_hostname(KCEnvironment * environment);

#ifdef __cplusplus
}
#endif
#endif                          // __KC_ENVIRONMENT_H__
