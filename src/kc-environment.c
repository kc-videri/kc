/**
 * @file        environment.c
 * @brief       Class to get environment variables (implementation)
 * @author      K-C Videri <kc.videri@gmail.com>
 *
 * copyright:   (C) 2013 by K-C Videri
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

#if defined(__linux__)
#include <unistd.h>

#elif (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#endif

#include "../include/kc-environment.h"

#define BUFFER_LENGTH 255           /**< Length of the buffer */

/**
 * Private environment structure
 */
struct environment {
    char *hostname; 				/**< Local host name */
    char *username; 				/**< User name */
};

// private
/**
 * Private function to get local host name
 * @param environment Object of KCEnvironment
 * @return 0 == success
 */
int get_hostname(KCEnvironment * environment);
/**
 * Private function to get user name
 * @param environment Object of KCEnvironment
 * @return 0 == success
 */
int get_username(KCEnvironment * environment);
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
int convert_wchar_multibyte(TCHAR * msg, char *value);
#endif

KCEnvironment *kc_environment_new()
{
    KCEnvironment *environment;

    environment = (KCEnvironment *) malloc(sizeof(KCEnvironment));
    if (environment == NULL) {
        return (environment);
    }

    if (get_hostname(environment) != 0) {
        goto kc_environment_new_failed;
    }

    if (get_username(environment) != 0) {
        goto kc_environment_username_failed;
    }

    return (environment);

  kc_environment_username_failed:free(environment->hostname);

  kc_environment_new_failed:free(environment);
    environment = NULL;
    return (environment);
}

void kc_environment_free(KCEnvironment * environment)
{
    free(environment->username);
    free(environment->hostname);
    free(environment);

    return;
}

char *kc_environment_get_hostname(KCEnvironment * environment)
{
    return (environment->hostname);
}

char *kc_environment_get_username(KCEnvironment * environment)
{
    return (environment->username);
}

int get_hostname(KCEnvironment * environment)
{
#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    WSADATA WSAData;
#endif

    environment->hostname =
        (char *) malloc((BUFFER_LENGTH + 1) * sizeof(char));
    if (environment->hostname == NULL) {
        return (-1);
    }
#if defined(__linux__)
    gethostname(environment->hostname, BUFFER_LENGTH);
    // TODO MOT: Error handling

#elif (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    // Initialize winsock dll
    if (WSAStartup(MAKEWORD(1, 0), &WSAData) == FALSE) {
        // TODO MOT: Error handling
    }
    // Get local host name
    if (gethostname(environment->hostname, BUFFER_LENGTH - 1)) {
        // Error -> call 'WSAGetLastError()'
    }
    // Cleanup
    WSACleanup();
#endif

    return (0);
}

int get_username(KCEnvironment * environment)
{
    int retval;

    environment->username =
        (char *) malloc((BUFFER_LENGTH + 1) * sizeof(char));
    if (environment->username == NULL) {
        return (-1);
    }
#if defined(__linux__)
    //gethostname(environment->hostname, BUFFER_LENGTH);
    retval = getlogin_r(environment->username, BUFFER_LENGTH);
    // TODO MOT: Error handling

    return (0);
#elif (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
    //int length;
    DWORD length;

    length = BUFFER_LENGTH;
    retval =
        GetUserName((TCHAR *) environment->username,
//                    (LPDWORD) ((int *) &length));
                    (LPDWORD) &length);
    if (retval) {
        //retval = convert_wchar_multibyte(buffer, environment->username);

        return (0);
    } else {
        return (-1);
    }
#endif

}

#if (defined _WIN32 || defined __WIN32__) && ! defined __CYGWIN__
int convert_wchar_multibyte(TCHAR * msg, char *value)
{
    value = (char *) malloc((BUFFER_LENGTH + 1) * sizeof(char));
    if (value == NULL) {
        return (-1);
    }

    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR) msg,
                        wcslen((const wchar_t *) msg) + 1, value,
                        BUFFER_LENGTH, NULL, NULL);
    // TODO MOT: error handling
    printf("%s\n", value);

    return (0);
}
#endif
