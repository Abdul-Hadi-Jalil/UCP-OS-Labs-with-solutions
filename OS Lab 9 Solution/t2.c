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

void wait(int* s) {
   while(1) {
       int temp = *s;
       if(temp > 0) {
           if(compare_and_set(s, temp, temp - 1) != 0) {
               continue;
           }
           return;
       }
   }
}

void signal(int* s) {
   while(1) {
       int temp = *s;
       if(compare_and_set(s, temp, temp + 1) != 0) {
           continue;
       }
       return;
   }
}
