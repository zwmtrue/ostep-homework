#include <stdio.h>

#include "common_threads.h"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int balance = 0;

void* worker(void* arg) {
	Pthread_mutex_lock(&m);
    balance++; // unprotected access 
	Pthread_mutex_unlock(&m);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
	Pthread_mutex_lock(&m);
    balance++; // unprotected access
	Pthread_mutex_unlock(&m);
    Pthread_join(p, NULL);
    return 0;
}
