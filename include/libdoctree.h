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

DTnode			*DTnewNode(DTnode *parent, const DTchar *label, int flags);
int				DTappendNode(DTnode *parent, DTnode *child);
int				DTchildCount(DTnode *node);
void			DTfreeNode(DTnode *node);
int				DTnodeHasChildren(DTnode *node);

DTattribute		*DTnewAtt(const DTchar *key, const DTchar *val, int flags);
void			*DTfreeAtt(DTattribute *att);
int				DTattCount(DTnode *node);
int				DTappendAtt(DTnode *node, DTattribute *att);
DTattribute		*DTgetAtt(DTnode *node, const DTchar *key);
int				DTsetAtt(DTnode *node, const DTchar *key, const DTchar *val, int flags);
int				DTnodeHasAtts(DTnode *node);

void			DTprintXml(FILE *f, DTnode *node, int flags);
void			DTprintJson(FILE *f, DTnode *node, int flags);

#define DTNODE_DEFAULT		0x0
#define DTNODE_ARRAY		0x1

#define DTATT_DEFAULT		0x0

#define DTJSON_WHITESPACE	0x1

#endif // LIBDOCTREE_H
