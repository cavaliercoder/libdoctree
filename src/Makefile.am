# share dlibrary
lib_LTLIBRARIES = libdoctree.la

libdoctree_la_SOURCES = \
	common.c \
	mstring.c \
	nodes.c \
	attributes.c \
	json.c \
	xml.c

libdoctree_la_CFLAGS = \
	-I../include

libdoctree_la_LDFLAGS = \
	-shared \
	-avoid-version

# static library
lib_LIBRARIES = libdoctree.a

libdoctree_a_SOURCES = \
	common.c \
	mstring.c \
	nodes.c \
	attributes.c \
	json.c \
	xml.c

libdoctree_a_CFLAGS = \
	-I../include

# tests binary
noinst_PROGRAMS = dt_test

dt_test_CFLAGS = \
	-I../include

dt_test_SOURCES = \
	test.c \
	mstring.c
