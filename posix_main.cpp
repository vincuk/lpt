#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MSG_SIZE 128

int main() {
	struct mq_attr attr;
	mqd_t mqdes;
	char buf[MSG_SIZE];   
	unsigned int prio;
	attr.mq_maxmsg = 300;
	attr.mq_msgsize = MSG_SIZE;
	attr.mq_flags = 0;
	
	mqdes = mq_open ("/test.mq", O_RDWR | O_CREAT, 0664, &attr);
	
	if (attr.mq_curmsgs != 0) {
		mq_receive (mqdes, &buf[0], MSG_SIZE, &prio);
		int f = open("/home/box/message.txt", O_RDWR | O_CREAT, 0666);
		write(f, buf, MSG_SIZE);
		close(f);
	}
	
	mq_close (mqdes);
	return 0;
}