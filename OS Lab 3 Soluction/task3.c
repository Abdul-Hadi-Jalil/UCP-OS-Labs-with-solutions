#include "stdio.h"

int main()
{
    int array[20] = {0};
    int size = 0;

    printf("Enter the values of the array\n");
    printf("Press -99 to terminate the input\n\n");

    for (int i = 0; i < 20; i++)
    {
        printf("Enter value of index %d: ", i);
        scanf("%d", &array[i]);

        if (array[i] == -99)
        {
            array[i] = 0;
            size = i;
            break;
        }
    }

    printf("\nArray before sorting: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (array[i] > array[j])
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    printf("\nArray after sorting: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i]);
    }

    return 0;
}