// QUEARRY.H [160929]
// Implement simple array-based queue.

// This code is to be included in code that needs queue datatype. Prior to
// include, there must be a typedef that defines type for Que_data.
// For example:
//	typedef int	Que_data;		// create queue filled with ints
//	#include "quearry.h"

#include "boolean.h"

// ##### Implementation of simple queue of type Stk_data #####

struct queue  {
	int			front;		// index of front element
	int			quecount;	// items in queue
	int			qarrsz;		// maximum size of array
	Que_data	*que;		// pointer to array of Que_data items
	};

typedef struct queue	Queue, *pQueue;


Queue *create_queue (int size)
// Create queue.
{
	Queue	*q = NULL;
	// First, check for idiocy
	if (size > 0)	{
		Que_data	*pqd = (Que_data *)malloc(size * sizeof(Que_data));
		if (pqd != NULL)	{
			// Memory for actual queue obtained; get memory for descriptor
			q = (pQueue) malloc (sizeof (Queue));
			if (q != NULL)	{
				// Got descriptor
				q->front = 0;		// initially empty
				q->quecount = 0;	// initially empty
				q->qarrsz = size;	// array size
				q->que = pqd;		// array to store queue items
				}
			}
		}
	return q;		// either pointer to queue descriptor or NULL
}//create_queue()


void destroy_queue (Queue **ppq)
// Destroy queue.  Pass address of queue pointer returned from create(); this
// way we can ensure pointer is cleared as well.
{
	// always apply PAI rule.
	if (ppq != NULL)	{
		Queue *pq = *ppq;		// get queue descriptor
		free (pq->que);			// free queue array
		free (pq);				// free queue descriptor
		*ppq = NULL;			// zero queue descriptor tag
		}
	return;
}//destroy_queue()


BOOL isQueueEmpty (pQueue q)
// Determine if queue currently empty
{
	BOOL	rslt = FALSE;
	if (q != NULL)	{
		rslt = q->quecount == 0;
		}
	return rslt;
}//isQueueEmpty()


BOOL isQueueFull (pQueue q)
// Determine if queue is full
{
	BOOL	rslt = FALSE;
	if (q != NULL)	{
		rslt = q->quecount >= (q->qarrsz);
		}
	return rslt;
}//isStackFull()


int removefront (pQueue q, Que_data *px)
// If possible, remove front element from queue pointed to by q.
// If successful, location at px will be updated and 1 will be returned;
// otherwise 0 will be returned and que_data item at px will not be changed.
{
	int		rslt = 0;
	if (q != NULL)	{
		// Anything to remove?
		if (!isQueueEmpty (q))	{
			*px = q->que[q->front++];
			q->quecount--;
			// wrap-around?
			if (q->front >= q->qarrsz)	q->front = 0;
			rslt = 1;
			}
		}
	return rslt;
}
		

int insert (pQueue q, Que_data x)
// If possible, insert new data element at end of queue.  If successful,
// return 1; otherwise return 0.
{
	int		rslt = 0;
	if (q != NULL)	{
		// Room for another item?
		if (!isQueueFull(q))	{
			// there is room.  Compute index of end position
			int   rear = q->front+q->quecount;
			if (rear >= q->qarrsz)	rear = rear % q->qarrsz;
			q->que [rear] = x;
			q->quecount++;
			rslt = 1;
			}
		}
	return rslt;
}

// ##### End simple queue implementation #####
