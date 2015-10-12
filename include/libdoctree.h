#ifndef LIBDOCTREE_H
#define LIBDOCTREE_H

#include <stdio.h>

#ifdef UNICODE
typedef wchar_t DTchar;
#else
typedef char DTchar;
#endif

typedef struct _DTnode {
	DTchar				*label;
	struct _DTnode		*parent;
	struct _DTnode		**children;
	struct _DTattribute	**attributes;
	int					flags;
} DTnode;

typedef struct _DTattribute {
	DTchar				*key;
	DTchar				*value;
	int					flags;
} DTattribute;

DTnode	*DTnewNode(DTnode *parent, const DTchar *label, int flags);
int		DTappendNode(DTnode *parent, DTnode *child);
int		DTchildCount(DTnode *node);
void	DTfreeNode(DTnode *node);


void	DTprintXml(FILE *f, DTnode *node);

#endif // LIBDOCTREE_H
