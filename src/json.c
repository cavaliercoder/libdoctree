#include "common.h"
#include "libdoctree.h"

static void
DTprintJsonNode(FILE *f, DTnode *node, int flags, int indent)
{
	int i = 0;
	DTnode **child = NULL;

	for (i = 0; i < indent; i++)
		fprintf(f, "  ");

	fprintf(f, "\"%s\": {\n", node->label);

	for (child = node->children; child && *child; child++)
		DTprintJsonNode(f, *child, flags, indent + 1);
	
	for (i = 0; i < indent; i++)
		fprintf(f, "  ");

	fprintf(f, "}\n", node->label);
}

void
DTprintJson(FILE *f, DTnode *node, int flags)
{
	DTnode **child = NULL;
	fprintf(f, "{\n");

	for (child = node->children; child && *child; child++)
		DTprintJsonNode(f, *child, flags, 1);

	fprintf(f, "}\n");
}