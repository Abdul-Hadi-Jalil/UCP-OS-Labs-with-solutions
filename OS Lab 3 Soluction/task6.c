#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        int size = argc - 1;
        int *array = (int *)malloc(size * sizeof(int));

        // filling the array
        for (int i = 0; i < size; i++)
        {
            array[i] = atoi(argv[i + 1]);
        }

        // finding the minimum number
        int min = array[0];
        int second_min = array[0];

        for (int i = 0; i < size; i++)
        {
            if (min > array[i])
            {
                min = array[i];
            }
        }

        // finding second minimum
        for (int i = 0; i < size; i++)
        {
            if (second_min > array[i] && array[i] != min)
            {
                second_min = array[i];
            }
        }
        printf("Second minimum number is %d\n", second_min);
    }

    return 0;
}