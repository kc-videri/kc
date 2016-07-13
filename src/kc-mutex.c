/**
 * @file        kc_mutex.c
 * @brief       Mutex implemenation for KC framework
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

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <kc-mutex.h>
#include <kc-mutex_private.h>

int kc_mutex_item_init(KCMutexItem obj)
{
    int retval;

    retval = pthread_mutex_init(&(obj->mutex), NULL);
    if (retval) {
        fprintf(stderr, "%s::%s(%d): Cannot initialise mutex: %s (%d)\n",
                __FILE__, __func__, __LINE__, strerror(errno), errno);
        retval = errno;
    }

    return retval;
}

int kc_mutex_item_destroy(KCMutexItem obj)
{
    int retval;

    retval = pthread_mutex_destroy(&(obj->mutex));
    if (retval) {
        fprintf(stderr, "%s::%s(%d): Cannot initialise mutex: %s (%d)\n",
                __FILE__, __func__, __LINE__, strerror(errno), errno);
        retval = errno;
    }

    return retval;

}

int kc_mutex_item_lock(KCMutexItem obj)
{
    pthread_mutex_lock(&(obj->mutex));

    return 0;
}

int kc_mutex_item_unlock(KCMutexItem obj)
{
    pthread_mutex_unlock(&(obj->mutex));

    return 0;
}
