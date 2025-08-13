#include <stdio.h>

void checkPrimeNumber(int num);

int main()
{
    int num = 0;

    printf("Enter a number: ");
    scanf("%d", &num);

    checkPrimeNumber(num);

    return 0;
}

void checkPrimeNumber(int num)
{
    int isPrime = 1;
    for (int i = 3; i < num; i++)
    {
        if (num % i == 0)
        {
            isPrime = 0;
            printf("\n Not Prime\n");
        }
    }
    if (isPrime)
    {
        printf("\nPrime\n");
    }
}