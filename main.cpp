#include <sys/msg.h>
#include <stdio.h>
#include <iostream>

int main() {
	FILE *outfile;
	int result;
	int msqid;
	
	struct message {
		long mtype;
		char mtext[80];
	} msg;
	
	key_t key = ftok("/tmp/msg.temp", 0);
	msqid = msgget(key, 0666 | IPC_CREAT);
	
	long msgtyp = 2;
	result = msgrcv(msqid, (void *) &msg, sizeof(msg.mtext), msgtyp, 0);
	
	std::cout << msg.mtext << std::endl;
	outfile = fopen("message.txt", "w");
	fprintf(outfile, "%s\n", msg.mtext);
	fclose(outfile);
	return 0;
}