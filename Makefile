TOP_DIR := $(shell pwd)
SERVER_APP = server.out

CC := g++
CFLAGS := -g -Wno-write-strings
LDFLAGS := -shared -fPIC  
LIBS := -lzmq -lczmq 
LIBS_DIR := -L/usr/lib/x86_64-linux-gnu
HEADERFILE_DIR := -I/usr/include
OBJ_SRC := OrbStreamNtp.c md5.c
OBJ_NAME := libOrbStreamNtp.so 
DEMO_SRC := demo.c
LIB_NAME := -lOrbStreamNtp
LIBS_DIR += -L.
all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ_SRC) $(HEADERFILE_DIR) $(LIBS) $(LIBS_DIR) -o $(OBJ_NAME) 
#	$(CC) $(CFLAGS) $(DEMO_SRC)  $(LIBS_DIR) $(LIB_NAME) -o $(SERVER_APP) 

clean:
	rm -f *.o *.out *.so 

