TOP_DIR := $(shell pwd)
CLIENT_APP = client.out
SERVER_APP = server.out

CC = gcc
CFLAGS = -g 
LIBS = -lzmq -lczmq 
LIBS_DIR = -L/usr/lib/x86_64-linux-gnu
HEADERFILE_DIR = -I/usr/include
CLIENT_SRC = client.c md5.c
SERVER_SRC = demo.c OrbStreamNtp.c md5.c

#all:  $(OBJS)
all:
	$(CC) -g -o $(CLIENT_APP) $(CLIENT_SRC) $(HEADERFILE_DIR) $(LIBS) $(LIBS_DIR) 
	$(CC) -g -o $(SERVER_APP) $(SERVER_SRC) $(HEADERFILE_DIR) $(LIBS) $(LIBS_DIR) 

clean:
	rm -f *.o *.out 

