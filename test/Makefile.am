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
    kc-json-test

kc_environment_test_SOURCES= kc-environment-test.c
kc_environment_test_LDFLAGS = $(top_srcdir)/src/libkc.la $(AM_LDFLAGS)
kc_environment_test_CPPFLAGS = -I$(top_srcdir)/include
kc_linked_list_test_SOURCES= kc-linked-list-test.c
kc_linked_list_test_LDFLAGS = $(top_srcdir)/src/libkc.la $(AM_LDFLAGS)
kc_linked_list_test_CPPFLAGS = -I$(top_srcdir)/include
kc_json_test_SOURCES= kc-json-test.c
kc_json_test_LDFLAGS = $(top_srcdir)/src/libkc.la $(AM_LDFLAGS)
kc_json_test_CPPFLAGS = -I$(top_srcdir)/include
