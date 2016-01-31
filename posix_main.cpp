#include <mqueue.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MSG_SIZE 128

int main() {
	struct mq_attr attr;
	mqd_t mqdes;
	char buf[MSG_SIZE];   
	unsigned int prio;
	attr.mq_maxmsg = 2;
	attr.mq_msgsize = MSG_SIZE;
	attr.mq_flags = 0;
	int mgsize;
	
	mqdes = mq_open ("/test.mq", O_RDWR | O_CREAT, 0664, &attr);
	mq_getattr (mqdes, &attr);
	
	if (attr.mq_curmsgs != 0) {
		mgsize = mq_receive (mqdes, &buf[0], MSG_SIZE, &prio);
		int f = open("/home/box/message.txt", O_RDWR | O_CREAT, 0666);
		write(f, buf, mgsize);
		close(f);
	}
	
	mq_close (mqdes);
	return 0;
}