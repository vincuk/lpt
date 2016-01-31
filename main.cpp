#include <sys/msg.h>
#include <stdio.h>

int main() {
	FILE *outfile;
	int result;
	int msqid;
	
	struct message {
		long mtype;
		char mtext[80];
	} msg;
	
	key_t key = ftok("/tmp/msg.temp", 0);

	long msgtyp = 1;
	result = msgrcv(msqid, (void *) &msg, sizeof(msg.mtext),
		msgtyp, MSG_NOERROR | IPC_NOWAIT);
		
	outfile = fopen("/home/box/message.txt", "w");
	fprintf(outfile, "%s\n", msg.mtext);
	fclose(outfile);
	return 0;
}
