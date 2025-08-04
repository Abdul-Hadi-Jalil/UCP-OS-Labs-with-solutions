#define _GNU_SOURCE
#include<stdio.h>
#include<sched.h>
#include<sys/sysinfo.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    int size = argc;
    int arr[argc];

    for(int i = 1; i < size; i++)
    {
        arr[i-1] = atoi(argv[i]);
    }

    for(int i = 0; i < 3; i++)
    {
        if(fork() == 0)
        {
            cpu_set_t mask;

            CPU_ZERO(&mask);
            CPU_SET(i, & mask);

            sched_setaffinity(i, sizeof(cpu_set_t), &mask);

            if(i == 0)
            {
                int sum = 0;
                for(int i = 0; i < size; i++)
                {
                    sum += arr[i];
                }
                printf("The avg is: %d\n", sum/size);
            }
            if(i == 1)
            {
                int min = arr[0];
                int max = arr[0];

                for(int i = 0; i< size; i++)
                {
                    if(arr[i] < min)
                    {
                        min = arr[i];
                    }
                    if(arr[i] > max)
                    {
                        max = arr[i];
                    }
                }

                printf("The minimum value is: %d\n", min);
                printf("The maximum value is: %d\n", max);
                   
            }
            if(i == 2)
            {
                for(int i = 0; i < size; i++)
                {
                    for(int j = i+1; j < size; j++)
                    {
                        if(arr[i] > arr[j])
                        {
                            int tem = arr[j];
                            arr[j] = arr[i];
                            arr[i] = tem;
                        }
                    }   
                }

                printf("The sorted array is: ");
                for(int i = 0; i < size; i++)
                {
                    printf(" %d ", arr[i]);
                }
                printf("\n");
            }
            return 0;
        }
    }
    return 0;
}