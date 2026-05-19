CC = gcc
CFLAGS = -Wall -Wextra

all: client_chat server_chat

client_chat: client_chat.c
	$(CC) $(CFLAGS) client_chat.c -o client_chat

server_chat: server_chat.c
	$(CC) $(CFLAGS) server_chat.c -o server_chat

clean:
	rm -f client_chat server_chat

