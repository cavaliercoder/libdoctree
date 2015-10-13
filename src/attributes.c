#include "common.h"
#include "libdoctree.h"

/*
 * Allocate a new node. Returns NULL on error.
 */
DTattribute*
DTnewAtt(const DTchar *key, const DTchar *val, int flags)
{
	DTattribute	*att = NULL;

	// key must not be NULL or empty
	if (NULL == key || '\0' == *key)
		return NULL;

	att = DTalloc(NULL, sizeof(DTattribute));
	if (NULL == att)
		return NULL;

	att->flags = flags;

	att->key = DTstrdup(key);
	if (NULL == att->key) {
		DTfreeAtt(att);
		return NULL;
	}

	if (NULL == val)
		att->value = NULL;
	else {
		att->value = DTstrdup(val);
		if (NULL == att->value) {
			DTfreeAtt(att);
			return NULL;
		}
	}

	return att;
}

/*
 * Free an attribute.
 * The attribute is not removed from the parent by this function.
 */
void
DTfreeAtt(DTattribute *att)
{
	if (NULL == att)
		return;

	if (NULL != att->key)
		DTfree(att->key);

	if (NULL != att->value)
		DTfree(att->value);

	DTfree(att);
}

/*
 * Return the number of attributes owned by a node.
 */
int
DTattCount(DTnode *node)
{
	int			n = 0;
	DTattribute	**att = NULL;

	for (att = node->attributes; att && *att; att++)
		n++;

	return n;
}

/*
 * Appends an attribute to a node. 
 * 
 * Returns the number of attributes owned by the node after the append operation
 * is complete or -1 on error.
 *
 * No checking for duplicate keys is performed as duplicate keys are allowed.
 */
int
DTappendAtt(DTnode *node, DTattribute *att)
{
	int attCount = 0;

	// count children
	attCount = DTattCount(node);

	// check for NULLs
	if (NULL == node || NULL == att)
		return -1;

	// realloc attribute array with an extra slot for the new attribute and NULL
	// terminator
	node->attributes = realloc(node->attributes, sizeof(DTattribute*) * (attCount + 2));
	if (NULL == node->attributes)
		return -1;

	// assign new attribute
	node->attributes[attCount] = att;
	node->attributes[attCount + 1] = NULL;

	att->parent = node;

	return attCount + 1;
}

/*
 * Gets the value of the given attribute.
 * Returns NULL of the attribute is not set.
 */
DTattribute*
DTgetAtt(DTnode *node, const DTchar *key)
{
	DTattribute	**att = NULL;
	
	for (att = node->attributes; att && *att; att++)
		if (0 == DTstrcmp(key, (*att)->key))
			return *att;

	return NULL;
}

/*
 * Creates or updates a node with the given attribute.
 * Returns the updated count of attributes owned by the node or -1 on error.
 */
int
DTsetAtt(DTnode *node, const DTchar *key, const DTchar *val, int flags)
{
	DTattribute	*att = NULL;
	int			count = 0;

	// check for existing attribute
	att = DTgetAtt(node, key);

	if (NULL == att) {
		// allocate a new attribute
		att = DTnewAtt(key, val, flags);
		if (NULL == att)
			return -1;

		count = DTappendAtt(node, att);
	} else {
		// update existing attribute
		att->flags = flags;
		
		if (NULL != att->value)
			DTfree(att->value);
		att->value = NULL;

		if (NULL != val) {
			att->value = DTstrdup(val);
			if (NULL == att->value)
				return -1;			
		}

		count = DTattCount(node);
	}

	return count;
}
