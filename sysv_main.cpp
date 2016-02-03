#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h> 


int main() {
	const int SIZE = 1048576;
	char * ptr;
	key_t key = ftok("/tmp/mem.temp", 0);
	
	int shmid = shmget( key, SIZE, IPC_CREAT | IPC_EXCL | 0660 );
	ptr = (char *) shmat(shmid, 0, 0); 
	for (int i = 0; i < SIZE; i++) {
		*ptr++ = 42;
	}
	return 0;
}
