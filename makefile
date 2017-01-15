all: file1 file2

file1: q1.c
	gcc -std=c99 q1.c -o q1

file2: q2.c
	gcc -std=c99 q2.c -o q2
