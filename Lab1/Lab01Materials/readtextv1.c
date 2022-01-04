#include <stdio.h>
#include <stdlib.h>

#define	EXIT_OK		0
#define	EXIT_ERROR	-1
#define MAX_STRING_LENGTH 30


void main (void)
{
	FILE	*fp;
	char	buffer [256];	// should be big enough
	char	*pbuffer;		// use to point to buffer (hold address of buffer)
	int		count;			// use to count lines

	pbuffer = buffer;		// initialize pointer to buffer
	count = 0;				// initialize counter

	// Asks for user input to get the file name.
	char *str = (char*) malloc(100);
	printf("Type da file name bro: ");
    scanf("%s",str);

	// open file containing text
	fp = fopen(str, "r");
	// confirm that no errors occurred
	if (fp == NULL)	{
		// and if an error did occur, tell users and quit
		fprintf (stderr, "ERROR: Could not find file\n");
		exit (EXIT_ERROR);
		}	

	// At this point we have file open. We want to read line and write it out;
	// and keep doing this until we get to the end of the file. In other words,

	while (fgets (pbuffer, 255, fp) != NULL)	{
		// got another line
		count++;
		printf ("%3d: %s", count, pbuffer);
		}

	// fgetline() returned EOF (end-of-file) meaning that we came to end.
	// Close file and exit
	fclose (fp);
	printf ("==End of text file==\n");
	exit (EXIT_OK);
}//main()
