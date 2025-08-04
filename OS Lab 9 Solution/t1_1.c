#include<stdio.h>
#include<pthread.h>

#define BUFFER_SIZE 10

typedef struct {
 int data;
} item;

item buffer[BUFFER_SIZE];
int in = 0; // Location of next input to buffer
int out = 0; // Location of next removal from buffer
int counter = 0; // Number of buffers currently full

long flag = 0;
long expected = 0;
long new = 1;

long compare_and_set(long *flag, long expected, long new)
{
 asm(
    "compare_and_set:;"
    "movq %rsi, %rax;"
    "lock cmpxchg %rdx, (%rdi);"
    "retq;"
 );
}

void* producer (void* ptr)
{
 item nextProduced;
 for(unsigned int i=0;i<2000000;i++)
 {
     while(compare_and_set(&flag,expected,new)!=0);
     if(counter == BUFFER_SIZE)
         continue;
     nextProduced.data = i; // replace this line with actual production logic
     buffer[in] = nextProduced;
     in = (in + 1) % BUFFER_SIZE;
     counter++;
     flag = 0;
 }
 pthread_exit(0);
}

void* consumer (void* ptr)
{
 item nextConsumed;
 for(unsigned int i=0;i<2000000;i++)
 {
     while(compare_and_set(&flag,expected,new)!=0);
     if(counter == 0)
         continue;
     nextConsumed = buffer[out];
     out = (out + 1) % BUFFER_SIZE;
     counter--;
     printf("Consumed: %d\n", nextConsumed.data); // replace this line with actual consumption logic
     flag = 0;
 }
 pthread_exit(0);
}

int main()
{
 pthread_t prod, cons;
 pthread_create(&prod, NULL, &producer, NULL);
 pthread_create(&cons, NULL, &consumer, NULL);

 pthread_join(prod, NULL);
 pthread_join(cons, NULL);

 return 0;
}
