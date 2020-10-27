TOP_DIR := $(shell pwd)
SERVER_APP = server.out

CC = gcc
CFLAGS = -g 
LIBS = -lzmq -lczmq 
LIBS_DIR = -L/usr/lib/x86_64-linux-gnu
HEADERFILE_DIR = -I/usr/include
SERVER_SRC = demo.c OrbStreamNtp.c md5.c

#all:  $(OBJS)
all:
	$(CC) -g -o $(SERVER_APP) $(SERVER_SRC) $(HEADERFILE_DIR) $(LIBS) $(LIBS_DIR) 

clean:
	rm -f *.o *.out 

