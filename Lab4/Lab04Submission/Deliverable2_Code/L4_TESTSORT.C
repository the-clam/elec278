// TESTSORT.C [161111]
// This code used to test sort routines.

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Array containing initial data.
#define	MAXINDEX	19			// how much actual data
int data [100]	= {
	44, 22,  3, 71, 16, 82,  1,  9, 99, 10,
	32, 18, 77, 28,  9, 17, 52, 61, 38, 12 };

// "Global" variables
int					verbose = 0;
long unsigned int	swaps = 0;			// may be lots of swaps

// Files required to run all the sorts.
#include "L4_UTILITYCODE.c"
#include "L4_BUBBLESORT.c"
#include "L4_HEAPSORT.C"
#include "L4_INSTSORT.C"
#include "L4_MERGESORT.C"
#include "L4_QUICKSORT.C"
#include "L4_SELSORT.C"
#include "L4_SHELLSORT.C"

int main (void)
{
	int			rslt, max;
	clock_t		start, end;
	int			*pa;			// Pointer to array to hold values.
	int			size;

	// Create string table to hold the table headers and text to be outputted later.
	char *textTable[11][7];
	char string[20];

	// Create int table to hold number of swaps and time required to use swap.
	int dataTable[8][6];

	// Populate table header rows.
	textTable[0][0] = "Lam,";
	textTable[0][1] = "Carl";
	textTable[0][2] = "Dataset size:";
	textTable[0][3] = itoa(read_int_file ("RANDOM.TXT", &pa),string,10);
	textTable[0][4] = "";
	textTable[0][5] = "";
	textTable[0][6] = "";
	textTable[1][0] = "";
	textTable[1][1] = "RANDOM";
	textTable[1][2] = "";
	textTable[1][3] = "ASCENDING";
	textTable[1][4] = "";
	textTable[1][5] = "DESCENDING";
	textTable[1][6] = "";
	textTable[2][0] = "Sort";
	textTable[2][1] = "Elapsed Time";
	textTable[2][2] = "Number of Swaps";
	textTable[2][3] = "Elapsed Time";
	textTable[2][4] = "Number of Swaps";
	textTable[2][5] = "Elapsed Time";
	textTable[2][6] = "Number of Swaps";
	textTable[3][0] = "Bubble Sort";
	textTable[4][0] = "Insertion Sort";
	textTable[5][0] = "Heap Sort";
	textTable[6][0] = "Merge Sort";
	textTable[7][0] = "Quick Sort";
	textTable[8][0] = "Radix Sort";
	textTable[8][0] = "Insertion Sort";
	textTable[9][0] = "Selection Sort (I)";
	textTable[10][0] = "Selection Sort (R)";
	textTable[11][0] = "Insertion Sort";
	
	for(int fileSelect = 0; fileSelect < 3; fileSelect++)
	{
		// Variables for use in data copying to table.
		

		for(int sortmode = 0; sortmode < 8; sortmode++)
		{		
			// Re-read copy of appropriate data for each pass.
			switch(fileSelect)
			{
				case 0:
					printf("============== RANDOM.TXT ==============\n");
					size = read_int_file ("RANDOM.TXT", &pa);
					break;
				case 1:
					printf("============ ASCENDING.TXT ============\n");
					size = read_int_file ("ASCENDING.TXT", &pa);
					break;
				case 2:
					printf("============ DESCENDING.TXT ============\n");
					size = read_int_file ("DESCENDING.TXT", &pa);
					break;
			}

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

			// Select appropriate sort method based on the current iteration number.
			switch(sortmode)
			{
				
				case 0:
					printf ("Bubble Sort\n");
					rslt = bubblesort (pa, 0, size-1);
					break;
				case 1:
					printf ("Insertion Sort\n");
					rslt = insertionsort (pa, 0, size-1);
					break;
				case 2:
					printf ("Heap Sort\n");
					rslt = heapsort (pa, size);
					break;
				case 3:
					printf ("Merge Sort\n");
					rslt = mergesort (pa, 0, size-1);
					break;
				case 4:
					printf ("Quicksort\n");
					rslt = quicksort (pa, 0, size-1);
					break;
				case 5:
					printf ("Selection Sort (Iterative)\n");
					rslt = selsortI (pa, 0, size-1);
					break;
				case 6:
					printf ("Selection Sort (Recursive)\n"); 
					rslt = selsortR (pa, 0, size-1);
					break;
				case 7:
					printf ("Shell Sort\n");
					rslt = ShellSort (pa, 0, size-1);
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
			dataTable[sortmode][2*fileSelect] = end-start;
			dataTable[sortmode][2*fileSelect + 1] = swaps;
			
		}
		free(pa);
	}

	// Code to output to table to text file.
	char *filename = "LAB4_PART2.TXT";
	FILE *fp = fopen(filename, "w");
	if(fp==NULL)
	{
		printf("Could not open output file.");
		exit(1);
	}

	//Print out the entire data output table.
	for(int i = 0; i < 11; i++)
	{
		for(int j = 0; j < 7; j++)
		{
			if(i < 3)
			{
				fprintf(fp, "%-20s",textTable[i][j]);
				printf("%-20s", textTable[i][j]);
			}
			else
			{
				if(j < 1)
				{
					fprintf(fp, "%-20s",textTable[i][j]);
					printf("%-20s", textTable[i][j]);
				}
				else
				{
					fprintf(fp,"%-20d", dataTable[i-3][j-1]);
					printf("%-20d", dataTable[i-3][j-1]);
				}
			}
		}
		fprintf(fp, "\n");
		printf("\n");
	}
	printf("\n");
	fclose(fp);
}//main()