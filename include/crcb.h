/*
 */
#ifndef CRCB_H
#define CRCB_H

#include <stdlib.h>

struct circularBuffer {
	char *data;
	size_t len;
	size_t cap;
	size_t activecap;
	size_t head; // ptr?
	size_t tail; // ptr?
};

void initialize(struct circularBuffer *b, char *buffer, size_t size);
void fillpattern(struct circularBuffer *b);
void printBuffer(struct circularBuffer *b);
void printState(struct circularBuffer *b);

void insert(struct circularBuffer *b, char v);
char bremove(struct circularBuffer *b);
char *reserve(struct circularBuffer *b, size_t need);
void fill(struct circularBuffer *b, size_t filled);


#endif