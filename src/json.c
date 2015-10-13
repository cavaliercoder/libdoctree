#include "common.h"
#include "libdoctree.h"

#define JS_SPACE		_T(" ")
#define JS_INDENT		_T("  ")
#define JS_NEWLINE		_T("\n")

static void
DTprintJsonAtts(FILE *f, DTnode *node, int flags, int indent)
{
	int			i = 0;
	DTattribute	**att = NULL;

	for (att = node->attributes; att && *att; att++) {
		// print line indent
		if (0 != (flags & DTJSON_WHITESPACE))
			for (i = 0; i < indent + 1; i++)
				DTfprintf(f, _T("  "));

		// print attribute name
		DTfprintf(f, _T("\"%s\":"), (*att)->key);

		// print space after attribute name
		if (0 != (flags & DTJSON_WHITESPACE))
			DTfprintf(f, _T(" "));

		// print attribute value
		if (NULL == (*att)->value)
			DTfprintf(f, _T("null"));
		else
			DTfprintf(f, _T("\"%s\""), (*att)->value);

		// print comma
		if (NULL != *(att + 1) || 0 < DTchildCount(node))
			DTfprintf(f, _T(","));

		// print line break
		if (0 != (flags & DTJSON_WHITESPACE))
			DTfprintf(f, JS_NEWLINE);
	}
}

static void
DTprintJsonNode(FILE *f, DTnode *node, int flags, int indent)
{
	int			i = 0;
	DTnode		**child = NULL;

	// print object start
	if (0 != (node->flags & DTNODE_ARRAY))
		DTfprintf(f, _T("["));
	else
		DTfprintf(f, _T("{"));

	if (0 != (flags & DTJSON_WHITESPACE) && (DTnodeHasAtts(node) || DTnodeHasChildren(node)))
		DTfprintf(f, JS_NEWLINE);

	// print attributes for objects
	if (0 == (node->flags & DTNODE_ARRAY))
		DTprintJsonAtts(f, node, flags, indent);

	// print children
	for (child = node->children; child && *child; child++) {
		// print line indent
		if (0 != (flags & DTJSON_WHITESPACE))
			for (i = 0; i < indent + 1; i++)
				DTfprintf(f, _T("  "));

		if (0 == (node->flags & DTNODE_ARRAY)) {
			// print object name
			DTfprintf(f, _T("\"%s\":"), (*child)->label);

			// print space after node name
			if (0 != (flags & DTJSON_WHITESPACE))
				DTfprintf(f, _T(" "));
		}

		// print child body
		DTprintJsonNode(f, *child, flags, indent + 1);

		// print comma
		if (NULL != *(child + 1))
			DTfprintf(f, _T(","));

		// print line break
		if (0 != (flags & DTJSON_WHITESPACE))
			DTfprintf(f, JS_NEWLINE);
	}
	
	// print indent before object end
	if (0 != (flags & DTJSON_WHITESPACE) && (DTnodeHasAtts(node) || DTnodeHasChildren(node)))
		for (i = 0; i < indent; i++)
			DTfprintf(f, _T("  "));

	// print object end
	if (0 != (node->flags & DTNODE_ARRAY))
		DTfprintf(f, _T("]"));
	else
		DTfprintf(f, _T("}"));
}
/*
 * Print a node and its descendants to the given file descriptor as a JSON
 * formatted document.
 */
void
DTprintJson(FILE *f, DTnode *node, int flags)
{
	DTprintJsonNode(f, node, flags, 0);

	// always end with a new line
	DTfprintf(f, JS_NEWLINE);
}
