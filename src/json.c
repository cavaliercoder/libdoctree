#include "common.h"
#include "libdoctree.h"

#define JS_SPACE		_T(" ")
#define JS_INDENT		_T("  ")
#define JS_NEWLINE		_T("\n")

/*
 * Print a JSON key name or value and naively escape illegal characters.
 */
static void
DTprintJsonValue(FILE *f, DTchar *val)
{
	for (; val && *val; val++) {
		switch (*val) {
			case '"':
				DTfprintf(f, "\\\"");
				break;

			case '\\':
				DTfprintf(f, "\\\\");
				break;

			case '\r':
				// skip
				break;

			case '\n':
				DTfprintf(f, "\\n");
				break;

			default:
				DTfprintf(f, "%c", *val);
				break;
		}
	}
}

/*
 * Print a nodes attributes as a JSON formatted document.
 */
static void
DTprintJsonAtts(FILE *f, DTnode *node, int flags, int indent)
{
	int			i = 0;
	DTattribute	**att = NULL;
	DTchar		*c, *n;

	for (att = node->attributes; att && *att; att++) {
		// print line indent
		if (0 != (flags & DTOUT_WHITESPACE))
			for (i = 0; i < indent + 1; i++)
				DTfprintf(f, _T("  "));

		// print attribute name
		DTfprintf(f, _T("\""));
		DTprintJsonValue(f, (*att)->key);
		DTfprintf(f, _T("\":"));

		// print space after attribute name
		if (0 != (flags & DTOUT_WHITESPACE))
			DTfprintf(f, _T(" "));

		// print attribute value
		if (NULL == (*att)->value) { // null values
			DTfprintf(f, _T("null"));
		} else if (0 != ((*att)->flags & DTATT_ARRAY)) { // multi-string array
			DTfprintf(f, _T("["));
			for (c = (*att)->value, n = c + DTstrlen(c) + 1; *c; c = n, n += DTstrlen(n) + 1) {
				DTfprintf(f, "\"");
				DTprintJsonValue(f, c);
				DTfprintf(f, "\"");

				if (*n) {
					DTfprintf(f, ",");
					if (0 != (flags & DTOUT_WHITESPACE))
						DTfprintf(f, _T(" "));
				}
			}

			DTfprintf(f, _T("]"));
		} else { // standard value
			DTfprintf(f, _T("\""));
			DTprintJsonValue(f, (*att)->value);
			DTfprintf(f, _T("\""));
		}

		// print comma
		if (NULL != *(att + 1) || 0 < DTchildCount(node))
			DTfprintf(f, _T(","));

		// print line break
		if (0 != (flags & DTOUT_WHITESPACE))
			DTfprintf(f, JS_NEWLINE);
	}
}

/*
 * Print a node and its descendants to the given file descriptor as a JSON
 * formatted document with the given indentation.
 */
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

	// print new line after object start
	if (0 != (flags & DTOUT_WHITESPACE) && (DTnodeHasAtts(node) || DTnodeHasChildren(node)))
		DTfprintf(f, JS_NEWLINE);

	// print attributes for objects
	if (0 == (node->flags & DTNODE_ARRAY))
		DTprintJsonAtts(f, node, flags, indent);

	// print children
	for (child = node->children; child && *child; child++) {
		// print line indent
		if (0 != (flags & DTOUT_WHITESPACE))
			for (i = 0; i < indent + 1; i++)
				DTfprintf(f, _T("  "));

		if (0 == (node->flags & DTNODE_ARRAY)) {
			// print object name
			DTfprintf(f, _T("\""));
			DTprintJsonValue(f, (*child)->label);
			DTfprintf(f, _T("\":"));

			// print space after node name
			if (0 != (flags & DTOUT_WHITESPACE))
				DTfprintf(f, _T(" "));
		}

		// print child body
		DTprintJsonNode(f, *child, flags, indent + 1);

		// print comma
		if (NULL != *(child + 1))
			DTfprintf(f, _T(","));

		// print line break
		if (0 != (flags & DTOUT_WHITESPACE))
			DTfprintf(f, JS_NEWLINE);
	}
	
	// print indent before object end
	if (0 != (flags & DTOUT_WHITESPACE) && (DTnodeHasAtts(node) || DTnodeHasChildren(node)))
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
	// TODO: use iteration instead of recursion in DTprintJson to prevent stack
	// TODO: overflow

	// print root node and descendants
	DTprintJsonNode(f, node, flags, 0);

	// always end with a new line
	DTfprintf(f, JS_NEWLINE);
}
