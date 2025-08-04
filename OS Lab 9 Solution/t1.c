#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFFER_SIZE 100

typedef struct
{
   int size;
   int* arr;
} array;

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;

int sum = 0;

long flag = 0;
long expected = 0;
long new = 1;

long compare_and_set(long *flag, long expected, long new)
{
   asm
   (
       "cmpxchg_label:;"
       "movq %rsi, %rax;"
       "lock cmpxchg %rdx, (%rdi);"
       "retq;"
   );
}

void* producer(void* ptr)
{
   array arr = *(array*) ptr;
   for(int i = 0; i < arr.size; i++)
   {
       while(compare_and_set(&flag, expected, new) != 0){}
       while(count == BUFFER_SIZE){}

       buffer[in] = arr.arr[i];
       in = (in+1) % BUFFER_SIZE;

       count++;
       flag = 0;
   }
   pthread_exit(NULL);
}

void* consumer(void* ptr)
{
   array arr = *(array*) ptr;
   for(int i = 0; i < arr.size; i++)
   {
       while(compare_and_set(&flag, expected, new) != 0){}
       while(count == 0){}

       sum += buffer[out];
       out = (out+1) % BUFFER_SIZE;

       count--;
       flag = 0;
   }
   pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
   array arr;
   arr.size = 1000000;
   arr.arr = malloc(arr.size * sizeof(int));

   for(int i = 0; i < arr.size; i++)
   {
       arr.arr[i] = i;
   }
   
   pthread_t prod, cons;

   pthread_create(&prod, NULL, &producer, &arr);
   pthread_create(&cons, NULL, &consumer, &arr);

   pthread_join(prod, NULL);
   pthread_join(cons, NULL);

   printf("Sum of all elements in the buffer is: %d\n", sum);

   free(arr.arr);

   return 0;
}
