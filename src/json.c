#include "common.h"
#include "libdoctree.h"

static void
DTprintJsonNode(FILE *f, DTnode *node, int flags, int indent)
{
	int			i = 0;
	DTnode		**child = NULL;
	DTattribute	**att = NULL;

	for (i = 0; i < indent; i++)
		DTfprintf(f, _T("  "));

	DTfprintf(f, _T("\"%s\": {\n"), node->label);

	for (att = node->attributes; att && *att; att++) {
		for (i = 0; i < indent + 1; i++)
			DTfprintf(f, _T("  "));

		DTfprintf(f, _T("\"%s\": \"%s\"\n"), (*att)->key, (*att)->value);
	}

	for (child = node->children; child && *child; child++)
		DTprintJsonNode(f, *child, flags, indent + 1);
	
	for (i = 0; i < indent; i++)
		DTfprintf(f, _T("  "));

	DTfprintf(f, _T("}\n"), node->label);
}

/*
 * Print a node and its descendants to the given file descriptor as a JSON
 * formatted document.
 */
void
DTprintJson(FILE *f, DTnode *node, int flags)
{
	DTnode **child = NULL;
	DTfprintf(f, _T("{\n"));

	for (child = node->children; child && *child; child++)
		DTprintJsonNode(f, *child, flags, 1);

	DTfprintf(f, _T("}\n"));
}
