/**
 * @file        kc-list.h
 * @brief       
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

#ifndef __KC_LIST_H__
#define __KC_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kc_list {
    void *data;
    struct kc_list *next;
} KCList;

KCList *kc_list_new();
int kc_list_free(KCList *obj);
int kc_list_add(KCList *obj, void *data);
int kc_list_remove(KCList *obj, KCList *element);
int kc_list_clear(KCList *obj);

KCList *kc_list_get_first(KCList *obj);
KCList *kc_list_get_next(KCList *obj);
void *kc_list_element_get_data(KCList *obj);

#ifdef __cplusplus
}
#endif

#endif /* __KC_LIST_H__ */
