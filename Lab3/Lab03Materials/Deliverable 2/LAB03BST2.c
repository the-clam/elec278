// LAB03BST2.c - Lab 03 - Carl, Lam

// ***************************************
// Filenames for the functions to be run.
#define readFile    "./IDENTS.TXT"
#define deleteFile  "./DELETES.TXT"
#define lookupFile  "./LOOKUPS.TXT"
// ***************************************

// Include neccessary libraries.
#include "LAB3_BST.h"

int numNodes = 0;

/* BINARY SEARCH TREE FUNCTIONS */
// Function to read data from a txt file named "IDENTS.txt".
Tree* inputIdents()
{
    FILE *fp = fopen(readFile, "r");  // Attempt to open input file for BST as specified in defines.
    // If file cannot be opened, indicate as such and terminate program.
    if(fp == NULL)
    {
        printf("Could not open ident file. Exiting program.\n");
        exit(0);
    }
    
    char inputline[128];                // Allocate a memory slot large enough to hold data from a line.
    const char seperator[3] = " \n";    // Newline indicates a new line of input data.
    
    Tree* identTree = NULL;             // Create a tree to hold all of the data.

    // Variables to hold the input values as they are inputted.
    int key;                            
    char *val;
    char *copyVal;

    // Iteration through every line.
    for(;;)
    {
        // Input line from text file. If it is NULL, end of file has been reached, so break.
        if(fgets(inputline, 128, fp) == NULL) break;
        
        // Seperates the input line into two different tokens.
        key = atoi(strtok(inputline, seperator));
        val = strtok(NULL, seperator);

        // Deep copy ensures there are no connections to the original variable.
        copyVal = malloc(strlen(val)+1); // Allocate the amount of space needed to hold the password value.
        strcpy(copyVal, val); // Deepcopy val (from inputline) into tempVal (seperate variable).

        if(numNodes == 0) // If there are no nodes, initiate new tree.
        {
            identTree = initTree(key,copyVal); 
            numNodes++;
        }
        else if(find(key, identTree->root) == NULL) // If no node with current key exists.
        {
            insert(key,copyVal,identTree->root); // Input into existing tree.
            numNodes++; // Increase count of nodes in BST.
        }
        else if(find(key, identTree->root) != NULL) // If node with current key already exists.
        {
            find(key, identTree->root)->value = copyVal; // Replace old value with new value.
        }
    }
    printf("Input complete.\n");
    printf("BST NODES: %d\n", numNodes); // Print required status report.

    // Verify if BST is built properly.
    if(verifyBST(identTree->root))
    {
        printf("BST is valid. Continuing...\n");
    }
    else
    {
        printf("BST is not valid. Exiting program.\n");
        exit(0);
    }
    
    return identTree; // Return tree.
}

void runDeletes(Tree* tree)
{
    FILE *fp = fopen (deleteFile, "r"); // Attempt to open input file for deletes as specified in defines.
    // If file cannot be opened, indicate as such and terminate program.
    if(fp == NULL)
    {
        printf("Could not open delete file. Exiting program.\n");
        exit(0);
    }

    char inputline[128];
    const char seperator[3] = " \n";

    Node *deleteNode = NULL;

    // Variable to hold the input values as they are inputted.
    int key;
    
    for (;;)
    {
        // Input line from text file. If it is NULL, end of file has been reached, so break.
        if (fgets (inputline, 128, fp) == NULL) break;
        key = atoi(strtok(inputline, seperator)); // Gets the input token for the delete function.
        deleteNode = find(key, tree->root); // Find the node to be deleted.

        if(deleteNode != NULL) // If there is a valid node to delete, then continue.
        {
            withdraw(key,tree->root, deleteNode); // Removes the node with the specified key from the tree.
            if(find(key, tree->root) == NULL) // Verify that the node with the specific key does not exist any more.
            {
                numNodes--; // Decrease number of nodes.
            }
        }
    }
    printf("Deletes complete.\n");
    printf("NODES AFTER DELETES: %d\n", numNodes);
    
    // Verify if BST is still built properly.
    if(verifyBST(tree->root))
    {
        printf("BST is valid. Continuing...\n");
    }
    else
    {
        printf("BST is not valid. Exiting program.\n");
        exit(0);
    }
}

void runLookups(Tree* tree)
{
    FILE *fp = fopen (lookupFile, "r"); // Attempt to open input file for deletes as specified in defines.
    // If file cannot be opened, indicate as such and terminate program.
    if(fp == NULL)
    {
        printf("Could not open delete file. Exiting program.\n");
        exit(0);
    }

    char inputline[128];
    const char seperator[3] = " \n";

    Node *lookupNode = NULL;

    // Variable to hold the input values as they are inputted.
    int key;

    printf("Credential Lookups:\n");

    for(;;)
    {
        // Input line from text file. If it is NULL, end of file has been reached, so break.
        if (fgets (inputline, 128, fp) == NULL) break;
        key = atoi(strtok(inputline, seperator)); // Gets the input token for the delete function.
        lookupNode = find(key, tree->root);

        // Output appropriate message based on lookup results.
        if(lookupNode == NULL) printf("<NOT FOUND>\n");
        else printf("ID %010d  PASSWORD %12s\n", lookupNode->key, lookupNode->value);
    }
}

// Function to check whether a tree is a binary search tree, returns true if true.
int verifyBST(Node* node)
{   
    // If the node is NULL, it is part of a valid BST because it has < 2 subtrees.
    if(node == NULL) return 1; 
    // If node is small than its left child, it is not part of a valid BST.
    else if(node->leftChild != NULL && (node->key < node->leftChild->key)) return 0;
    // If node is greater than its right child, it is not part of a valid BST.
    else if(node->rightChild != NULL && (node->key > node->rightChild->key)) return 0;
    // If the node fails any of the above tests, the BST is no longer valid.
    return 1;
}

/* MAIN FUNCTION */
void main(void)
{
    printf("-----------------------------------\n");
    Tree* identTree = inputIdents(); // Create BST and fill it with information from txt file.
    printf("-----------------------------------\n");
    runDeletes(identTree); // Delete IDs & passwords specified in the txt file from the BST.
    printf("-----------------------------------\n");
    runLookups(identTree); // Look up IDs and passwords and output to the terminal.
    printf("-----------------------------------\n");
}