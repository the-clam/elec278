// Building BST w/ key and value, both being strings.

// Include neccessary libraries.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* NODE DEFINITION AND FUNCTIONS */
// Definition of specified treenode, use typedef to reduce the number of times that struct has to be typed.
typedef struct _trnode TreeNode, *pTreeNode;
struct _trnode	{
	char		*pname;			// Parameter name.
	char		*pvalue;		// Parameter value.
	TreeNode	*leftChild;		// Left subtree pointer.
	TreeNode	*rightChild;	// Right subtree pointer.
};

// Define the size of a node as SZ_NODE.
#define SZ_TRNODE	(sizeof (TreeNode))

// Create new node, by passing in a key and value by parameters. Value can be excluded during node creation but
// key required. Key-only is good for binary data, either it exists or it doesn't.
TreeNode *CreateNode (char *key, char *value)
{
	TreeNode *pn = NULL; // Temp pointer to configure the new node, default is NULL.

	// If key is NULL, return skip to returning NULL node. Allows for parameters inform by either existing or
	// not existing.
	if (key != NULL)
	{
		pn = (TreeNode *) malloc (SZ_TRNODE); 					// Allocate appropriate amount of space for node.
		if (pn) 												// If node is not NULL.
		{
			pn->pname = strdup (key);							// Fill pname value w/ copy of key.
			pn->pvalue = value==NULL ? NULL : strdup (value);	// Fill pvalue value w/ copy of value.
			pn->leftChild = NULL;								// Default NULL leftChild for a new node.
			pn->rightChild = NULL;								// Default NULL leftChild for a new node.
		}
	}
	return pn; // Return pointer to new node created if at least key provided.
}

// Deletes node from structure, however, does not delete subtrees of the node. (Should already have been dealt
// with before this process).
int DeleteNode (TreeNode *ptn)
{
	int rslt = -1;					// Return FAIL by default.
	if (ptn != NULL)				// Checks if node being passed actual exists.
	{
		free (ptn->pname);			// Free up name from memory.
		if (ptn->pvalue != NULL)	// IF there is a pvalue, free from memory.
			free (ptn->pvalue);		
		free (ptn);					// Free node after freeing the data in the node.
		rslt = 0;					// Change result to PASS.
	}
	return rslt;
}

// Function used to order nodes. Takes 2 nodes, compares key values with strcmp(), returns result in an int
// variable pointer to by prslt.
int CompareNodes (TreeNode *psrc, TreeNode *pdst, int *prslt)
{
	if ((psrc == NULL) || (pdst == NULL) || (prslt == NULL))	return -1; // Return FAIL if any parameters are NULL.
	// strcmpi() works by returning a value of -1, 0, or 1. 
	// If -1, first param < second. If 0, both params are equal. If 1, first param > second. 
	*prslt = strcmpi(psrc->pname, pdst->pname);
	return 0;	// Return 0 if operation PASS.
}

/* TREE DEFINITION AND FUNCTIONS */
// Basic definition of tree. Only needs to include pointer to root of the tree.
// Typedef at end to remove need to type struct every time.
typedef struct _tree 
{
	TreeNode *root;
} Tree;

// Insert node pointed to by parameter pnew, into tree w/ root node pointed to pointer pointed to by proot. proot can
// be pointer to root, left, or right (can be tree or subtrees).
int insert_node (TreeNode *pnew, TreeNode **proot)
{
	TreeNode	*pr;		// Holding pointer to hold existing nodes for comparisons.
	int		rslt = -1;		// Default to FAIL return value.
	int		cmprslt;		// Int to hold comparison results (-1, 0, 1).
	
	if ((proot == NULL) || (pnew == NULL))	return rslt; // If either value passed in is NULL, return FAIL.

	// If tree being pointed to by **proot is empty, then this is the first node of the tree.
	if (*proot == NULL)	
	{
		*proot = pnew;		// Point the root pointer for the tree to the new "first" node.
		rslt = 0;			// Return PASS value.
		printf (" --- Value %s inserted at root\n", pnew->pname);
	}
	// If not empty tree, need to determine where to put the node based on its integer value versus the integer value
	// of the already existing node.
	else
	{
		pr = *proot;	// Get pointer of the root being passed in, hold temporarily.

		// Determine node value im comparison to current root node value. Equal is rejected.
		if (CompareNodes (pnew, pr, &cmprslt) == 0)		// If -1, first param (new) < second (root). 
														// If 0, both params are equal. 
														// If 1, first param > second. 
		{
			if (cmprslt > 0) 	// New value > root value, goes into right subtree.
			{
				printf (" --- %s goes into Right subtree of value %s\n", pnew->pname, pr->pname);
				rslt = insert_node (pnew, &(pr->rightChild));
			}
			else if (cmprslt < 0)	// New value < root value, goes into left subtree.
			{
				printf (" --- %s goes into Left subtree of value %s\n", pnew->pname, pr->pname);
				rslt = insert_node (pnew, &(pr->leftChild));
			}
		}
	}
	return rslt; // If values equal, default "error" returned.
}

// Prints tree values using pre-order: Node Value, Left, Right.
void print_preorder (TreeNode *pn)
{
	if (pn == NULL)	return; 			// If node node pointed to is NULL, return nothing.	
	printf (" %s\n ", pn->pname);		// Print node name.
	print_preorder (pn->leftChild);		// Go left and print the tree node there.
	print_preorder (pn->rightChild);	// Go right and print the tree node there.
}
	
// Prints tree values using post-order: Left, Right, Node Value.
void print_postorder (TreeNode *pn)
{
	if (pn == NULL)	return;				// If node node pointed to is NULL, return nothing.	
	print_postorder (pn->leftChild);	// Go left and print the tree node there.
	print_postorder (pn->rightChild);	// Go right and print the tree node there.
	printf (" %s\n", pn->pname);		// Print node name.
}

// Prints tree values using in-order: Left, Node Value, Right.
void print_inorder (TreeNode *pn)
{
	if (pn == NULL)	return;				// If node node pointed to is NULL, return nothing.
	print_inorder (pn->leftChild);		// Go left and print the tree node there.
	printf (" %s\n", pn->pname);		// Print node name.
	print_inorder (pn->rightChild);		// Go right and print the tree node there.
}

/* MAIN FUNCTION */
// Test code to illustrate how binary search tree works with key and data being strings. We use a test file that
// resembles a DOS/Windows system configuration (INI) file.
int main (void)
{
	Tree		mytree = {NULL};		// Declare a new instance of tree with a NULL root.
	TreeNode 	*pnode;					// Temp node to build new nodes in, for inserting purposes.
	
	
	FILE		*fp;					// Pointer to file to be opened.
	char		*p, *pname, *pvalue;	// Temp pointers to hold string values.
	char		*pbuff;					// Buffer to read data file.
	
	pbuff = (char *)malloc(256);		// Get buffer to read data file into.

	// Cannot buffer file, return FAIL.
	if (pbuff == NULL)
	{
		fprintf (stderr, "ERROR: Cannot get memory for buffer\n");
		return -1;
	}
	
	// Open the TEST.ini file for reading.
	fp = fopen ("TEST.ini", "r");
	
	// If file cannot be opened, return FAIL.
	if (fp == NULL)
	{
		fprintf (stderr, "ERROR: Cannot open data file\n");
		return -1;
	}
	
	// Indefinite loop to read and insert data into BST until no more data to read.
	for (;;)
	{
		p = fgets (pbuff, 256, fp);	// Read maximum of 256 characters, line by line.
		if (p == NULL)	break;		// If there is NULL (no more data), break out of loop.
		while (*p == ' ')	p++;	// If the current char is empty space, keep skipping until it is actual char.
		pname = p;					// 
		p++;
		while (*p != '=')	p++;
		*p = '\0';
		p++;
		while (*p == ' ')	p++;
		pvalue = p;
		p++;
        while (*p != '\n' && *p != '\r') p++;
		*p = '\0';
		printf ("Name: %15s   Value: %s\n", pname, pvalue);
		pnode = CreateNode (pname, pvalue);
		insert_node (pnode, &mytree.root);
	}

	// Close the file being read.
	fclose (fp);

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




