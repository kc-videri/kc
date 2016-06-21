/**
 * @file        environment_test.c
 * @brief       Class to get environment variables (testing)
 * @author      K-C Videri <kc.videri@gmail.com>
 *
 * copyright:   (C) 2013 by K-C Videri
 *
 * Description : Uses shared library to print greeting
 * To run the resulting executable the LD_LIBRARY_PATH must be
 * set to ${project_loc}/kc/.libs
 * Alternatively, libtool creates a wrapper shell script in the
 * build directory of this program which can be used to run it.
 * Here the script will be called "environment".
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

#include "../include/kc-environment.h"

/**
 * Main function of testing environment
 */
int main(void) {
	KCEnvironment *environment;

#if defined(__linux__)
	printf("Linux\n");
#elif defined(_WIN32)
	printf("Windows\n");
#else
	printf("unknown\n");
#endif

	environment = kc_environment_new();
	printf("hostname: %s\n", kc_environment_get_hostname(environment)); // DELETE
	printf("username: %s\n", kc_environment_get_username(environment)); // DELETE

	//getchar();                  // DELETE
	kc_environment_free(environment);

	return (EXIT_SUCCESS);
}
