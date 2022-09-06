// LAB3_BST.c - Lab 03 - Carl, Lam

#include <stdlib.h>
#include <stdio.h>
#include "LAB3_BST.h"

Node *initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created.
{
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	if (n != NULL)	{
		n->key = k;
		n->value = v;
		n->leftChild = NULL;
		n->rightChild = NULL;
		}
	return n;
}//initNode()


Tree *initTree(Key k, void *v)
// Set up new tree. Allocates memory for Tree structure, then
// calls initNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k,v);
	return t;
}//initTree()


void printTreeExplanation (void)
// Prints hint to reader what to expect on screen
{
	static int done = 0;
	if (!done)	{
		printf ("First time explanation of tree display:\n");
		printf ("Every node is displayed as a comma-separated pair within brackets:");
		printf (" (kk,vv)\n");
		printf ("where kk is the key and vv is the value\n");
		printf ("A tree starts with a curly bracket { and ends with a curly bracket }.\n");
		printf ("An empty tree will be {}\n");
		printf ("A tree with no children will be { (kk,vv),{},{} }\n");
		printf ("If either subtree is populated, it will be shown using the same ");
		printf ("technique as described above\n");
		printf ("(Hint: Start at root - and then match up all the remaining\n");
		printf ("brackets, then interpret what those bracket pairs are telling\n");
		printf ("you.)\n============\n\n");
		done = 1;
		}
}//printTreeExplanation()


void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
	// assume printTree magically knows the types in the tree node
	printTreeExplanation();
	// start of this tree
	printf("{");
	// values in the root node (assuming value is pointing to an integer)
	printf("(%ld,%d),", root->key, *(int*)root->value);
	
	// Now show left subtree or {} if there is no left subtree
	if (root->leftChild != NULL)	printTree(root->leftChild);
	else							printf("{}");
	// Marker between left and right subtrees		
	printf(",");
	// Now show right subtree or {} if there is no right subtree
	if (root->rightChild != NULL)	printTree(root->rightChild);
	else							printf("{}");
	// Close display of this tree with closing curly bracket	
	printf("}");
}//printTree()


Node *find (Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// Key value sought is smaller than current node key (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k,root->leftChild);	
}//find()


int insert(Key k, void *v, Node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
	int result = BST_FAIL;
	// this if statement can only be true with first root (root of whole tree)
	if (root == NULL)	{
		Node *n = initNode(k,v);
		root = n;
		return BST_SUCCESS;
		}
	
	// already exists in tree ==> can't insert
	if (root->key == k)
		result = BST_FAIL;
	else if (k < root->key) {
		// key value less than key value in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insert(k, v, root->leftChild);
		else {
			// new Node becomes the left subtree
			Node *n = initNode(k,v);
			root->leftChild = n;
			result = BST_SUCCESS;
			}
	} else if (k > root->key) {			// test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insert(k,v,root->rightChild);
		else {
			// no right subtree - new node becomes right subtree
			Node*n = initNode(k,v);
			root->rightChild = n;
			result = BST_SUCCESS;
			}
		}
	return result;	
}//insert()


int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see a conditional expression in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
	return (a>=b) ? a : b;
}//intmax()


int height(Node *root)
// Height definition:
// Height of an empty tree is -1.  Height of a leaf node is 0. Height of other
// nodes is 1 more than larger height of node's two subtrees.
{ 
	int	nodeheight = -1;	// This is the default case for an empty tree.
	if(root != NULL)		// When a NULL node is reached, that is the bottom of the tree. Stop recursion.
	{
		int left = height(root->leftChild);		// Both the left and right children are checked for height recursively.
		int right = height(root->rightChild);	
		nodeheight = intmax(left, right) + 1;	// Nodeheight will be equal to the "larger" side
	}
	return nodeheight; // Return the height of the tree.
}//height()


Node* findParentHelper (Key k, Node* root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
	Node *search; // Temporary node used to hold nodes being searched.
	// If either child present AND has key equal to target key, return current root as parent. 
	// This will end the recursion process.
	if((root->leftChild != NULL && root->leftChild->key == k) || (root->rightChild != NULL && root->rightChild->key == k)) return root;
	// If at least one grandchild of the left child, continue recursive search.
	if(root->leftChild != NULL && (root->leftChild->leftChild != NULL || root->leftChild->rightChild != NULL))
	{
		search = findParentHelper(k, root->leftChild);	// Traversing to left child.
		if(search != NULL) return search;				// If not NULL, then more children to search.
	}
	// Same as above but for right child.
	if(root->rightChild != NULL && (root->rightChild->leftChild != NULL || root->rightChild->rightChild != NULL))
	{
		search = findParentHelper(k, root->rightChild);	// Traversing to right child.
		if(search != NULL) return search;				// If not NULL, then more children to search.
	}
	return NULL; // Default case to return.
}//findparenthelper()


Node *findParent(Key k, Node *root)
// 
{
	// Deal with special special cases which could only happen for root
	// of whole tree
	if (root == NULL)	return root;	
	// real root doesn't have parent so we make it parent of itself
	if (root->key == k)	return root;	
	// root has no children
	if ((root->leftChild == NULL) && (root->rightChild == NULL)) 
			return NULL;
	
	// Deal with cases where root has at least one child
	return findParentHelper(k, root);
}//findParent()


void delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
{
	// Deletion has 3 cases - no subtrees, only left or right subtree, or both
	// left and right subtrees.
	Node *deleteNode = n;		// Copy of pointer to node being deleted. Makes it easier to refer to.

	if(deleteNode->leftChild != NULL && deleteNode->rightChild != NULL) // Cases with both subtrees.
	{ 
		// Pointers to traverse the tree.
		Node *currentNode = deleteNode;
		Node *searchNode = deleteNode->leftChild;
		// To satisfy BST delete with 2 nodes, find largest (rightmost) node on left subtree to replace the
		// node to be deleted. Traverse the left subtree until this is found (until a NULL node is found).
		// The node that will be found will be either a leaf or a node with only one child. 
		while(searchNode != NULL && searchNode->rightChild != NULL)
		{
			currentNode = searchNode; // If reached here, search node is not NULL, safe to set as current node.
			searchNode = searchNode->rightChild; // Continue traversing. If NULL is reached, this loop will not repeat.
		}
		// Found the rightmost key in the left subtree. Take this node's data and replace the node to be deleted.
		deleteNode->key = searchNode->key;
		deleteNode->value = searchNode->value;
		// Since we determined that at this point, the "replacement node" can either be a leaf or only have one child,
		// we can recursively call the delete function as these two scenarios are covered in the other else/elseifs
		// (and we have all the required function arguments to do so).
		delete(currentNode, searchNode);
	}
    else if(deleteNode->leftChild != NULL || deleteNode->rightChild != NULL) // Cases with only one subtree.
    {
		if(deleteNode->leftChild != NULL) // Left child.
		{
			// If the node being deleted is the left child of the parent, then splice to the parent's left. 
			if(p->leftChild == deleteNode) p->leftChild = deleteNode->leftChild;
			// Otherwise, splice to parent's right.
	    	if(p->rightChild == deleteNode) p->rightChild = deleteNode->leftChild;
		}
	    if(deleteNode->rightChild != NULL) // Right child.
		{
			// Same as above, except modified for the right side.
			if(p->leftChild == deleteNode) p->leftChild = deleteNode->rightChild;
	    	if(p->rightChild == deleteNode) p->rightChild = deleteNode->rightChild;
		}
	}
    else // Cases with no children.
    {
		// To delete a leaf node, replace it with pointer to NULL to remove any references to that leaf.
		if(p->leftChild == deleteNode) p->leftChild = NULL;
		if(p->rightChild == deleteNode) p->rightChild = NULL;
    }
    free(deleteNode); // Remove the node to be deleted from memory.
}//delete()


int withdraw(Key k, Node* root, Node* n)
// Withdraw does two things:
//	return a copy of the node with key k (and value v)
//	Delete the node with key k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);
	
	if (m != NULL)	{
		// create a copy of the node with the same key and value
		n = initNode(m->key,m->value);
		p = findParent(k,root);
		// can delete the node
		delete(p,m);
		return 1;
	}
	return 0;	
}//withdraw()