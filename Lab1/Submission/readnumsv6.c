// readnumsv6.c - Lab 01 - Carl, Lam

// This program reads numbers inputted by the user and adds them to a linkedlist, users can choose whether 
// the numbers are added to the front or back of the linkedlist, as well as indicate when they are finished
// with data entry. Version 6 is a combination of the features of all previous versions, with the addition
// of the deletion feature that allows for the removal of all nodes containing a specific value.

// Including the neccessary libraries.
#include <stdio.h>
#include <stdlib.h>

// Including manifest for quick reference.
#define	EXIT_OK		0
#define	EXIT_ERROR	-1
  
// Defining the struct for each node of the linkedlist.
struct node 
{
	struct node	*pnextnode;
	int			datavalue;
};

// Global pointer structs to be used by all functions. One points to the first element (head) of the linkedlist, 
// the second poins to the last element (tail) of the linkedlist.
struct node	*phead = NULL;
struct node *pback = NULL;


/** FUNCTIONS **/

struct node *pnew_node (int d)
// This function create a new node struct with the fields filled. The pointer to the new node is returned, unless
// node creation fails, in which case it will return NULL. 
{
	// Use malloc to allocate memory for the node and declare a new node struct.
	struct node	*pn = (struct node *) malloc (sizeof (struct node));

	// If the node creation is successful, fill in the struct fields.
	if (pn != NULL)
	{
		pn->datavalue = d; 		// Assign the value passed in as an argument to the datavalue field.
		pn->pnextnode = NULL;	// Initialize the nextnode pointer as NULL, as the node has not been added to
								// a linkedlist yet.
	}
	// If node creation is successful, a struct with fields filled in will be returned, otherwise a NULL node will
	//  be returned.
	return pn;
}// End of *pnew_node.


int insert_data_at_front (int d)
// Add a new node of data to the front of the linkedlist.
{
	// Call node creation function to create an isolated node struct with the datavalue of d and nextpointer NULL.
	struct node	*pn = pnew_node (d);

	// If a NULL node is returned, then node creation failed.
	if (pn == NULL)	return -1;

	// The nextnode of the new node is assigned to phead (so the nextnode of the new head points to the old head).
	// Then, the pointer of phead is given to the new node. There is no change to the order of the existing list.
	pn->pnextnode = phead;
	phead = pn;

	// If this is the first node being added, then the pback pointer will be NULL as there will be nothing after 
	// the new phead. If this is the case, then phead will be assigned the pback pointer as well.
	if (pback == NULL)	pback = pn;
	return 0;
}// End of insert_data_at_front().


int insert_data_at_end (int d)
// Add a new node of data to the end of the linkedlist.
{
	// Call node creation function to create an isolated node structure with the datavalue of d and nextpointer NULL.
	struct node	*pn = pnew_node (d);

	// If a NULL node is returned, then node creation failed.
	if (pn == NULL)	return -1;

	// If the list is currently empty (if pback is NULL), then the node will be added to the list by assigning it 
	// both titles of phead and pback.
	if (pback == NULL)	
	{
		pback = pn;
		phead = pn;
	}
	else
	{
		// If there are already nodes in the linkedlist, change the nextnode of the old pback node to point to the
		// new node. The nextnode of the new node can be left as NULL as it is at the end.
		pback->pnextnode = pn;
		// Assign the pback pointer to the new node.
		pback = pn;
	}
	return 0;
}// End of insert_data_at_end().

int remove_data (int d)
// Remove all instances of a specified value from the linkedlist.
{
	// Create pointer to hold temporary pointer for processing purposes. Initiate current value with head to start.
	struct node *pcur = phead;

	// Temporary variable used to hold previous node, in case we need to access it to splice it to the next node.
	struct node *pprev = NULL;
	
	// First, check to see if node it is empty. If it is, exit the function by returning 0. (Not an error)
	if(pcur == NULL)
	{
		return 0;
	}

	// Check to see if head node holds specified value. If true, shift head to next node until the head no longer 
	// contains the specified value.
	while(pcur != NULL && pcur->datavalue == d)
	{	
		phead = pcur->pnextnode; 	// Shift head to next node as the new head.
		free(pcur); 				// Free the old head memory slot.
		pcur = phead; 				// Set current value as new head.
	}
	
	// Iterate through the remainder of the linkedlist after the head.
	while(pcur != NULL)
	{
		// Check if current node matches value to be removed.
		if(pcur->datavalue == d)
		{
			// If it does, splice out the current node by connecting previous node to the next node.
			// This excludes the current node by routing the pointers around it.
			pprev->pnextnode = pcur->pnextnode;
			free(pcur);									// Free the memory held by the node to be removed. 
			pcur = pprev->pnextnode;					// Connect the previous pointer to the next node via pnextnode
														// to exclude the spliced node from the linkedlist.
		}
		else
		{
			// If the node does not need to be removed, save the current node into the "previous" node slot in case
			// it is needed to splice the next node out.
			pprev = pcur;
			pcur = pcur->pnextnode; // Move the current pointer to the next node.
		}
	}
	return 0;
}// End of remove_data().

void print_linked_list (void)
// Function to print out all data contents of the linkedlist in order.
{
	struct node	*ptemp;		// Temporary pointer used to iterate through nodes.
	int			count;		// Count the number of items displayed on the command window line.
	
	// If the linkedlist is empty, output appropriate message and end function.
	if (phead == NULL)
	{
		printf ("<EMPTY LIST>\n");
		return;
	}

	// If list is not empty, point the iterating pointer ptemp at the head of the list, print the data at that node, then
	// move the temp pointer to the next node in the list. Repeat this process until there are no more nodes to print.
	ptemp = phead;
	count = 0;				// Counts the number of items displayed in the command window line.
	while (ptemp != NULL)
	{
		printf ("%4d", ptemp->datavalue);
		if (ptemp->pnextnode != NULL)
		{
			printf ("->");
			count++;				// Increment the number of items on the command window line. 
			if (count > 12)			// If data is getting close to the edge of the window, start a new line and reset counter.
			{
				putchar ('\n');
				count = 0;
			}
		}
		else
		{
			putchar ('\n');
		}
		ptemp = ptemp->pnextnode; 	// Move to next node.
	}
	return;
}// End of print_linked_list().

void main (void)
{
	// Variables to hold user input.
	char	ch;
	int		d;
	int		going;

	// Print out instructions for user.
	printf ("On each line, enter letter F or B, followed by a space and\n");
	printf ("a number. F means the number is placed at the front of the\n");
	printf ("list and B means the number is placed at the back\n");
	printf ("To end your input, enter letter Q and any number.\n");

	going = 1;
	while (going)
	{
		scanf ("%c", &ch);			// Get letter in first position.
		scanf ("%d", &d);			// Get number after letter.
		while (getchar() != '\n');	// Skip remaining characters, up to and including newline.
		printf ("Received %c %d\n", ch, d);
		
		// Switch cases to determine appropriate function based on user input.
		switch (ch)
		{
			case 'Q':
			case 'q':
				going = 0;		// Q or q means end of input
				break;
			case 'F':
			case 'f':
				insert_data_at_front (d);
				break;
			case 'B':
			case 'b':
				insert_data_at_end (d);
				break;
			case 'D':
			case 'd':
				remove_data (d);
				break;
			default:
				fprintf (stderr, "ERROR: Invalid command --%c--\n", ch);
				break;
		}		
	}
	// User has completed input.
	print_linked_list ();
	printf ("====END====\n");
}// End of main().