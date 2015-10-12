#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <string.h>

#ifdef UNICODE
#define DTstrdup	wcsdup
#else
#define DTstrdup	strdup
#endif

#endif // COMMON_H
