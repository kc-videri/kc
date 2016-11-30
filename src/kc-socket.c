/**
 * @file        kc-socket.c
 * @brief       Source file for socket communication
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

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <kc-socket.h>
#include <kc-socket_private.h>
#include <kc-object.h>

/**
 * Public function definition
 * */
int kc_socket_set_port(KCSocket obj, int port)
{
    if (obj->domain == AF_INET) {
        obj->addr->sin_port = htons(port);
    } else if (obj->domain == AF_INET6) {
        obj->addr6->sin6_port = htons(port);
    } else {
        return -1;
    }

    return 0;
}

int kc_socket_set_host(KCSocket obj, char *host)
{
    struct addrinfo hints, *results, *result;
    int retval;
    int fd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = obj->domain;
    hints.ai_socktype = obj->type;

    if ((retval = getaddrinfo(host, NULL, &hints, &results)) != 0) {
        fprintf(stderr, "Cannot get address information: %s (%d)\n",
                gai_strerror(retval), retval);
        return retval;
    }

    for (result = results; result != NULL; result = result->ai_next) {
        fd = socket(result->ai_family, result->ai_socktype,
                    result->ai_protocol);
        if (fd == -1) {
            continue;
        }

        if (bind(fd, result->ai_addr, result->ai_addrlen) == 0) {
            if (obj->domain == AF_INET) {
                struct sockaddr_in *addr;

                addr = (struct sockaddr_in *) result->ai_addr;
                obj->addr->sin_addr.s_addr = addr->sin_addr.s_addr;
            } else if (obj->domain == AF_INET6) {
                struct sockaddr_in6 *addr;

                addr = (struct sockaddr_in6 *) result->ai_addr;
                memcpy(&(obj->addr6->sin6_addr), &(addr->sin6_addr),
                       sizeof(struct in6_addr));
            } else {
                return -1;
            }

            close(fd);
            break;
        }

        close(fd);

    }

    freeaddrinfo(results);      // all done with this structure

    return 0;
}

int kc_socket_set_ipv4_addr(KCSocket obj, char *ip_addr)
{
    int retval;

    retval =
        inet_pton(obj->domain, ip_addr,
                  (void *) (&(obj->addr->sin_addr.s_addr)));
    if (retval < 0) {
        fprintf(stderr, "Can't set ip addr: %s (%d)", strerror(errno),
                errno);
        return errno;
    } else if (retval == 0) {
        fprintf(stderr, "%s is not a valid IP address\n", ip_addr);
        return -1;
    }

    return 0;
}

int kc_socket_set_ipv6_addr(KCSocket obj, char *ip_addr)
{
    fprintf(stderr, "// TODO: not implemented\n");  // DELETE 

    return -1;
}

int kc_socket_connect(KCSocket obj)
{
    int retval;
    struct sockaddr *addr;
    size_t obj_size;

    if (obj->domain == AF_INET) {
        addr = (struct sockaddr *) obj->addr;
        obj_size = sizeof(struct sockaddr);
    } else if (obj->domain == AF_INET6) {
        fprintf(stderr, "// TODO: not test\n");  // DELETE 
        addr = (struct sockaddr *) obj->addr6;
        obj_size = sizeof(struct sockaddr);
    } else {
        return -1;
    }

    retval = connect(obj->fd, addr, obj_size);
    if (retval < 0) {
        fprintf(stderr, "Cannot connect: %s (%d)\n", strerror(errno),
                errno);
        return errno;
    }

    return 0;
}

/*
 * Private function declaration
 * */

KCSocket kc_socket_init(int domain, int type, int protocol)
{
    KCSocket obj;

    obj = (KCSocket) kc_object_new(sizeof(KCSocket));
    if (obj == NULL) {
        return NULL;
    }
    // Default settings
    obj->domain = domain;
    obj->type = type;
    obj->protocol = protocol;
    if (obj->domain == AF_INET) {
        obj->addr =
            (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in *));
        obj->addr->sin_family = domain;
    } else if (obj->domain == AF_INET6) {
        obj->addr6 =
            (struct sockaddr_in6 *) malloc(sizeof(struct sockaddr_in6 *));
        obj->addr6->sin6_family = domain;
    }

    if ((obj->fd = socket(obj->domain, obj->type, obj->protocol)) < 0) {
        fprintf(stderr, "Cannot create socket: %s (%d)\n", strerror(errno),
                errno);
        goto kc_socket_init_error;
    }

    return obj;

  kc_socket_init_error:
    kc_object_free((KCObject) obj);

    return NULL;
}

int kc_socket_free(KCSocket obj)
{
    free(obj->addr);

    return 0;
}

#if 0
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int create_tcp_socket();
char *get_ip(char *host);
char *build_get_query(char *host, char *page);
void usage();

#define HOST "coding.debuntu.org"
#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.0"

int main(int argc, char **argv)
{
    struct sockaddr_in *remote;
    int sock;
    int tmpres;
    char *ip;
    char *get;
    char buf[BUFSIZ + 1];
    char *host;
    char *page;

    if (argc == 1) {
        usage();
        exit(2);
    }
    host = argv[1];
    if (argc > 2) {
        page = argv[2];
    } else {
        page = PAGE;
    }

    //sock = create_tcp_socket();
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("Can't create TCP socket");
        exit(1);
    }
    //ip = get_ip(host);
    struct hostent *hent;
    int iplen = 15;             //XXX.XXX.XXX.XXX
    ip = (char *) malloc(iplen + 1);
    memset(ip, 0, iplen + 1);
    if ((hent = gethostbyname(host)) == NULL) {
        herror("Can't get IP");
        exit(1);
    }
    if (inet_ntop(AF_INET, (void *) hent->h_addr_list[0], ip, iplen) ==
        NULL) {
        perror("Can't resolve host");
        exit(1);
    }
    fprintf(stderr, "IP is %s\n", ip);

    remote = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in *));
    remote->sin_family = AF_INET;
    tmpres = inet_pton(AF_INET, ip, (void *) (&(remote->sin_addr.s_addr)));
    if (tmpres < 0) {
        perror("Can't set remote->sin_addr.s_addr");
        exit(1);
    } else if (tmpres == 0) {
        fprintf(stderr, "%s is not a valid IP address\n", ip);
        exit(1);
    }
    remote->sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *) remote, sizeof(struct sockaddr))
        < 0) {
        perror("Could not connect");
        exit(1);
    }
    get = build_get_query(host, page);
#if 0
    char *query;
    char *getpage = page;
    char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";
    if (getpage[0] == '/') {
        getpage = getpage + 1;
        fprintf(stderr, "Removing leading \"/\", converting %s to %s\n",
                page, getpage);
    }
    // -5 is to consider the %s %s %s in tpl and the ending \0 query =
    (char *) malloc(strlen(host) + strlen(getpage) +
                    strlen(USERAGENT) + strlen(tpl) - 5);
    sprintf(query, tpl, getpage, host, USERAGENT);
    return query;
#endif
    fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get);

    //Send the query to the server
    int sent = 0;
    while (sent < strlen(get)) {
        tmpres = send(sock, get + sent, strlen(get) - sent, 0);
        if (tmpres == -1) {
            perror("Can't send query");
            exit(1);
        }
        sent += tmpres;
    }
    //now it is time to receive the page
    memset(buf, 0, sizeof(buf));
    int htmlstart = 0;
    char *htmlcontent;
    while ((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0) {
        if (htmlstart == 0) {
            /* Under certain conditions this will not work.
             * If the \r\n\r\n part is splitted into two messages
             * it will fail to detect the beginning of HTML content
             */
            htmlcontent = strstr(buf, "\r\n\r\n");
            if (htmlcontent != NULL) {
                htmlstart = 1;
                htmlcontent += 4;
            }
        } else {
            htmlcontent = buf;
        }
        if (htmlstart) {
            fprintf(stdout, htmlcontent);
        }

        memset(buf, 0, tmpres);
    }
    if (tmpres < 0) {
        perror("Error receiving data");
    }
    free(get);
    free(remote);
    free(ip);
    close(sock);
    return 0;
}

void usage()
{
    fprintf(stderr, "USAGE: htmlget host [page]\n\
\thost: the website hostname. ex: coding.debuntu.org\n\
\tpage: the page to retrieve. ex: index.html, default: /\n");
}


int create_tcp_socket()
{
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("Can't create TCP socket");
        exit(1);
    }
    return sock;
}


char *get_ip(char *host)
{
    struct hostent *hent;
    int iplen = 15;             //XXX.XXX.XXX.XXX
    char *ip = (char *) malloc(iplen + 1);
    memset(ip, 0, iplen + 1);
    if ((hent = gethostbyname(host)) == NULL) {
        herror("Can't get IP");
        exit(1);
    }
    if (inet_ntop(AF_INET, (void *) hent->h_addr_list[0], ip, iplen) ==
        NULL) {
        perror("Can't resolve host");
        exit(1);
    }
    return ip;
}

char *build_get_query(char *host, char *page)
{
    char *query;
    char *getpage = page;
    char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";
    if (getpage[0] == '/') {
        getpage = getpage + 1;
        fprintf(stderr, "Removing leading \"/\", converting %s to %s\n",
                page, getpage);
    }
    // -5 is to consider the %s %s %s in tpl and the ending \0
    query =
        (char *) malloc(strlen(host) + strlen(getpage) +
                        strlen(USERAGENT) + strlen(tpl) - 5);
    sprintf(query, tpl, getpage, host, USERAGENT);
    return query;
}
#endif
