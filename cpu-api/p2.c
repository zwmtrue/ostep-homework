#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
  printf("Hello world (pid:%d)\n", (int) getpid());
  int rc = fork();
  if (rc < 0){
	fprintf(stderr, "fork failed\n");
       exit(1);
  } else if (rc == 0) { // child (new process)      
	 printf("hello, I am child (pid:%d)\n", (int) getpid());
  } else { // parent goes down this path (main)
         int rc_wait = wait(NULL);
	  printf("hello, I am parent of %d (pid:%d)\n",
              rc, (int) getpid());
  }
   return 0;
}

