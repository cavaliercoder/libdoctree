#include "common.h"
#include "libdoctree.h"

static void
DTprintXmlNode(FILE *f, DTnode *node, int indent)
{
	int i = 0;
	DTnode **child = NULL;

	for (i = 0; i < indent; i++)
		fprintf(f, "  ");

	fprintf(f, "<%s>\n", node->label);

	for (child = node->children; child && *child; child++)
		DTprintXmlNode(f, *child, indent+1);
	
	for (i = 0; i < indent; i++)
		fprintf(f, "  ");

	fprintf(f, "</%s>\n", node->label);
}

void
DTprintXml(FILE *f, DTnode *node)
{
	DTprintXmlNode(f, node, 0);
}