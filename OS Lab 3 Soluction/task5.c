#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a = 0, b = 0, result = 0;

    if (argc >= 3)
    {
        a = atoi(argv[1]);
        b = atoi(argv[2]);

        result = a * b;

        printf("Multiply result is %d", result);
    }
    return 0;
}