#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include<stdlib.h>

typedef struct 
{
   FILE* filename;
   int num_threads;
   char* str;
} array;

int cancel = 0;

void* search(void* ptr)
{
   array one = *(array*) ptr;
   char buffer[50];
   int line_no = 0;
   
   if(cancel == 1)
   {
        pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        pthread_testcancel();
   }
   while(!cancel && fgets(buffer, sizeof(buffer), one.filename)) 
   {
        line_no++;
       if(strstr(buffer, one.str) != NULL) 
       {
           printf("Name found\n");
           printf("in line %d\n", line_no);
           cancel = 1;
           return NULL;
       }
   }

   printf("Name not Found\n");
   return NULL;
}

int main(int argc, char* argv[])
{
   array one;

   one.filename = fopen(argv[1],"r");
   one.num_threads = atoi(argv[2]);
   one.str = argv[3];

   pthread_t tid[one.num_threads];

    for(int i = 0; i < one.num_threads; i++)
    {
        pthread_create(&tid[i], NULL, &search, &one);
        pthread_cancel(tid[i]);
    }
   
    for(int i = 0; i < one.num_threads; i++)
    {
        pthread_join(tid[i], NULL);   
    }

   return 0;
}