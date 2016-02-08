#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>

#define NUM_THREADS 4

void foo(void) {
    while(true);
}

int main(int argc, const char *argv[]) {
	int pid;
	pid = getpid();
	FILE *out;
	out = fopen ("main.pid", "w");
	fprintf (out, "%d\n", pid);
	fclose(out);
	
	pthread_t  threads[NUM_THREADS];
	pthread_mutex_t lock;
	int tries;
	ret = pthread_mutexattr_init(&mattr);
    
    for (i=0;i<NUM_THREADS;i++)
	    pthread_create(&threads[i], NULL, (void *(*)(void *)) foo, NULL);

	pthread_create(&threads, NULL, search, (void *)pid);
    
   
    pthread_join(thread, NULL);
    return 0;
}