#pragma once
#define UDP_TYPE_HEAD 1000
#define UDP_SERVER_IP 127.0.0.1
#define UDP_PORT 3300
#define UDP_RECVBUF 4096
#define UDP_ACCEPT_QUEUE_LEN 10

typedef struct UDP_QUEUE
{
	char* buf;
	int status;
}UDP_QUEUE;