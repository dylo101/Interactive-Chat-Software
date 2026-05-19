#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/types.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

#define STRLEN 120

struct sockaddr_in server_addr, client_addr;
uint16_t server_port;


void usage() 
{
	printf("Command format: ./server port_number\n\n");
	printf("\tport_number \tshould be a well-known port\n\n");
	exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])
{
	int sockfd, nsockfd;
	time_t ticks;
	socklen_t client_len;
	char t[256];


	if(argc == 1)
	{
		printf("Server port number missing!\n");
		usage();
	}

	server_port = atoi(argv[1]);
	ticks = time(NULL);
	printf("\nServer starts running at %s\n",(char *) ctime(&ticks));

	char buffer[STRLEN + 1];
	// create a socket on the server ent
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		fprintf(stderr,"\nError openning socket!\n");
		exit(EXIT_FAILURE);
	}

	bzero((char *) &server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);	// big-endian conversion
	server_addr.sin_port = htons(server_port);	

	if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
	{
		fprintf(stderr, "\nError binding address to socket\n");
		exit(EXIT_FAILURE);
	}

	// listen to client connection
	if(listen(sockfd, 1) < 0)
	{
		fprintf(stderr,"\nError creating a passive connection\n");
		exit(EXIT_FAILURE);
	}

	while (1)
    	{
        	client_len = sizeof(client_addr);
        	if ((nsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len)) < 0)
        	{
            		fprintf(stderr, "\nError accepting client\n");
            		exit(EXIT_FAILURE);
        	}

        	printf("Client connected.\n");

        	while (1)
        	{
            		int n = read(nsockfd, buffer, STRLEN);
            		if (n > 0)
            		{	
				ticks = time(NULL);
    				char *timestamp = ctime(&ticks);
    				timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline
                		printf("Client[%s]:$ %s\n", timestamp, buffer);
                		if (strcmp(buffer, "quit") == 0)
                    		break;
            		}
			
			ticks = time(NULL);
    			char *timestamp = ctime(&ticks);
    			timestamp[strlen(timestamp) - 1] = '\0'; // Remove newline
            		printf("Server[%s]:$ ", timestamp);
            		fgets(buffer, STRLEN, stdin);
            		buffer[strcspn(buffer, "\n")] = 0;

            		write(nsockfd, buffer, strlen(buffer) + 1);
            		if (strcmp(buffer, "quit") == 0)
            		{
                		break;
                	}
        	}

        	printf("Client disconnected.\n");
        	close(nsockfd);
    	}

    	close(sockfd);
    	return 0;
} // end of main


