#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h> 


int main() {
	char * ptr;
	key_t key = ftok("/tmp/mem.temp", 0);
	size_t segsize = 1024*1024*sizeof(char);
	
	int shmid = shmget( key, segsize, IPC_CREAT | IPC_EXCL | 0660 );
	ptr = shmat(shmid, 0, 0); 
	for (int i = 0; i < 1024*1024; i++) {
		*ptr++ = 42;
	}
	return 0;
}
