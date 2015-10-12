#include <stdlib.h>

#include "libdoctree.h"

int
main(int argc, const char* argv[])
{
	DTnode *doc = NULL, *node = NULL;

	doc = DTnewNode(NULL, "root", 0);

	node = DTnewNode(doc, "child1", 0);
	DTnewNode(node, "grandchild1", 0);
	
	node = DTnewNode(doc, "child2", 0);
	DTnewNode(node, "grandchild2", 0);

	DTprintXml(stdout, doc);

	DTfreeNode(doc);
}