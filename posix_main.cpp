#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	const int SIZE = 1048576;
	char *ptr;
	char *shm_base;
	
	int shm_fd = shm_open("/test.shm", O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	shm_base = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	
	ptr = shm_base;
	for (int i = 0; i < SIZE; i++) {
		*ptr++ = 13;
	}
	
	return 0;
}