#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	int result;
	int msqid;
	
	struct message {
		long mtype;
		char mtext[80];
	} msg;
	
	key_t key = ftok("/tmp/msg.temp", 0);
	msqid = msgget(key, 0666 | IPC_CREAT);

	long msgtyp = 1;
	result = msgrcv(msqid, (void *) &msg, sizeof(msg.mtext), msgtyp, 0);
		
	int f = open("/home/box/message.txt", O_RDWR | O_CREAT, 0666);
	write(f, msg.mtext, result);
	close(f);
	
	return 0;
}
