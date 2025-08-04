#include "stdio.h"

int main()
{
    float side1 = 0, side2 = 0, side3 = 0;
    printf("Enter the three sides of a triangle\n");

    printf("Enter side1: ");
    scanf("%f", &side1);

    printf("Enter side2: ");
    scanf("%f", &side2);

    printf("Enter side3: ");
    scanf("%f", &side3);

    if (side1 + side2 > side3 && side2 + side3 > side1 && side1 + side3 > side2)
    {
        printf("\nYes this is a triangle now lets see which type of triangle is it\n\n");
        if (side1 != side2 && side1 != side3 && side2 != side3)
        {
            printf("This is an scalene triangle\n");
        }
        else if (side1 == side2 && side2 == side3)
        {
            printf("It is an equilateral triangle\n");
        }
        else if (side1 == side2 | side2 == side3 | side1 == side3)
        {
            printf("It is an isocseles triangle\n");
        }
    }
    else
    {
        printf("No this is not a triangle\n");
    }

    return 0;
}