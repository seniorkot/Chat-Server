COMP=gcc
TARGET=c_server
CFLAGS= -std=c89 -pedantic -Wall -lpthread
MLINK= -o
FILES= ./server/server.c ./server/session.c ./server/message.c

c_server: ./server/server.c
	$(COMP) $(MLINK) $(TARGET) $(CFLAGS) $(FILES)