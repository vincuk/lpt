#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>

pthread_mutex_t lock;
pthread_spinlock_t spinlock;
pthread_rwlock_t rlock;
pthread_rwlock_t wlock;

void *sub_a(void *) {
	pthread_mutex_lock(&lock);
    while(true);
}
void *sub_b(void *) {
	pthread_spin_lock(&spinlock);
    while(true);
}
void *sub_c(void *) {
	pthread_rwlock_rdlock(&rlock);
    while(true);
}
void *sub_d(void *) {
	pthread_rwlock_wrlock(&wlock);
    while(true);
}

int main(int argc, const char *argv[]) {
	int pid;
	pid = getpid();
	FILE *out;
	out = fopen ("main.pid", "w");
	fprintf (out, "%d\n", pid);
	fclose(out);
	
	pthread_t threads[4];
	pthread_mutex_init(&lock);  
	pthread_spin_init(&spinlock);
	pthread_rwlock_init(&rlock);
	pthread_rwlock_init(&wlock)
    pthread_create(&threads[0], NULL, sub_a, NULL);
    pthread_create(&threads[1], NULL, sub_b, NULL);
    pthread_create(&threads[2], NULL, sub_c, NULL);
    pthread_create(&threads[3], NULL, sub_d, NULL);
       
    return 0;
}