// TESTSORT.C [161111]
// This code used to test sort routines.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Array containing initial data.
#define	MAXINDEX	19			// how much actual data
int data [100]	= {
	44, 22,  3, 71, 16, 82,  1,  9, 99, 10,
	32, 18, 77, 28,  9, 17, 52, 61, 38, 12 };

// "Global" variables
int					verbose = 0;
long unsigned int	swaps = 0;			// may be lots of swaps

#include "L4_UTILITYCODE.c"
#include "L4_BUBBLESORT.c"
#include "L4_HEAPSORT.C"
#include "L4_INSTSORT.C"
#include "L4_MERGESORT.C"
#include "L4_QUICKSORT.C"
#include "L4_RADXSORT.C"
#include "L4_SELSORT.C"
#include "L4_SHELLSORT.C"

int main (void)
{
	//Variables
	int			rslt, max;
	clock_t		start, end;
	int			*pa;			// pointer to array;
	int			size;

	// Fetch data
	size = read_int_file ("RANDOM.TXT", &pa);
	size = read_int_file ("ASCENDING.TXT", &pa);
	size = read_int_file ("DESCENDING.TXT", &pa);
	
	// Reset number of swaps to 0.
	swaps = 0;

	// IF VERBOSE > 0, prints array out before sorting.
	if(verbose) printarray ("Array before any work done:", pa, 0, size-1, 10);

	// Check to see if array is sorted before.
	printf ("==Check array before sort\n");
	if(array_sorted(NULL, pa, 0, size-1, 1)) printf("Warning: Array is initially sorted\n");
	else printf("         Array is unsorted\n");

	swaps = 0;
	
	start = clock();
	//printf ("Bubble Sort\n");		rslt = bubblesort (pa, 0, size-1);           //OK
	//printf ("Insertion Sort\n");	rslt = insertionsort (pa, 0, size-1);        //OK
	//printf ("Heap Sort\n");		rslt = heapsort (pa, size);      //2B tested
	//printf ("Merge Sort\n");		rslt = mergesort (pa, 0, size-1);            //OK
	//printf ("Quicksort\n");		rslt = quicksort (pa, 0, size-1);            //OK
	//printf ("Radix sort\n");		rslt = radixsort (pa, size);			 	 //OK
	//printf ("Selection Sort (Iterative)\n");	rslt = selsortI (pa, 0, size-1); //OK
	//printf ("Selection Sort (Recursive)\n");  rslt = selsortR (pa, 0, size-1); //OK
	//printf ("Shell Sort\n");		rslt = ShellSort (pa, 0, size-1);            //OK
	end = clock();
	
	printf ("End time: %ld  Start time:  %ld  Diff: %ld\n",
				end, start, end-start);
	if (verbose || 1)
		printarray ("Final array:", pa, 0, size-1, 8);
	if (array_sorted(NULL, pa, 0, size-1, 1))
		printf ("==After sort, array is sorted\n");
	else	{
		printf ("Sort failed - array is not sorted\n");
		//printarray ("Sort error: ", pa, 0, size-1, 8);
		}
	printf ("Swaps:  %ld  CPU time:  %ld\n", rslt, end-start);
	

}//main()