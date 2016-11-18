AM_CFLAGS =\
	 -Wall\
	 -g
	 
#if WIN32
#KC_CFLAGS = -mms-bitfields
#KC_LDFLAGS = -Wl,-subsms-bitfields -lws2_32
#endif   

noinst_PROGRAMS= \
    kc-environment-test \
    kc-linked-list-test \
    kc-json-test \
	kc-webserver-rest-test.fcgi \
	kc-webclient-rest-test

kc_environment_test_SOURCES= kc-environment-test.c
kc_environment_test_LDFLAGS = $(top_srcdir)/src/libkc.la $(AM_LDFLAGS)
kc_environment_test_CPPFLAGS = -I$(top_srcdir)/include
kc_linked_list_test_SOURCES= kc-linked-list-test.c
kc_linked_list_test_LDFLAGS = $(top_srcdir)/src/libkc.la $(AM_LDFLAGS)
kc_linked_list_test_CPPFLAGS = -I$(top_srcdir)/include
kc_json_test_SOURCES= kc-json-test.c
kc_json_test_LDFLAGS = $(top_srcdir)/src/libkc.la $(AM_LDFLAGS)
kc_json_test_CPPFLAGS = -I$(top_srcdir)/include
kc_webserver_rest_test_fcgi_SOURCES= kc-web-rest-test.c
kc_webserver_rest_test_fcgi_LDFLAGS = -lkc -L../src/.libs/ -lkcwebserver -lfcgi $(AM_LDFLAGS) 
kc_webserver_rest_test_fcgi_CPPFLAGS = -I$(top_srcdir)/include
kc_webclient_rest_test_SOURCES= kc-webclient-rest-test.c
kc_webclient_rest_test_LDFLAGS = -lkc -lkcnet -L../src/.libs/ $(AM_LDFLAGS) 
kc_webclient_rest_test_CPPFLAGS = -I$(top_srcdir)/include
