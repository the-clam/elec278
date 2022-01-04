// TESTSORT.C [161111]
// This code used to test sort routines.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// "Global" variables
int					verbose = 0;
long unsigned int	swaps = 0;			// may be lots of swaps

// Files required to run all the sorts.
#include "L4_UTILITYCODE.C"
#include "L4_QUICKSORT2.C"

int main (void)
{
	int			rslt, max;
	clock_t		start, end;
	int			*pa;			// Pointer to array to hold values.
	int			size;

	// Create string table to hold the table headers and text to be outputted later.
	char *textTable[4][3];
	char string[20];

	// Create int table to hold number of swaps and time required to use swap.
	int dataTable[8][6];

	// Populate table header rows.
	textTable[0][0] = "Lam,Carl";
	textTable[0][1] = "Size of dataset";
	textTable[0][2] = itoa(read_int_file ("RANDOM.TXT", &pa),string,10);
	textTable[1][0] = "";
	textTable[1][1] = "Elapsed time";
	textTable[1][2] = "Number of swaps";
	textTable[2][0] = "Original Quicksort";
	textTable[3][0] = "Modified Quicksort";

	for(int sortmode = 0; sortmode < 2; sortmode++)
	{
		// Fetch data from specified file.
		size = read_int_file ("RANDOM.TXT", &pa);
		printf("============== RANDOM.TXT ==============\n");

		// IF VERBOSE is active, prints array out before sorting.
		if(verbose) printarray ("Array before any work done:", pa, 0, size-1, 10);

		// Check to see if array is sorted before.
		printf ("[CHECK] Is array initially sorted?\n");
		if(array_sorted(NULL, pa, 0, size-1, 1)) printf("WARNING: Array initially sorted!\n");
		else printf("Array not initially sorted.\n");
		
		// Log timer and reset swaps before the sort occurs.
		start = clock();
		swaps = 0;

		printf("\n[USING] ");

		// Select appropriate quicksort method based on current iteration number.
		switch(sortmode)
		{
			case 0:
				printf ("Quicksort\n");
				rslt = quicksort (pa, 0, size-1);
				break;
			case 1:
				printf ("Modified Quicksort\n");
				rslt = modified_quicksort (pa, 0, size-1);
				break;
		}

		// Log time after sort is completed.
		end = clock();

		// IF VERBOSE is active, print out the final array.
		if (verbose) printarray ("\nFinal array:", pa, 0, size-1, 8);

		// Print out the amount of time and number of swaps used to sort.
		printf ("End time: %ld, Start time: %ld, Diff: %ld\n", end, start, end-start);
		printf ("Swaps:  %ld  CPU time:  %ld\n", rslt, end-start);

		// Check to see if array is properly sorted.
		printf("\n[CHECK] Is array properly sorted?\n");
		if (array_sorted(NULL, pa, 0, size-1, 1)) printf ("Array is sorted.\n");
		else 
		{
			printf("WARNING: Array is not sorted!");
			printarray ("Sort error: ", pa, 0, size-1, 8);
		}
		printf("========================================\n\n");

		// Input data into data table.
		dataTable[sortmode][1] = end-start;
		dataTable[sortmode][2] = swaps;

		free(pa);
	}

	// Code to output to table to text file.
	char *filename = "LAB4_PART3.TXT";
	FILE *fp = fopen(filename, "w");
	if(fp==NULL)
	{
		printf("Could not open output file.");
		exit(1);
	}

	//Print out the entire data output table.
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(i < 2)
			{
				fprintf(fp, "%-25s",textTable[i][j]);
				printf("%-25s", textTable[i][j]);
			}
			else
			{
				if(j < 1)
				{
					fprintf(fp, "%-25s",textTable[i][j]);
					printf("%-25s", textTable[i][j]);
				}
				else
				{
					fprintf(fp,"%-25d", dataTable[i-2][j]);
					printf("%-25d", dataTable[i-2][j]);
				}
			}
		}
		fprintf(fp, "\n");
		printf("\n");
	}
	printf("\n");
	fclose(fp);
}//main()