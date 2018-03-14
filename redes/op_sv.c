#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	int result, flag;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	char message[50], operator[50], first[50], second[50];
	char *token;
	char op;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = atoi(argv[1]);
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
	listen(server_sockfd, 1);
	while (1){
		flag = 0;
		printf("waiting 4 u\n");
		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
		read(client_sockfd, message, 50);
		token = strtok(message, ":");
		op = token[0];
		token = strtok(NULL, ":");
		strcpy(first, token);
		token = strtok(NULL, ":");
		strcpy(second, token);
		printf("%s %c %s\n", first, op, second);
		if(op == '+' || op == '-'){
			result = (op == '+') ? atoi(first) + atoi(second) : atoi(first) - atoi(second);
		}
		else if(op == '/' || op == '*'){
			result = (op == '*') ? atoi(first) * atoi(second) : atoi(first) / atoi(second);
		}
		else
			flag = 1;
		sprintf(message, "%d", result);
		if(!flag)
			write(client_sockfd, message, 50);
		else
			write(client_sockfd, "Operacao invalida", 50);
		close(client_sockfd);
	}
	return 0;
}
