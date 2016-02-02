#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
	key_t key;
	int cntr;
    union semun semopts;
    int   semid;
    int members = 16;
	
	key = ftok("/tmp/sem.temp", 0);
	semid = semget(key, members, IPC_CREAT|IPC_EXCL|0666);

	for(cntr=0; cntr<members; cntr++) {
		semopts.val = cntr;
		semctl(semid, cntr, SETVAL, semopts);
	}
	return 0;
}
