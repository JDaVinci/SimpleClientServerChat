######################################
# Makefile
# Krishna Sai Chemudupati
# November 6, 2018
# COSC 3750
#
# This is my Makefile for Assignment 6
########################################

CC=gcc
#Will have to remove -Wall from the flags. 
CFLAGS= -ggdb -Wall
RM=/bin/rm -f
.PHONY: clean all 

all: wytalkC wytalkD

wytalkC: wytalkC.c
	${CC} ${CFLAGS} wytalkC.c socketfun.c -o wytalkC

wytalkD: wytalkD.c
	${CC} ${CFLAGS} wytalkD.c socketfun.c -o wytalkD

socketfun.o: socketfun.c socketfun.h
	${CC} ${CFLAGS} -c socketfun.c  
clean: 
	\${RM}  wytalkC wytalkD
