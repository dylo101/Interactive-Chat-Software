# Interactive Chat Software
Linux environment chat softwareusing socket APIs.

# Socket APIs used in code:
1. socket (creates socket)
	-used in server_chat.c and client_chat.c
	-parameters: domain, type, protocol
2. bind (assigns address to socket)
	-used in server_chat.c
	-parameter: sockfd, addr, addrlen
3. listen (makes socket listen for connections)
	-used in server_chat.c
	-parameters: sockfd, backlog
4. accept (accepts client connections)
	-used in server_chat.c
	-parameters: sockfd, addr, addrlen
5. connect (connects to server)
	-used in client_chat.c
	-parameters: sockfd, addr, addrlen
6. read (receives messaegs)
	-used in server_chat.c and client_chat.c
	-sockfd, buf, count
7. write (sends messages)
	-used in server_chat.c and client_chat.c
	-parameters: sockfd, buf, count
8. close (closes socket)
	-used in server_chat.c and client_chat.c
	-parameters: sockfd
