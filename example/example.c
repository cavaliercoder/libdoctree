#include <stdlib.h>

#include "libdoctree.h"

int
main(int argc, const char* argv[])
{
	DTnode *doc = NULL, *node = NULL;

	doc = DTnewNode(NULL, "root", 0);
	DTsetAtt(doc, "Name", "Adam", 0);
	DTsetAtt(doc, "Gender", "Male", 0);

	node = DTnewNode(doc, "child1", 0);
	DTsetAtt(node, "Name", "Cane", 0);
	DTsetAtt(node, "Gender", "Male", 0);

	DTnewNode(node, "grandchild1", 0);
	
	node = DTnewNode(doc, "child2", 0);
	DTsetAtt(node, "Name", "Abel", 0);
	DTsetAtt(node, "Gender", "Male", 0);

	node = DTnewNode(node, "grandchild2", 0);
	node = DTnewNode(node, "great-grandchild2", 0);

	DTsetAtt(node, "OverwriteTest", "Initial value", 0);
	DTsetAtt(node, "OverwriteTest", "Updated value", 0);
	DTsetAtt(node, "OverwriteTest", "Final value", 0);

	DTsetAtt(node, "NullTest", NULL, 0);

	DTprintJson(stdout, doc, 0);

	DTfreeNode(doc);
}
