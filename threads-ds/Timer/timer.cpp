#include <sys/time.h>
#include <stdio.h>
int main() {
	struct timeval current_time1, current_time2;
	
	gettimeofday(&current_time1, NULL);
	gettimeofday(&current_time2, NULL);
	
	printf("seconds : %ld\nmicro seconds : %ld\n",
    current_time1.tv_sec, current_time1.tv_usec);
	
	
	printf("seconds : %ld\nmicro seconds : %ld\n",
    current_time2.tv_sec, current_time2.tv_usec);

  return 0;
}