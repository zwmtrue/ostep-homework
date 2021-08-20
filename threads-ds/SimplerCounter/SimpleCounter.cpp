#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct __counter_t
{
	int 			value;
	pthread_mutex_t lock;
	int threshold;
} counter_t;


void init(counter_t *c, int threhold){
	c->value = 0;
    c->threshold = threhold;
	pthread_mutex_init(&c->lock, NULL);
}

void * increment(void *arg){
    counter_t *c = (counter_t *) arg;  
    int t = c->threshold;
    int i = 0;

    while( i < t ){
        pthread_mutex_lock(&c->lock);
        c->value++;        
        pthread_mutex_unlock(&c->lock);
        i++;
    }
    return  (void * ) NULL;
}

int get(counter_t *c){
	pthread_mutex_lock(&c->lock);
	int rc = c->value;
	pthread_mutex_unlock(&c->lock);
	return  rc;
}


int main(int argc, char * argv[]) {
	int threshold ,threads ;
	
	if (sscanf (argv[1], "%i", &threads) != 1) {
		fprintf(stderr, "error - not an integer");
	}
	if (sscanf (argv[2], "%i", &threshold) != 1) {
		fprintf(stderr, "error - not an integer");
	}
	
	
	struct timeval start, end;
    int rc[threads] = {};

    pthread_t p[threads] = {};
    counter_t cnt ;
    init(&cnt, threshold);

	gettimeofday(&start, NULL);
    for (int i=0; i < threads; i++){
        rc[i] =  pthread_create(&p[i], NULL, increment, &cnt);
    }
    
    for (int i=0; i < threads; i++){      
        pthread_join(p[i], NULL);
    }
	gettimeofday(&end, NULL);	
	
    printf("Count : %d; Threads %d\n", cnt.value, threads);
	printf("seconds : %ld\nmicro seconds : %ld\n",
        end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);

  return 0;
}