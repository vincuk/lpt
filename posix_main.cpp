#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MSG_SIZE       512

int main() {
	struct sigevent sigevent;  
	mqd_t mqdes;
	char buf[MSG_SIZE];   
	unsigned int prio;    
	
	FILE *outfile;
	
	mqdes = mq_open ("/test.mq", O_RDWR | O_CREAT, 0664, 0);
	mq_receive (mqdes, &buf[0], MSG_SIZE, &prio);
	
	std::cout << msg.mtext << std::endl;
	outfile = fopen("message.txt", "w");
	fprintf(outfile, "%s", buf);
	fclose(outfile);
	mq_close (mqdes);
	return 0;
}


