TOP_DIR := $(shell pwd)

CC := g++
LD := ld
LIBS := -lOrbStreamNtp 
LIBS_DIR := -L/usr/lib/x86_64-linux-gnu
LIBS_DIR += -L../lib
INCLUDE_DIR := -I/usr/include
INCLUDE_DIR += -I../include
CFLAGS := -Wno-write-strings  
CFLAGS += $(INCLUDE_DIR) 
LDFLAGS := $(LIBS_DIR) $(LIBS) 

SOURCE := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(wildcard *.c))
TARGET := server.out 

$(TARGET):$(OBJS)
	@echo $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS)
%.o:%.c 
	@echo Compling $<...
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY:clean

clean:
	rm -f *.o *.out *.so 

