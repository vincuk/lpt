#include <sys/msg.h>
#include <unistd.h>

int main() {
	int result;
	int msqid;
	long msgtyp = 1;
	
	struct message {
		long mtype;
		char mtext[80];
	} msg;
	
	key_t key = ftok("/tmp/msg.temp", 0);
	msqid = msgget(key, 0666 | IPC_CREAT);
	result = msgrcv(msqid, (void *) &msg, sizeof(msg.mtext), msgtyp, 0);

	int f = open("/home/box/message.txt", O_RDWR | O_CREAT, 0666);
	write(f, msg.mtext, sizeof(msg.mtext));
	close(f);
	
	return 0;
}


