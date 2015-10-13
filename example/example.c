#include <stdlib.h>

#include "libdoctree.h"

int
main(int argc, const char* argv[])
{
	DTnode *hier, *children;
	DTnode *adam, *eve, *cain, *abel, *seth;

	// Adam
	adam = DTnewNode(NULL, "root", DTNODE_DEFAULT);
	DTsetAtt(adam, "Name", "Adam", DTATT_DEFAULT);
	DTsetAtt(adam, "Gender", "Male", DTATT_DEFAULT);

	eve = DTnewNode(adam, "Spouse", DTNODE_DEFAULT);
	DTsetAtt(eve, "Name", "Eve", DTATT_DEFAULT);
	DTsetAtt(eve, "Gender", "Female", DTATT_DEFAULT);

	children = DTnewNode(adam, "Children", DTNODE_ARRAY);
	DTsetAtt(children, "TestArrayAtts", "!!! THIS SHOULD NOT BE PRINTED !!!", DTATT_DEFAULT);

	cain = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(cain, "Name", "Cain", DTATT_DEFAULT);
	DTsetAtt(cain, "Gender", "Male", DTATT_DEFAULT);

	abel = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(abel, "Name", "Abel", DTATT_DEFAULT);
	DTsetAtt(abel, "Gender", "Male", DTATT_DEFAULT);

	seth = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(seth, "Name", "Seth", DTATT_DEFAULT);
	DTsetAtt(seth, "Gender", "Male", DTATT_DEFAULT);

	// Cain
	DTsetAtt(cain, "Spouse", "Aclima", DTATT_DEFAULT);

	children = DTnewNode(cain, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Enoch", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	children = DTnewNode(hier, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Irad", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	children = DTnewNode(hier, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Mehujael", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	children = DTnewNode(hier, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Methushael", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	// Abel
	DTsetAtt(abel, "Spouse", NULL, DTATT_DEFAULT);
	children = DTnewNode(abel, "Children", DTNODE_ARRAY);

	// Seth
	DTsetAtt(seth, "Spouse", "Azura", DTATT_DEFAULT);

	children = DTnewNode(seth, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Enos", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	children = DTnewNode(hier, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Cainan", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	children = DTnewNode(hier, "Children", DTNODE_ARRAY);
	hier = DTnewNode(children, "Child", DTNODE_DEFAULT);
	DTsetAtt(hier, "Name", "Mahalaleel", DTATT_DEFAULT);
	DTsetAtt(hier, "Gender", "Male", DTATT_DEFAULT);

	// setup feature tests
	DTsetAtt(adam, "TestJsonEscape", "Multi\nLine\nValue!\nSome slashes: \\\\\nAnd quotes: \"America...\"", DTATT_DEFAULT);
	DTsetAttArray(adam, "TestAttArray", "one\0two\0three\0", DTATT_DEFAULT); // append new

	DTsetAttArray(adam, "TestAttArray2", "initial\0value\0", DTATT_DEFAULT); // append new
	DTsetAttArray(adam, "TestAttArray2", "final\0value\0", DTATT_DEFAULT); // update existing

	DTsetAtt(adam, "TestOverwrites", "Initial value", DTATT_DEFAULT);
	DTsetAtt(adam, "TestOverwrites", "Updated value", DTATT_DEFAULT);
	DTsetAtt(adam, "TestOverwrites", "Final value", DTATT_DEFAULT);

	// print
	DTprintJson(stdout, adam, DTOUT_WHITESPACE);
	DTfreeNode(adam);
}
