// L4_QUICKSORT2.C - Lab 04 - Carl, Lam
// Implements simple quicksort algorithm in conjunction with insertionsort.

// Modified insertionsort code to work with the modified quicksort.
void insertionsort (int *a, int min, int max)
// Work through array of numbers, placing each one in the correct place. Note that insertion sort differs from 
// bubblesort in that with insertion sort, one value is moved to its relative place. In bubble sort, the largest 
// value is found as the checking keeps choosing the larger of two values to keep moving.
{
	int		i, j;
	int		rslt = -1;

	// Check for errors
	if (a == NULL || (min > max))
	{
		error("insertionsort() called with invalid parameters");
	} 
	else
	{
		// Outer for loop works through values from min to max. Effectively, we start by making data in position relative
		// 0 a sorted array containing one element, then adding the rest of the array, one by one, to the sorted part.
		for (i = min; i <=max; i++)
		{
			// Now, i indicates which new element in the array is going to be inserted into its correct position. At the
			// end of each loop, one more value is moved, and all of the bottom is ordered.
			for (j = i; j > min && (a[j - 1] > a[j]); j--)
			{
				swap(a, j, j - 1);
			}
		}
	}
}//insertionsort()

int partition (int  *a,  int left, int right)
// Using locations a[left..right], partition fragment by picking a[left] as separator value, then working through
// bottom and top halves of the array, arranging - by swapping values if necessary - that all values smaller than
// the separator value are in the bottom part and all values larger are in the top part. Used by both the original
// and modified quicksort.
{
	int	ll, rr, pivotval;
	ll = left+1;
	rr = right;
	// choose pivot to be leftmost location
	pivotval = a[left];
    while (ll < rr)	
	{
		// if one on left less than pivot, leave it alone
		if(a[ll] <= pivotval)	{ ll++; continue;}
		// if one on right greater than pivot, leave it
        if(a[rr] > pivotval)	{ rr--; continue;}
		// both left and right on wrong side - swap them
		swap(a, ll, rr);
    }
	// we stop when rr and ll collide. Place pivot value such that everything
	// to left is less and everything to right is same or greater.
	if (a[ll] < pivotval)	
	{
		swap(a, ll, left);
	}
	else
	{
		swap(a, --ll, left);
	}
	return ll;
}//partition()

// Original quicksort functions.
int quicksort (int *a,  int left, int right)
{
	if (left < right)
	{
		int  pivotndx = partition (a, left, right);
		quicksort (a, left, pivotndx-1);
		quicksort (a, pivotndx+1, right);
	}
	return swaps;
}//quicksort()

int modified_quicksort(int *a, int left, int right)
{
	if(left<right)
	{
		if(right-left > 32)
		{
			int  pivotndx = partition (a, left, right);
			quicksort (a, left, pivotndx-1);
			quicksort (a, pivotndx+1, right);
		}
		else
		{
			insertionsort(a, left, right);
		}
	}
	return swaps;	
}//modified_quicksort()