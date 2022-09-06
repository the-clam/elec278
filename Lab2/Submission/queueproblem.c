// queueproblem.c – Lab 02 – Carl, Lam

// Include required libraries.
#include <stdio.h>
#include <malloc.h>

// Defines for using bool.
#define bool    unsigned char
#define false   (unsigned char) 0
#define true    (unsigned char) 1

/* MULTIPLE QUEUE IMPLEMENTATION (adapted from code examples) */
// Structure definition for items, which are elements of queues.
struct item                     
{
	struct item		*next;      // Store pointer to next variable.
	int				value;      // Store value held on item.
};
typedef struct item		Item, *pItem;

// Structure definition for individual queues.
struct queue                    
{
    Item	*front;     // Pointer to front queue item.
    Item	*end;       // Pointer to end queue item.
    int		count;      // Number of items in queue.
};
typedef struct queue    Queue, *pQueue;

// Create new instance of queue.
pQueue newQueue()                                       
{
    pQueue thisQueue;
    thisQueue = (pQueue)malloc(sizeof(struct queue));       // Create new queue and allocate memory for it.
    if(thisQueue != NULL)                                   // Continue if new queue created successfully (not NULL).
    {
        thisQueue->front = NULL;                            // Set NULL front and end pointer (position for item not known yet).
        thisQueue->end = NULL;                              
        thisQueue->count = 0;                               // Set count of items to zero, as it is a new queue.
    }
    return thisQueue;                                       // Return pointer to new queue.
}

// Destroy specified queue.
void destroyQueue(pQueue queueToDestroy)                
{
    free(queueToDestroy);       // Free up memory allocated to that queue.
}

// Create new item, assign value to item, add item to end of specified queue.
bool queueInsert(pQueue targetQueue, int n)
{
	Item *pnew = (Item *)malloc(sizeof (struct item));                  // Create new item and allocate memory for it.
	bool result = false;                                                 
    if(pnew != NULL)                                                    // Continue if new item created successfully (not NULL). 
    {
		pnew->value = n;                                                // Initialize new item with required data.
		pnew->next = NULL;
		if(targetQueue->end != NULL) targetQueue->end->next = pnew;     // If there is another item in queue, make current end item point to new item.
		targetQueue->end = pnew;                                        // Update end pointer for queue to point to new item.
		if(targetQueue->front == NULL) targetQueue->front = pnew;       // If queue empty, new item is also first item.
		targetQueue->count++;                                           // Increment item count for queue.
		result = true;                                                  // Indicate queue item was set up successfully.
    }
	return result;                                                      // If operation is successful, return true, otherwise return false.
}

// Print all values of array in rows of 12, using %5d format.
void queuePrint(pQueue targetQueue)
{
    if(targetQueue->count <= 0) printf("Queue empty.");     // If queue is empty, indicate as such.
    Item *temp;                                             // Temporary pointer to go through queue.
    temp = targetQueue->front;                              // Point to front of desired queue.
    int counter = 0;                                        // Reset counter (so appropriate number of numbers can be outputted per line.)
    while(temp != NULL)                                     // Repeat until whole queue has been iterated through.
    {
        printf("%5d ", temp->value);                        // Print number with appropriate formatting.
        temp = temp->next;                                  // Point to next item in queue.
        counter++;                                          // Track number of items printed per line.
        if(counter >= 12)                                   
        {
            printf("\n");                                   // Create new line if 12 items on line.
            counter = 0;                                    // Reset counter for next row's output.
        }
    }
    printf("\n");                                           // New line to signify end of queue's data.
}

/* MAIN FUNCTION */
void main()
{
    pQueue queues[4];                                                       // Create array to hold four queues.
    for(int i = 0; i < 4; i++) queues[i] = newQueue();                      // Initialize four queues in an array to hold inputs.
    printf("Enter ONLY integers seperated by newlines or a space.\n");      // Print out instructions.
    printf("(Terminate input by entering a negative number):\n");
    int input = 0;                                                          // Variable to hold input.  
    while(input >= 0)                                                       // Take input until a negative value is inputted.
    {
        scanf("%d", &input);                                                // Scans and inserts input into appropriate queue.
        if      (input % 4 == 0) queueInsert(queues[0], input);
        else if (input % 4 == 1) queueInsert(queues[1], input);
        else if (input % 4 == 2) queueInsert(queues[2], input);
        else if (input % 4 == 3) queueInsert(queues[3], input);
        else    break;                                                      // If input doesn't fit above operations, break.
    }
    printf("Negative number inputted, outputting queues.\n\n");             // Message to indicate input has terminated.
    for(int i = 0; i < 4; i++)                                              // Print all queues.
    {
        printf("-------------------------------");
        printf("[QUEUE #%1d:]", i+1);
        printf("-------------------------------\n");
        queuePrint(queues[i]);
    }
    printf("\n");
    for(int i = 0; i < 4; i++) destroyQueue(queues[i]);                     // Free queue memory after use.
}