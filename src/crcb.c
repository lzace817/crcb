#include <stdio.h>
#include <assert.h>
#include <crcb.h>

#define COLS 16

// auxiliar fuctionality
void initialize(struct circularBuffer *b, char *buffer, size_t size)
{
	b->data = buffer;
	b->cap = size;

	b->len = 0;
	b->head = 0;
	b->tail = 0;
	b->activecap = size;
}

void fillpattern(struct circularBuffer *b)
{
	for(size_t i = 0; i < b->cap; i++) {
		b->data[i] = i % 32;
	}
}

void printBuffer(struct circularBuffer *b)
{
	size_t i;
	for( i = 0; i + COLS <= b->cap; i+=COLS) {
		printf("%08lx: ", i);
		for(int j = 0; j < COLS; j+=2) {
			printf("%02x%02x ",(unsigned char) b->data[i+j],
				(unsigned char) b->data[i+j+1]);
		}
		printf("\n");
	}
	if (i < b->cap) {
		printf("%08lx: ", i);
		for(size_t j = i; j < b->cap; j++) {
			printf("%02x",(unsigned char) b->data[j]);
			if (j % 2)
				printf(" ");
		}
		printf("\n");
	}
}

void printState(struct circularBuffer *b)
{
	printf("cap %ld\n",		 b->cap);
	printf("activecap %ld\n",	 b->activecap);
	printf("len %ld\n",		 b->len);
	printf("head %ld\n",		 b->head);
	printf("tail %ld\n",		 b->tail);
}


/* insert a single character to buffer
 * b : buffer
 * v : character
 */
void insert(struct circularBuffer *b, char v)
{
	assert(b->len < b->activecap && "the buffer is full");
	b->data[b->head++] = v;
	b->len++;
	if (b->head == b->cap)
		b->head = 0;
}

/* remove single character from buffer
 * b : buffer
 * returns character in front of buffer
 */
char bremove(struct circularBuffer *b)
{
	assert(b->len > 0 && "the buffer is empty");
	char tmp = b->data[b->tail];
	#if DEBUG
	b->data[b->tail] = 0;
	#endif
	b->tail++;
	b->len--;
	if(b->tail == b->activecap) {
		b->activecap = b->cap;
		b->tail = 0;
	}
	return tmp;
}


/* reserve contiguous space in the buffer
 * b: buffer
 * need: the amount of contiguous needed space
 * return pointer to the begining of reserved space if possible
 * or NULL if fail
 */
char *reserve(struct circularBuffer *b, size_t need)
{
	// activecap = len + empty
	if (b->tail < b->head) {
		// need to worry

		// take the run up to the end of the buffer
		size_t contiguous = b->cap - b->head;
		if (need <= contiguous)
			// return true;
			return &b->data[b->head];

		// there is no contigous space from current head position
		// up to the end of buffer. but maybe there is space
		// from begining of buffer up to before tail begins

		if (need <= b->tail) {

			b->activecap = b->head; //shrinks the buffer
			b->head = 0;
			// return true;
			return &b->data[b->head];
		}
	} else {
		// don't worry
		if (need <= (b->activecap - b->len)) {
			// return true;
			return &b->data[b->head];
		}
	}
	// return false;
	return NULL;
}

/* This MUST only be called after reserve whith filled <= need.
 * Set the buffer to acount for <filled> characters inserted in the
 * begining of the contiguous reserved space.
 * b : buffer
 * filled: quantity of filled character in the begining of reserved
 * space.
 */
void fill(struct circularBuffer *b, size_t filled)
{
	// assume filled < need
	b->head += filled;
	b->len += filled;
}

bool is_empty(struct circularBuffer *b)
{
	return b->len == 0;
}

bool is_full(struct circularBuffer *b)
{
	return b->len == b->activecap;
}