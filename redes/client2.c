#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char word[50];
	char output[50];

	port = argv[1];
	server = gethostbyname(argv[0]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = ;
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1){
		perror("vixe\n");
		exit(1);
	}
	printf("Digite a continha: tipo / 2 3 = 2 dividido por 3\n");
	scanf("%s", word);
	write(sockfd, word, 50);
	read(sockfd, output, 50);
	printf("Voce recebeu:\n%s\n", output);
	close(sockfd);
	exit(0);
	return 0;
}