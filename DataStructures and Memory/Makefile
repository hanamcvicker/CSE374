# Copyright [2022] <Hana McVicker>
# CSE374, HW5, 22wi
# 11/28/2022
# t9 Makefile program

# This is "phony" target
# that just tells make what other targets to build.
all: t9

# The executable
t9: trie.o tnine.o
	gcc -Wall -std=c11 -g -o t9 trie.o tnine.o

# Individual source files
trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -g -c trie.c trienode.h

tnine.o: tnine.c trienode.h
	gcc -Wall -std=c11 -g -c tnine.c trienode.h

# "phony" target to remove built files and backups
clean:
	rm -f .o t9~
