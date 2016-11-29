
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-I../include \
	$(KC_CFLAGS)

AM_CFLAGS =\
	`pkg-config --cflags json-c` \
	-Wall\
	-g

lib_LTLIBRARIES = libkc.la libkcnet.la libkcwebserver.la

libkc_la_SOURCES = \
	kc-object.c \
	kc-environment.c \
	kc-string.c \
	kc-wstring.c \
	kc-linked-list.c \
	kc-mutex.c \
	kc-json.c \
	kc-web.c \
	kc.c

libkc_la_LDFLAGS = 

libkc_la_LIBADD = \
	-ljson-c \
	$(KC_LIBS)

libkcnet_la_SOURCES = \
	kc-socket.c \
	kc-tcp-socket.c \
	kc-web-client.c

libkcnet_la_LDFLAGS = 

libkcnet_la_LIBADD = $(KC_LIBS) -lkc

libkcwebserver_la_SOURCES = \
	kc-web-server.c

libkcwebserver_la_LDFLAGS = 

libkcwebserver_la_LIBADD = $(KC_LIBS) -lkc -lfcgi

if PLATFORM_WIN32
libkc_la_LDFLAGS += -no-undefined
libkcwebserver_la_LDFLAGS += -no-undefined
endif

if NATIVE_WIN32
libkc_la_LDFLAGS += -export-dynamic
libkcwebserver_la_LDFLAGS += -export-dynamic
endif

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = kc-0.0.1.pc kcwebserver-0.0.1.pc

EXTRA_DIST = \
	kc-0.0.1.pc.in \
	kcwebserver-0.0.1.pc.in
