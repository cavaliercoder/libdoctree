#include "common.h"
#include "libdoctree.h"

static void
DTprintXmlNode(FILE *f, DTnode *node, int flags, int indent)
{
	int i = 0;
	DTnode **child = NULL;

	for (i = 0; i < indent; i++)
		fprintf(f, "  ");

	fprintf(f, "<%s>\n", node->label);

	for (child = node->children; child && *child; child++)
		DTprintXmlNode(f, *child, flags, indent + 1);
	
	for (i = 0; i < indent; i++)
		fprintf(f, "  ");

	fprintf(f, "</%s>\n", node->label);
}

void
DTprintXml(FILE *f, DTnode *node, int flags)
{
	DTprintXmlNode(f, node, flags, 0);
}