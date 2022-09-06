// Stack-UsingQueue.C [181209]
// An odd example - implementation of a stack using a queue. Given ordering
// difference, requires a lot of shuffling around.

#include <stdio.h>

#define bool	unsigned char
#define	false	(unsigned char) 0
#define true	(unsigned char) 1

bool qempty (void);
bool qfull (void);
bool enqueue (int n);
bool dequeue (int *n);
void qprint (void);

#include "Queue-IncludeVersion.c"


int		stkcount = 0;

int push (int n)
{
	if (qfull ())	return -1;
	enqueue (n);
	stkcount++;
	return 0;
}

int pop (int *n)
{
	int		i;
	if (qempty())	return -1;
	// Last one pushed is at end of queue, so shuffle all but last one
	for (i=0; i<stkcount-1; i++)	{
		int tmp;
		dequeue (&tmp);
		enqueue (tmp);
		}
	dequeue (n);
	stkcount--;
	return 0;
}

int main(void)
{
    int		i, j;
	for (i=0; i<10; i++)	push (i);
	while (pop(&j) != -1)	{
		printf ("%d\n", j);
		}
    return 0;
}

