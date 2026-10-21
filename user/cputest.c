#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NPROCS 4
#define NPRINTS 5

int
main(int argc, char *argv[])
{
  for (int i = 0; i < NPROCS; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("cputest: fork failed\n");
      exit(1);
    }
    if (pid == 0) {
      // process con
      for (int j = 0; j < NPRINTS; j++) {
        printf("child %d (pid %d): cpu %d\n", i, getpid(), getcpu());
        // làm việc tính toán một chút để scheduler có cơ hội chuyển CPU
        for (volatile int k = 0; k < 5000000; k++)
          ;
        // hoặc nhường CPU: pause(0) / sleep(1)
        pause(0);
      }
      exit(0);
    }
  }

  // process cha đợi tất cả con
  for (int i = 0; i < NPROCS; i++)
    wait(0);

  exit(0);
}
