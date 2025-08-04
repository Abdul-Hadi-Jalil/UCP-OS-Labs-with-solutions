#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  cpu_set_t mask;

  // Initialize the CPU set to all zeros
  CPU_ZERO(&mask);

  // Set the bit that represents core 0
  CPU_SET(0, &mask);

  // Print the CPU set
      if (CPU_ISSET(1, &mask)) {
          printf("CPU core %d is in the set.\n", 1);
      }

  return EXIT_SUCCESS;
}
