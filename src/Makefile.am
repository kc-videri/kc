
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-I../include \
	$(KC_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libkc.la libkcweb.la

libkc_la_SOURCES = \
	kc-environment.c \
	kc-string.c \
	kc-linked-list.c \
	kc-mutex.c \
	kc.c

libkc_la_LDFLAGS = 

libkc_la_LIBADD = $(KC_LIBS)

libkcweb_la_SOURCES = \
	kc-web.c

libkcweb_la_LDFLAGS = 

libkcweb_la_LIBADD = $(KC_LIBS) -lkc -lfcgi

if PLATFORM_WIN32
libkc_la_LDFLAGS += -no-undefined
libkcweb_la_LDFLAGS += -no-undefined
endif

if NATIVE_WIN32
libkc_la_LDFLAGS += -export-dynamic
libkcweb_la_LDFLAGS += -export-dynamic
endif

#include_HEADERS = \
#	kc.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = kc-0.0.1.pc kcweb-0.0.1.pc

EXTRA_DIST = \
	kc-0.0.1.pc.in \
	kcweb-0.0.1.pc.in
