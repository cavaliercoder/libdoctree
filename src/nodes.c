#include "common.h"
#include "libdoctree.h"

/*
 * Allocate a new node. Returns NULL on error;
 */
DTnode *
DTnewNode(DTnode *parent, const DTchar *label, int flags)
{
	DTnode	*node = NULL;

	// label must not be NULL or empty
	if (NULL == label || '\0' == *label)
		return NULL;

	// allocate
	node = DTalloc(NULL, sizeof(DTnode));
	if (NULL == node)
		return NULL;

	node->flags = flags;

	// duplicate and assign label
	node->label = DTstrdup(label);
	if (NULL == node->label) {
		DTfreeNode(node);
		return NULL;
	}

	// assign parent
	if (NULL != parent) {
		if (-1 == DTappendNode(parent, node)) {
			DTfreeNode(node);
			return NULL;
		}
	}

	return node;
}

/*
 * Free a node and all of its descendants.
 */
void
DTfreeNode(DTnode *node)
{
	DTnode		**child = NULL;
	DTattribute	**att = NULL;

	if (NULL == node)
		return;

	for (att = node->attributes; att && *att; att++)
		DTfreeAtt(*att);
	
	for (child = node->children; child && *child; child++)
		DTfreeNode(*child);
	
	if (NULL != node->label)
		DTfree(node->label);

	DTfree(node);
}

/*
 * Return the number of children owned by a node.
 */
int
DTchildCount(DTnode *node)
{
	int		n = 0;
	DTnode	**child = NULL;

	for (child = node->children; child && *child; child++)
		n++;

	return n;
}


int
DTnodeHasChildren(DTnode *node)
{
	return (node->children && *node->children);
}

int
DTnodeHasAtts(DTnode *node)
{
	return (node->attributes && *node->attributes);
}

/*
 * Append a node to another node.
 *
 * Returns the number of child nodes owned by the parent after the append
 * operation is complete or -1 on error.
 */
int
DTappendNode(DTnode *parent, DTnode *child)
{
	int childCount = 0;

	// check for NULLs
	if (NULL == parent || NULL == child)
		return -1;

	// count children
	childCount = DTchildCount(parent);

	// realloc child array with an extra slot for the new child and NULL
	// terminator
	parent->children = DTalloc(parent->children, sizeof(DTnode*) * (childCount + 2));
	if (NULL == parent->children)
		return -1;

	// assign new child
	parent->children[childCount] = child;
	parent->children[childCount + 1] = NULL;
	child->parent = parent;

	return childCount + 1;
}
