// MAKEWRDS.C [200818]
// Program to create files required for ELEC278 Lab 5 part 1.
// WORDLIST- file containing many lines of alphanumeric strings

// HISTORY
// 200818 - DFA - First release


/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2021.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

Author:  David F. Athersych, P.Eng.
All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */

#define	FL_WRDLST		"WORDLIST.TXT"
#define FL_DELETES		"DELETES.TXT"
#define FL_LOOKUPS		"LOOKUPS.TXT"
#define	COUNT_IDENT		60
#define	COUNT_DELS		6
#define COUNT_LUKUPS	6

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>

// CONFIGURATION. If you want this program to create the same table each time,
// set the following global variable to 1. If you want a randow set each time,
// set the variable to 0.

const int	FixedTable = 1;


char *random_string (int count)
// Routine generates random string up to 31 characters long.
{
	static char			buff [32];
	static char	chars[60] =
					"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int					i;

	// protect against mistakes
	if (count < 0 || count > 30)	return NULL;

	for (i=0; i<count; i++)	{
		int	ndx = rand() % 52;
		buff [i] = chars [ndx];
		}
	// Finished generating characters - add string terminator
	buff [i] = '\0';
	return buff;
} //random_string()


int main (int argc, char argv[])
{
	int				i;
	char			*pwd;
	unsigned char	dup = 0;
	unsigned int	seed = 27901;
	unsigned int	id;
	unsigned int	lower = 100000, upper = 19999999;
	FILE			*fp_wrds;
	FILE			*fp_luks;

	// Seed random number generator. Note that seed can be current time so
	// sequence of numbers will be different each run.
	// printf ("FYI: Maximum value from rand() is: %d\n", RAND_MAX);
	if (FixedTable)	srand (seed);		// same seed to start random sequence
	else			srand (time(0));	// changes each run of program

	// Create files. Generate all 3 at same time so we can ensure overlaps for
	// delete and lookup
	fp_wrds = fopen (FL_WRDLST, "w");
	if (fp_wrds == NULL)	{
		fprintf (stderr, "ERROR: Could not open %s\n", FL_WRDLST);
		return -1;
		}
	fp_luks = fopen (FL_LOOKUPS, "w");
	if (fp_luks == NULL)	{
		fprintf (stderr, "ERROR: Could not open %s\n", FL_LOOKUPS);
		fclose (fp_wrds);
		return -1;
		}

	for (i=0; i<COUNT_IDENT; i++)	{
		// Create random 8 character string
		pwd = random_string (8);
		fprintf (fp_wrds, "%s\n", pwd);
		if (i%5 == 0)
				fprintf (fp_luks, "%s\n", pwd);
		}//endfor
	fclose (fp_luks);
	fclose (fp_wrds);
	return 0;
} //main()
