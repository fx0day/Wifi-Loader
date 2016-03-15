#include <stdio.h>

#include <windows.h>
#include <winsock.h>

#ifndef WINVER
	#define WINVER 0x0500
#endif

//#define MAKE_IP(a, b, c, d) (((a) << 24) + ((b) << 16) + ((c) << 8) + (d))

//#define IP MAKE_IP(192, 168, 0, 4)
#define PAYLOAD "README.md"

int main(int argc, char *argv[]) {
if (argc ==4)
    {
	int port=atoi(argv[2]);
	FILE *f;
	char *buffer;
	int length;
	
	int server;
	struct sockaddr_in serverAddress;

printf("Sending on IP : %s\n", argv[1]);
printf("Sending on Port : %s\n", argv[2]);
printf("Sending File : %s\n", argv[3]);
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddress.sin_port = htons(port);
	
	connect(server, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	
	f = fopen(argv[3], "rb");
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	buffer = malloc(length);
	rewind(f);
	fread(buffer, length, 1, f);
	fclose(f);
	
	sendto(server, buffer, length, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
	
	printf("Sent %d bytes\n", length);
	
	free(buffer);
	
	closesocket(server);
	
	WSACleanup();
	
	return 0;
}
else printf ("Usage: WIFI-Loader IP PORT FILE\n");
printf ("Ex: WIFI-Loader 192.168.0.14 9023 payload.bin");

return EXIT_SUCCESS;

}
