#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "mstring.h"

static void
print_failf(const char *format, ...)
{
   va_list arg;

   va_start(arg, format);

   fprintf(stderr, "[ \x1B[31mFAIL\033[0m ] ");
   vfprintf(stderr, format, arg);
   fputc('\n', stderr);

   va_end(arg);
}

static void
print_passf(const char *format, ...)
{
   va_list arg;
   va_start(arg, format);

   fprintf(stdout, "[ \x1B[32mPASS\033[0m ] ");
   vfprintf(stdout, format, arg);
   fputc('\n', stdout);

   va_end(arg);	
}

int
main(const int argc, const char **argv)
{
	int		errors = 0, i = 0, n = 0;
	char	*t, *c, buf[18];

	t = "one\0two\0three\0";

	/*
	 * test mstrlen
	 */
	n = mstrlen(t); // 3
	if (3 == n) {
		print_passf("mstrlen: length of multi-string array");
	} else {
		errors++;
		print_failf("mstrlen: expected multi-string length 3, got: %i", n);
	}
	
	n = mstrlen(""); // 3
	if (0 == n) {
		print_passf("mstrlen: length of empty multi-string array");
	} else {
		errors++;
		print_failf("mstrlen: expected multi-string length 0, got: %i", n);
	}

	/*
	 * test mstrsize
	 */
	n = mstrsize(t); // 14 + NULL
	if (15 == n) {
		print_passf("mstrsize: size of multi-string array");
	} else {
		errors++;
		print_failf("mstrsize: expected multi-string size 15, got: %i", n);
	}

	n = mstrsize("");
	if (0 != n) {
		errors++;
		print_failf("mstrsize: expected multi-string size 0, got: %i", n);
	}

	/* 
	 * test mstrdup
	 */
	c = mstrdup(t);
	n = -1;
	for (i = 0; i < 15; i++) {
		if (t[i] != c[i]) {
			n = i;
			break;
		}
	}
	free(c);

	if (-1 == n) {
		print_passf("mstrdup: duplicate multi-string");
	} else {
		errors++;
		print_failf("mstrdup: duplicated multi-string does not match source at char %i", n);
	}

	/*
	 * test mstrelem
	 */
	c = mstrelem(t, 0);
	if (0 != strcmp(c, "one")) {
		errors++;
		print_failf("Expected element 0 in multi-string array to be \"one\", got: \"%s\"\n", c);
	}

	c = mstrelem(t, 1);
	if (0 != strcmp(c, "two")) {
		errors++;
		print_failf("Expected element 1 in multi-string array to be \"two\", got: \"%s\"\n", c);
	}

	c = mstrelem(t, 2);
	if (0 != strcmp(c, "three")) {
		errors++;
		print_failf("Expected element 2 in multi-string array to be \"three\", got: \"%s\"\n", c);
	}

	c = mstrelem(t, 3);
	if (c) {
		errors++;
		print_failf("Expected element 3 in multi-string array to be NULL, got: \"%s\"\n", c);
	}

	c = mstrelem("", 0);
	if (c) {
		errors++;
		print_failf("Expected element 0 in empty multi-string array to be NULL, got: \"%s\"\n", c);
	}

	/*
	 * test mstrncat
	 */
	memset(buf, 0, sizeof(buf));
	n = mstrncat(buf, "one", sizeof(buf));
	if (n != 3) {
		errors++;
		print_failf("Expected append operation to write 3 characters, got: %i\n", n);
	}

	n = mstrncat(buf, "two", sizeof(buf));
	if (n != 3) {
		errors++;
		print_failf("Expected append operation to write 3 characters, got: %i\n", n);
	}

	n = mstrncat(buf, "three", sizeof(buf));
	if (n != 5) {
		errors++;
		print_failf("Expected append operation to write 3 characters, got: %i\n", n);
	}

	n = mstrncat(buf, "four", sizeof(buf)); // only room for 2 more chars
	if (n != 2) {
		errors++;
		print_failf("Expected append operation to write 2 characters, got: %i\n", n);
	}

	n = mstrncat(buf, "five", sizeof(buf)); // only room for 2 more chars
	if (n != 0) {
		errors++;
		print_failf("Expected append operation to write 0 characters, got: %i\n", n);
	}

	c = mstrelem(buf, 0);
	if (0 != strcmp(c, "one")) {
		errors++;
		print_failf("Expected element 0 in multi-string array to be \"one\", got: \"%s\"\n", c);
	}

	c = mstrelem(buf, 1);
	if (0 != strcmp(c, "two")) {
		errors++;
		print_failf("Expected element 1 in multi-string array to be \"two\", got: \"%s\"\n", c);
	}

	c = mstrelem(buf, 2);
	if (0 != strcmp(c, "three")) {
		errors++;
		print_failf("Expected element 2 in multi-string array to be \"three\", got: \"%s\"\n", c);
	}

	c = mstrelem(buf, 3);
	if (0 != strcmp(c, "fo")) {
		errors++;
		print_failf("Expected element 3 in multi-string array to be \"fo\", got: \"%s\"\n", c);
	}

	/*
	 * test mstrcat
	 */
	t = mstrdup(t);
	t = mstrcat(t, "four");
	c = mstrelem(t, 3);
	if (c && 0 == strcmp("four", c)) {
		print_passf("mstrcat: append to non-empty multi-string array");
	} else {
		errors++;
		print_failf("mstrcat: expected element 3 in multi-string array to be \"four\", got: \"%s\"\n", c);
	}
	
	t = mstrdup("");
	t = mstrcat(t, "one");
	c = mstrelem(t, 0);
	if (c && 0 == strcmp("one", c)) {
		print_passf("mstrcat: append to empty multi-string array");
	} else {
		errors++;
		print_failf("mstrcat: expected element 0 in multi-string array to be \"one\", got: \"%s\"\n", c);
	}

	return errors;
}

