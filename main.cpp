#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
	sem_t * mysem;
	mysem = sem_open("/test.sem", O_CREAT, 0666, 66);
	if (mysem != 0) {
        perror("Unable to initialize the semaphore");
        abort();
    }
	return 0;
}