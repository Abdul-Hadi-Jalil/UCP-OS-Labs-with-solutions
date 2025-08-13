#include <stdio.h>
#include <stdlib.h> // For malloc, free
#include <string.h> // For strdup (optional)

struct Employee
{
    int age;
    char *name; // Will be dynamically allocated
    char *id;   // Will be dynamically allocated
    float pay;
};

int main()
{
    struct Employee employee;
    char temp_buffer[256]; // Temporary buffer for safe input

    // Read name
    printf("Enter the name of employee: ");
    scanf("%255s", temp_buffer);                     // Read into temp buffer
    employee.name = malloc(strlen(temp_buffer) + 1); // Allocate exact space
    strcpy(employee.name, temp_buffer);              // Copy to dynamic memory

    // Read age
    printf("Enter the age of employee: ");
    scanf("%d", &employee.age); // & for int

    // Read ID
    printf("Enter the id of employee: ");
    scanf("%255s", temp_buffer);
    employee.id = malloc(strlen(temp_buffer) + 1);
    strcpy(employee.id, temp_buffer);

    // Read pay
    printf("Enter the pay of employee: ");
    scanf("%f", &employee.pay); // & for float

    // Display details
    printf("\nEmployee Details:\n");
    printf("Name: %s\n", employee.name);
    printf("Age: %d\n", employee.age);
    printf("ID: %s\n", employee.id);
    printf("Pay: %.2f\n", employee.pay);

    // Free allocated memory
    free(employee.name);
    free(employee.id);

    return 0;
}