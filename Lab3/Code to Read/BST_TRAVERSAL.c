// Building a binary search tree. Each node contains one integer as data (also as key),
// to explore how tree traversals work. Pay attention to double pointers. 
// Main points:
// - Look at simplified structure used to point to top of tree.
// - Look at simplified version of node - one piece of data controls the ordering.
//
// Basic definition of struct node for free.
// Bare minimum - two pointers to left/right subtrees and one data item.
//
//    ppNode         pNode root     Node
//    +-------+      +-------+      +--------+
//    |     o------->|     o------->| value  |
//    +-------+      +-------+      +--------+
//                                  |  left  |
//                                  +/-------+
//                                  / right  |
//                                 /+-------\+
//                                /          \
//                            left           right
//                           subtree        subtree

// Include neccessary libraries.
#include <stdlib.h>
#include <stdio.h>

/* NODE DEFINITION AND FUNCTIONS */
// Basic definition of a tree node. Bare minimum has left and right pointers, and
// data value. Includes typedef to remove need for repeatedly typing struct. pNode
// and ppNode also included (pointer to pointer of node). Reference diagram above.
typedef struct node	
{
	int				value;
	struct node		*leftChild, *rightChild;
} Node, *pNode, **ppNode;

// Define size of node into SZ_NODE.
#define SZ_NODE	(sizeof (struct node))

// Creates new node with value v and NULL pointers for left and right child. Returns
// pointer to this newly created node, or NULL if creation failed.
Node *newNode (int v)
{
	Node	*pn;
	pn = (Node *) malloc (SZ_NODE);
	if (pn)
	{
		pn->value = v;
		pn->leftChild = NULL;
		pn->rightChild = NULL;
	}
	return pn;
}

/* TREE DEFINITION */
// Basic definition of tree. Only needs to include pointer to root of the tree.
// Typedef at end to remove need to type struct every time.
typedef struct Tree
{
	Node *root;
} Tree;



/* TREE FUNCTIONS */
// Insert node pointed to by *pnew into tree that has root node pointer to by **proot.
// **proot will point to a root, left, or right in a node (pointer to a tree or subtree).
int insert_node (Node *pnew, Node **proot)
{
	Node	*pr;			// Holding pointer to hold existing nodes for comparisons. 
	int		rslt = -1;		// Return FAIL by default.

	if (proot == NULL || pnew == NULL) return rslt; // Return FAIL if either NULL.

	// If tree being pointed to by **proot is empty, then this is the first node of the tree.
	if (*proot == NULL)		
	{
		*proot = pnew;		// Point the root pointer for the tree to the new "first" node.
		rslt = 0;			// Insert successful.
		printf (" --- Value %d inserted at root of subtree\n", pnew->value);
	}
	// If not empty tree, need to determine where to put the node based on its integer value
	// versus the integer value of the already existing node.
	else
	{
		pr = *proot;		// Get pointer of the root being passed in, hold temporarily.

		// Determine node value im comparison to current root node value. Equal numbers rejected.		
		if (pnew->value > pr->value)
		{
			// New value > root value, goes into right subtree.
			printf (" --- %d goes into Right subtree of value %d\n", pnew->value, pr->value);
			// Command to insert node will return the whether the command is successful.
			rslt = insert_node (pnew, &(pr->rightChild));
		}
		else if (pnew->value < pr->value)
		{
			// New value < root value, goes into left subtree.
			printf (" --- %d goes into Left subtree of value %d\n", pnew->value, pr->value);
			// Command to insert node will return the whether the command is successful.
			rslt = insert_node (pnew, &(pr->leftChild));
		}
	}
	return rslt; // If values equal, default "error" returned.
}

// Prints tree values using pre-order: Node, Left, Right.
void print_preorder (Node *pn)
{
	if (pn == NULL)	return;				// If node node pointed to is NULL, return nothing.
	printf (" %d ", pn->value);			// Print the value of the node.
	print_preorder (pn->leftChild);		// Go left and print the tree node there.
	print_preorder (pn->rightChild);	// Go right and print the tree node there.
}

// Print tree values based on post-order: Left, Right, Node.
void print_postorder (Node *pn)
{
	if (pn == NULL)	return;				// If node node pointed to is NULL, return nothing.
	print_postorder (pn->leftChild);	// Go left and print the tree node there.
	print_postorder (pn->rightChild);	// Go right and print the tree node there.
	printf (" %d ", pn->value);			// Print the value of the node.
}

// Print tree values based on in-order: Left, Node, Right.
void print_inorder (Node *pn)
{
	if (pn == NULL)	return;				// If node node pointed to is NULL, return nothing.
	print_inorder (pn->leftChild);		// Go left and print the tree node there.
	printf (" %d ", pn->value);			// Print the value of the node.
	print_inorder (pn->rightChild);		// Go right and print the tree node there.
}

void print_compressed ()
{
}

/* TREE BUILDING DATA */
/* Remove comment from one of the next two lines to choose a set to use. */
//#define USE_ARBITRARY
#define USE_CLASS_DATA

// Random set of integers.
#ifdef USE_ARBITRARY
#define	DATASZ	20
int data [20]	=	{
	55, 62, 47, 12, 56,	72, 99, 18, 43, 51,
	38, 83, 41, 16, 15, 66, 91, 81, 71, 61
	};
#endif

// This is the data used in class.
#ifdef USE_CLASS_DATA
#define	DATASZ	14
int data [14]	=	{
	28,  15,  37,   4,  25,  32,  46,  3,  12,  20,
    30,  34,  14,  23
	};
#endif

/* MAIN FUNCTION */
void main (void)
{
	Tree	mytree = {NULL};	// Declare a new instance of tree with a NULL root.
	Node	*pnode; 			// Temp node to build new nodes in, for inserting purposes.
	
	// Insert selected data into tree.
	for (int i=0; i<DATASZ; i++)
	{
		printf ("Inserting value %d into BST\n", data[i]); 
		pnode = newNode (data[i]); // First build node with value.
		int rslt = insert_node (pnode, &mytree.root); // Insert node into tree.
		if (rslt) printf ("Problem inserting %d\n", data[i]);
	}

	// Print out mytree.
	printf ("Inorder Traversal\n");
	print_inorder(mytree.root);
	printf ("\n----------\n");
	printf ("Preorder Traversal\n");
	print_preorder(mytree.root);
	printf ("\n----------\n");
	printf ("Postorder Traversal\n");
	print_postorder(mytree.root);
	printf ("\n----------\n");
}




