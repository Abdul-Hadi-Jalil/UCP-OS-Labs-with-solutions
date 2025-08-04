#include "stdio.h"

int main()
{
    float length = 0, width = 0;
    float area = 0;

    printf("Enter the length of a rectangle: ");
    scanf("%f", &length);

    printf("Enter the width of a rectangle: ");
    scanf("%f", &width);

    area = length * width;

    printf("The area of the rectangle is %f", area);

    return 0;
}