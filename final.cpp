#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <strings.h>
#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <pthread.h>

char *dirval = (char *)"/";

void not_found(int client) {
	char buf[1024];
	sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
	write(client, buf, strlen(buf));
	sprintf(buf, "Content-Type: text/html\r\n");
	write(client, buf, strlen(buf));
	sprintf(buf, "\r\n");
	write(client, buf, strlen(buf));
	sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
	write(client, buf, strlen(buf));
	sprintf(buf, "<BODY><P>Page not found.\r\n");
	write(client, buf, strlen(buf));
	sprintf(buf, "</BODY></HTML>\r\n");
	write(client, buf, strlen(buf));
}

void send_file(int client, FILE *f) {
	char buf[1024];

	write(client, "HTTP/1.0 200 OK\r\n", 16);
	write(client, "Content-Type: text/html\r\n\n", 25);
	write(client, "\r\n", 2);
	fgets(buf, sizeof(buf), f);
	while (!feof(f)) {
		write(client, buf, strlen(buf));
		fgets(buf, sizeof(buf), f);
	}
}

void accept_request(void *arg) {
	int* client = (int *)arg;
	int bufsize = 1024;

	char *buffer = (char *)malloc(bufsize);
	char method[512];
	char URL[1024];
	size_t i, j;

	recv(*client, buffer, bufsize, 0);
	
// 	printf("%s\n", buffer);
	
	i = 0;
	j = 0;
	int url_s = strlen(dirval);

	if (dirval[0] != '/') {
		URL[0] = '/';
		i++;
		url_s++;
	}
	while (j < url_s) {
		URL[i] = dirval[j];
		i++;
		j++;
	}
	i = 0;
	j = 0;
	while (!isspace(buffer[j]) && (i < sizeof(method) - 1)) {
		method[i] = buffer[j];
		i++;
		j++;
	}
	method[i] = '\0';
	i = url_s; 
	j++;
	int k = 0;
	while (!isspace(buffer[j]) && (i < sizeof(URL) - 1)) {
		URL[i] = buffer[j];
		i++;
		j++;
		k++;
	}
	if (k == 1) {
		char * index = (char *)"index.html";
		for (j = 0; j < 10; j++) {
			URL[i] = index[j];
			i++;
		}
	}
	URL[i] = '\0';
// 	printf("Requested URL: %s\n", URL);

	if (strcasecmp(method, "GET") == 0) {
		FILE *f = NULL;
		f = fopen(URL, "r");
		if (f != NULL)
			send_file(*client, f);
		else
			not_found(*client);
	}
	close(*client);
}

int main(int argc, char **argv) {
	int c;
	int portval = 15000;
	char *hostval = (char *)"localhost";
	while (1) {
		static struct option long_options[] =
		{
			{"host", required_argument, 0, 'h'},
			{"port", required_argument, 0, 'p'},
			{"dir", required_argument, 0, 'd'},
        };
        int option_index = 0;
		c = getopt_long (argc, argv, "h:p:d:", long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
			{
			case 'h':
				hostval = optarg;
				break;
			case 'p':
				portval = atoi(optarg);
				break;
			case 'd':
				dirval = optarg;
				break;
			default:
				abort ();
			}
	}
	
// 	printf ("host = %s, port = %d, dir = %s\n", hostval, portval, dirval);
	
	pid_t curPID = fork();
 	if (curPID != 0) {
 		exit(0);
 	}

	int create_socket, new_socket;
	socklen_t addrlen;
	struct sockaddr_in address;
	pthread_t newthread;

	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0) {
// 		printf("The socket was created\n");
	}
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(hostval);
	address.sin_port = htons(portval);
	
	if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0) {
// 		printf("Binding Socket\n");
	}
	
	
	while (1) {
		if (listen(create_socket, 10) < 0) {
			perror("server: listen");
			exit(1);
		}
	
		if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {
			perror("server: accept");
			exit(1);
		}
	
		if (new_socket > 0) {
// 			printf("The Client is connected...\n");
		}

		if (pthread_create(&newthread, NULL, (void *(*)(void *))accept_request, (void*)&new_socket) != 0) {
			perror("pthread_create");
		}
	}
	close(create_socket);
	return 0;
}