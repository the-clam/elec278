// stackproblem.c – Lab 02 – Carl, Lam

// Include required libraries.
#include <stdio.h>

// Defines used to set maximum size of data input, maximum and minimum indexes, and return messages.
#define STACK_SIZE  80
#define	EMPTY_INDEX	-1
#define	MAX_INDEX	(STACK_SIZE - 1)
#define	RTN_ERROR	0
#define	RTN_OK		1

// Use defined variables to initialize array for stack functions.
int  top = EMPTY_INDEX;
char stack [STACK_SIZE];

/* STACK FUNCTIONS (adapted from code examples) */
// Push character to top of stack.
int push(char n)
{
    if(top == MAX_INDEX) return RTN_ERROR;      // If stack full, return error.
    stack[++top] = n;                           // Add char n to the stack, increase top number.
    return RTN_OK;
}

// Pop character from top of stack.
int pop(char *val)
{
    if(top == EMPTY_INDEX) return RTN_ERROR;    // If stack empty, return error.
    *val = stack[top--];                        // Pass the val at the top of the stack by reference, decrease top number.
    return RTN_OK;
}

/* MAIN FUNCTION */
void main()
{   
    char c, val;                                        // Variables to hold chars.
    while(c != '\n')                                    // Input characters in single line until enter pressed. Characters over limit will be excluded.
    {
        scanf("%c", &c);                                // Scans individual characters.
        if(top == MAX_INDEX) break;                     // If array full, stop accepting inputs. 
        if(c != '\n') push(c);                          // If character is not a newline, push character into stack.
    }
    if(top == EMPTY_INDEX) printf("\n");                // Output max 80 characters reversed. If stack empty, empty line will be printed.
    else while(pop(&val) == 1) printf("%c", val);       // Pop and print top character in stack until stack empty.
}