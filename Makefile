TOP_DIR := $(shell pwd)

CC := g++
LD := ld
LIBS := -lzmq -lczmq 
LIBS_DIR := -L/usr/lib/x86_64-linux-gnu
INCLUDE_DIR := -I/usr/include
INCLUDE_DIR += -I./include
CFLAGS := -g -shared -fPIC
CFLAGS += $(INCLUDE_DIR) 
LDFLAGS += $(LIBS_DIR) $(LIBS)

SOURCE := $(wildcard *.c) 
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
TARGET := libOrbStreamNtp.so 
#TARGET := server.out
$(TARGET):$(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)
#	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SOURCE)

%.o:%.c 
	@echo Compling $<...
	$(CC) -g -I/usr/include -I./include -L/usr/lib/x86_64-linux-gnu -lzmq -lczmq -MM $< -o $@

.PHONY:clean

clean:
	rm -f *.o *.out *.so 

