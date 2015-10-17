#ifndef MSTRING_H
#define MSTRING_H

void	mprint(FILE *f, const char *s, const char *separator);
size_t	mstrsize(const char *str);
size_t	mstrlen(const char *s);
char*	mstrdup(const char *str);
char*	mstrelem(char *s, const int index);
char*	mstrcat(char *dest, const char *s);
int		mstrncat(char *dest, const char *s, const size_t size);

#endif //MSTRING_H
