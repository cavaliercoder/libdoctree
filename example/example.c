#include <stdlib.h>
#include <string.h>

#include "libdoctree.h"

#ifndef _T
#ifdef _UNICODE
#define _T(s)		L ## s
#else
#define _T(s)		s
#endif
#endif

static void
usage(FILE *f)
{
	fprintf(f, "usage: example [xml | json]\n");
}

int
main(int argc, const char* argv[])
{
	DTnode *hier, *children;
	DTnode *adam, *eve, *cain, *abel, *seth;

	if (argc < 2) {
		usage(stderr);
		exit(1);
	}

	// Adam
	adam = DTnewNode(NULL, _T("root"), DTNODE_DEFAULT);
	DTsetAtt(adam, _T("Name"), _T("Adam"), DTATT_DEFAULT);
	DTsetAtt(adam, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	eve = DTnewNode(adam, _T("Spouse"), DTNODE_DEFAULT);
	DTsetAtt(eve, _T("Name"), _T("Eve"), DTATT_DEFAULT);
	DTsetAtt(eve, _T("Gender"), _T("Female"), DTATT_DEFAULT);

	children = DTnewNode(adam, _T("Children"), DTNODE_ARRAY);
	DTsetAtt(children, _T("TestArrayAtts"), _T("!!! THIS SHOULD NOT BE PRINTED !!!"), DTATT_DEFAULT);

	cain = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(cain, _T("Name"), _T("Cain"), DTATT_DEFAULT);
	DTsetAtt(cain, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	abel = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(abel, _T("Name"), _T("Abel"), DTATT_DEFAULT);
	DTsetAtt(abel, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	seth = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(seth, _T("Name"), _T("Seth"), DTATT_DEFAULT);
	DTsetAtt(seth, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	// Cain
	DTsetAtt(cain, _T("Spouse"), _T("Aclima"), DTATT_DEFAULT);

	children = DTnewNode(cain, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Enoch"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	children = DTnewNode(hier, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Irad"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	children = DTnewNode(hier, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Mehujael"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	children = DTnewNode(hier, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Methushael"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	// Abel
	DTsetAtt(abel, _T("Spouse"), NULL, DTATT_DEFAULT);
	children = DTnewNode(abel, _T("Children"), DTNODE_ARRAY);

	// Seth
	DTsetAtt(seth, _T("Spouse"), _T("Azura"), DTATT_DEFAULT);

	children = DTnewNode(seth, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Enos"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	children = DTnewNode(hier, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Cainan"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	children = DTnewNode(hier, _T("Children"), DTNODE_ARRAY);
	hier = DTnewNode(children, _T("Child"), DTNODE_DEFAULT);
	DTsetAtt(hier, _T("Name"), _T("Mahalaleel"), DTATT_DEFAULT);
	DTsetAtt(hier, _T("Gender"), _T("Male"), DTATT_DEFAULT);

	// setup feature tests
	DTsetAtt(adam, _T("TestJsonEscape"), _T("Multi\nLine\nValue!\nSome slashes: \\\\\nAnd quotes: \"America...\""), DTATT_DEFAULT);
	DTsetAtt(adam, _T("TestOverwrites"), _T("Initial value"), DTATT_DEFAULT);
	DTsetAtt(adam, _T("TestOverwrites"), _T("Updated value"), DTATT_DEFAULT);
	DTsetAtt(adam, _T("TestOverwrites"), _T("Final value"), DTATT_DEFAULT);
	DTsetAttArray(adam, _T("TestAttArray"), _T("one\0two\0three\0"), DTATT_DEFAULT); // append new
	DTsetAttArray(adam, _T("TestAttArray2"), _T("initial\0value\0"), DTATT_DEFAULT); // append new
	DTsetAttArray(adam, _T("TestAttArray2"), _T("final\0value\0"), DTATT_DEFAULT); // update existing

	// print json
	if (0 == strcmp(argv[1], "json"))
		DTprintJson(stdout, adam, DTOUT_WHITESPACE);
	else if (0 ==strcmp(argv[1], "xml"))
		DTprintXml(stdout, adam, DTOUT_WHITESPACE);
	else {
		fprintf(stderr, "Invalid document format: %s\n", argv[1]);
		exit(1);
	}

	// clean up
	DTfreeNode(adam);
}
