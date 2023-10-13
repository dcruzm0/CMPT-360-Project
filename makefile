#################################################################################
# name: Mark D'Cruz, Keegan Vanstone
# lab section: CMPT 360
# Lab 2 makefile
# file purpose: This file is the makefile
################################################################################

CC = gcc
CFLAGS = -Wall -std=c11

all: main Lab2.tar.gz

main: main.c dataStructures.c dataStructures.h history.c history.h
	$(CC) $(CFLAGS) main.c dataStructures.c dataStructures.h history.c history.h -o main

Lab2.tar.gz: dataStructures.c dataStructures.h main.c makefile
	tar -zcvf Lab2.tar.gz dataStructures.c dataStructures.h main.c makefile history.c history.h

