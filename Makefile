# CSF Fall 2019
# Homework 1
# TODO: add your name
# TODO: add your email address

CC = gcc
CFLAGS = -g -std=c99 -pedantic -Wall -Wextra

%.o : %.c
	$(CC) -c $(CFLAGS) -o $*.o $<

hex : hex.o
	$(CC) -o $@ hex.o

solution.zip : Makefile hex.c
	rm -f solution.zip
	zip -9r $@ Makefile hex.c

clean :
	rm -f *.o hex solution.zip
