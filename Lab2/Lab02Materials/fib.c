#include <stdio.h>

int fib(int n)
{
    if(n == 0) {
        return 1;
    }
    else if (n == 1) {
        return 2;
    }
    else {
        return fib(n-1)*fib(n-2);
    }
    
}


void main()
{
    int d;
    scanf ("%d", &d);
    printf("%d", fib(d));
}