#include "common.h"
#include "libdoctree.h"

/*
 * Allocate a new node. Returns NULL if out of memory.
 */
DTnode *
DTnewNode(DTnode *parent, const DTchar *label)
{
	DTnode	*node = NULL;
	int		appendResult = 0;

	// allocate
	node = calloc(0, sizeof(DTnode));
	if (NULL == node) {
		return NULL;
	}

	// duplicate and assign label
	node->label = DTstrdup(label);
	if (NULL == node->label) {
		free(node);
		return NULL;
	}

	// assign parent
	if (NULL != parent) {
		appendResult = DTappendNode(parent, node);
		if (0 == appendResult) {
			free(node);
			return NULL;
		}
	}

	return node;
}

/*
 * Append a node to another node.
 *
 * Returns the number of child nodes owned by the parent after the append
 * operation is complete or 0 on error.
 */
int
DTappendNode(DTnode *parent, DTnode *child)
{
	int childCount = 0;

	// check for NULLs
	if (NULL == parent || NULL == child)
		return 0;

	// count children
	childCount = DTchildCount(parent);

	// realloc child array with an extra slot for the new child and NULL
	// terminator
	parent->children = realloc(parent->children, sizeof(DTnode*) * (childCount + 2));
	if (NULL == parent->children)
		return 0;

	// assign new child
	parent->children[childCount] = child;
	parent->children[childCount + 1] = NULL;
	child->parent = parent;

	return childCount + 1;
}

/*
 * Return the number of children a node has.
 */
int
DTchildCount(DTnode *node)
{
	int		n = 0;
	DTnode	**child = NULL;

	for (child = node->children; NULL != child; child++)
		n++;

	return n;
}