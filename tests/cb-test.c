#include <stdio.h>
#include <string.h>
#include <crcb.h>

#define BUFFER_CAP 16
char buffer[BUFFER_CAP];

struct CircularBuffer cb = {
    .data		 = buffer,
    .len		 = 0,
    .cap		 = BUFFER_CAP,
    .activecap	 = BUFFER_CAP,
    .head		 = 0,
    .tail		 = 0
};

void test0(void)
{
    printf("================== test0 ==================\n");

    memset(buffer, 0, BUFFER_CAP);
    initialize(&cb, buffer, BUFFER_CAP); // TODO: activecap should be 16

    // bremove(&cb); // error
    fillpattern(&cb);

    for(int i = 0; i < 16; i++) {
        insert(&cb, 0xaa);
    }
    // insert(&cb, 'e'); // error
    bremove(&cb);
    bremove(&cb);
    bremove(&cb);

    insert(&cb, 0xba);
    insert(&cb, 0xbe);
    printBuffer(&cb);
}

void test1(void)
{
    printf("================== test1 ==================\n");
    memset(buffer, 0, BUFFER_CAP);
    initialize(&cb, buffer, BUFFER_CAP); // TODO: activecap should be 16
    insert(&cb, 0xaa);
    insert(&cb, 0xaa);
    insert(&cb, 0xaa);

    char *addr = reserve(&cb, 9);
    if (addr) {
        // void *memset(void *s, int c, size_t n);
        memset(addr, 0x77, 8);
        fill(&cb, 8);

        printBuffer(&cb);
        printState(&cb);
    }

}

void test2(void)
{
    printf("================== test2 ==================\n");

    memset(buffer, 0, BUFFER_CAP);
    initialize(&cb, buffer, BUFFER_CAP);
    for(int i = 0; i < 16; i++) {
        insert(&cb, 0xaa);
    }

    for(int i = 0; i < 13; i++) {
        bremove(&cb);
    }

    insert(&cb, 0xbb);
    insert(&cb, 0xbb);
    insert(&cb, 0xbb);
    insert(&cb, 0xbb);

    char *addr = reserve(&cb, 9);
    if (addr) {
        // void *memset(void *s, int c, size_t n);
        memset(addr, 0x77, 8);
        fill(&cb, 8);

        printBuffer(&cb);
        printState(&cb);
    }
}

void test3(void)
{
    printf("================== test3 ==================\n");

    memset(buffer, 0, BUFFER_CAP);
    initialize(&cb, buffer, BUFFER_CAP);
    for(int i = 0; i < 8; i++) {
        insert(&cb, 0xaa);
    }

    for(int i = 0; i < 2; i++) {
        bremove(&cb);
    }


    char *addr = reserve(&cb, 5);
    if (addr) {
        // void *memset(void *s, int c, size_t n);
        memset(addr, 0x77, 5);
        fill(&cb, 5);

        printBuffer(&cb);
        printState(&cb);
    }
}


void test4(void)
{
    printf("================== test4 ==================\n");

    memset(buffer, 0, BUFFER_CAP);
    initialize(&cb, buffer, BUFFER_CAP);
    for(int i = 0; i < 10; i++) {
        insert(&cb, 0xaa);
    }

    for(int i = 0; i < 8; i++) {
        bremove(&cb);
    }


    char *addr = reserve(&cb, 7);
    if (addr) {
        // void *memset(void *s, int c, size_t n);
        memset(addr, 0x77, 7);
        fill(&cb, 7);

        printBuffer(&cb);
        printState(&cb);
    }

    bremove(&cb);
    bremove(&cb);
    bremove(&cb);

    printBuffer(&cb);
    printState(&cb);
}

void test5()
{
    printf("================== test5 ==================\n");

    memset(buffer, 0, BUFFER_CAP);
    initialize(&cb, buffer, BUFFER_CAP);
    for(int i = 0; i < 12; i++) {
        insert(&cb, 0xaa);
    }

    for(int i = 0; i < 7; i++) {
        bremove(&cb);
    }

    printBuffer(&cb);
    printState(&cb);

    char *addr = reserve(&cb, 8);
    if (addr) {
        // void *memset(void *s, int c, size_t n);
        printf("nani? how I got here?\n");
        memset(addr, 0x77, 3);
        fill(&cb, 3);

        printBuffer(&cb);
        printState(&cb);
    } else {
        printf("could not reserve %d\n", 8);
    }

}



void tests(void)
{
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
}

int main(void)
{
    tests();
    return 0;
}