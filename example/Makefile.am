AUTOMAKE_OPTIONS = foreign nostdinc
LIBS = $(BLANK_AT_MAKETIME)

bin_PROGRAMS = example

example_SOURCES = \
	example.c

example_LDADD = ../src/libdoctree.la
example_CFLAGS = -I../include -g -rdynamic
