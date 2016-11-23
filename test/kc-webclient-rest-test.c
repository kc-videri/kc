/**
 * @file        kc-webclient-rest-test.c
 * @brief       Test web client communication
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

#include <kc-web-client.h>

int main(void)
{
    KCWebClient client;

    client = kc_web_client_new();
    if (client == NULL) {
        return -1;
    }

    kc_web_client_set_host(client, "localhost");
    kc_web_client_set_path(client, "cgi/rest.fcgi");
    kc_web_client_send(client);

    return 0;
}
