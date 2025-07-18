/*
 */
#ifndef CRCB_H
#define CRCB_H

#include <stdlib.h>

struct CircularBuffer {
	char *data;
	size_t len;
	size_t cap;
	size_t activecap;
	size_t head; // ptr?
	size_t tail; // ptr?
};

void initialize(struct CircularBuffer *b, char *buffer, size_t size);
void fillpattern(struct CircularBuffer *b);
void printBuffer(struct CircularBuffer *b);
void printState(struct CircularBuffer *b);

void insert(struct CircularBuffer *b, char v);
char bremove(struct CircularBuffer *b);
char *reserve(struct CircularBuffer *b, size_t need);
void fill(struct CircularBuffer *b, size_t filled);


#endif