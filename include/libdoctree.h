#ifndef LIBDOCTREE_H
#define LIBDOCTREE_H

#ifdef UNICODE
typedef wchar_t DTchar;
#else
typedef char DTchar;
#endif

typedef struct _DTnode {
	DTchar				*label;
	struct _DTnode		*parent;
	struct _DTnode		**children;
	int					flags;
} DTnode;

DTnode	*DTnewNode(DTnode *parent, const DTchar *label);
int		DTappendNode(DTnode *parent, DTnode *child);
int		DTchildCount(DTnode *node);

#endif // LIBDOCTREE_H
