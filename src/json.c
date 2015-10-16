#include "common.h"
#include "doctree.h"

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
				DTfputs(_T("\\\""), f);
				break;

			case '\\':
				DTfputs(_T("\\\\"), f);
				break;

			case '\r':
				// skip
				break;

			case '\n':
				DTfputs(_T("\\n"), f);
				break;

			default:
#ifdef _UNICODE
				fputwc(*val, f);
#else
				fputc(*val, f);
#endif
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
				DTfputs(_T("  "), f);

		// print attribute name
		DTfputs(_T("\""), f);
		DTprintJsonValue(f, (*att)->key);
		DTfputs(_T("\":"), f);

		// print space after attribute name
		if (0 != (flags & DTOUT_WHITESPACE))
			DTfputs(_T(" "), f);

		// print attribute value
		if (NULL == (*att)->value) { // null values
			DTfputs(_T("null"), f);
		} else if (0 != ((*att)->flags & DTATT_ARRAY)) { // multi-string array
			DTfputs(_T("["), f);
			for (c = (*att)->value, n = c + DTstrlen(c) + 1; *c; c = n, n += DTstrlen(n) + 1) {
				DTfputs(_T("\""), f);
				DTprintJsonValue(f, c);
				DTfputs(_T("\""), f);

				if (*n) {
					DTfputs(_T(","), f);
					if (0 != (flags & DTOUT_WHITESPACE))
						DTfputs(_T(" "), f);
				}
			}

			DTfputs(_T("]"), f);
		} else { // standard value
			DTfputs(_T("\""), f);
			DTprintJsonValue(f, (*att)->value);
			DTfputs(_T("\""), f);
		}

		// print comma
		if (NULL != *(att + 1) || 0 < DTchildCount(node))
			DTfputs(_T(","), f);

		// print line break
		if (0 != (flags & DTOUT_WHITESPACE))
			DTfputs(JS_NEWLINE, f);
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
		DTfputs(_T("["), f);
	else
		DTfputs(_T("{"), f);

	// print new line after object start
	if (0 != (flags & DTOUT_WHITESPACE) && (DTnodeHasAtts(node) || DTnodeHasChildren(node)))
		DTfputs(JS_NEWLINE, f);

	// print attributes for objects
	if (0 == (node->flags & DTNODE_ARRAY))
		DTprintJsonAtts(f, node, flags, indent);

	// print children
	for (child = node->children; child && *child; child++) {
		// print line indent
		if (0 != (flags & DTOUT_WHITESPACE))
			for (i = 0; i < indent + 1; i++)
				DTfputs(_T("  "), f);

		if (0 == (node->flags & DTNODE_ARRAY)) {
			// print object name
			DTfputs(_T("\""), f);
			DTprintJsonValue(f, (*child)->label);
			DTfputs(_T("\":"), f);

			// print space after node name
			if (0 != (flags & DTOUT_WHITESPACE))
				DTfputs(_T(" "), f);
		}

		// print child body
		DTprintJsonNode(f, *child, flags, indent + 1);

		// print comma
		if (NULL != *(child + 1))
			DTfputs(_T(","), f);

		// print line break
		if (0 != (flags & DTOUT_WHITESPACE))
			DTfputs(JS_NEWLINE, f);
	}
	
	// print indent before object end
	if (0 != (flags & DTOUT_WHITESPACE) && (DTnodeHasAtts(node) || DTnodeHasChildren(node)))
		for (i = 0; i < indent; i++)
			DTfputs(_T("  "), f);

	// print object end
	if (0 != (node->flags & DTNODE_ARRAY))
		DTfputs(_T("]"), f);
	else
		DTfputs(_T("}"), f);
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
	DTfputs(JS_NEWLINE, f);
}
