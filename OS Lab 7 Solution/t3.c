#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <sys/sysinfo.h>

double calculate_pi(long int start, long int end, double dx) 
{
  double pi = 0.0;
  for(long int i = start; i < end; i++) {
      double x = (i + 0.5) * dx;
      pi += 4.0 / (1.0 + x * x);
  }
  pi *= dx;
  return pi;
}

int main() 
{
  long int nsteps = 10000000;
  double dx = 1.0 / nsteps;
  int num_cpus = get_nprocs();

  pid_t pid;
  for(int i = 0; i < num_cpus; i++) 
  {
      pid = fork();
      if(pid == 0) 
      {
          long int start = i * (nsteps / num_cpus);
          long int end = (i + 1) * (nsteps / num_cpus);
          double pi = calculate_pi(start, end, dx);
          printf("%lf\n", pi);
          return 0;
      }
  }

  for(int i = 0; i < num_cpus; i++) 
  {
      wait(NULL);
  }

  return 0;
}
