#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>

pthread_cond_t cv; 
pthread_mutex_t mutex; 
pthread_barrier_t barrier;

void *sub_a(void *) {
	pthread_cond_wait(&cv, &mutex);
    while(true);
}
void *sub_b(void *) {
	pthread_barrier_wait(&barrier);
    while(true);
}

int main(int argc, const char *argv[]) {
	int pid;
	pid = getpid();
	FILE *out;
	out = fopen ("main.pid", "w");
	fprintf (out, "%d\n", pid);
	fclose(out);
	
	pthread_t threads[2];
	pthread_cond_init(&cv, NULL);
	pthread_barrier_init(&barrier, NULL, 2);
    pthread_create(&threads[0], NULL, sub_a, NULL);
    pthread_create(&threads[1], NULL, sub_b, NULL);   
    return 0;
}