#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

#define FCB_IMPLEMENTATION
#include "fcb.h"

void check_growing(void)
{
    FCB b = fcb_new(4);

    fcb_enqueue(&b, 'b');
    fcb_enqueue(&b, 'b');
    fcb_enqueue(&b, 'b');
    fcb_enqueue(&b, 'b');
    // bbbb

    assert('b' == fcb_dequeue(&b));
    assert('b' == fcb_dequeue(&b));
    // --bb

    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'a');
    // aabb

    fcb_enqueue(&b, 'c');
    fcb_enqueue(&b, 'c');
    // aabb cc--

    const char expected[] = {'b', 'b', 'a', 'a', 'c', 'c' };
    for(size_t i = 0; ! fcb_is_empty(&b); i++) {
        assert(i <= sizeof(expected));
        assert(expected[i] == fcb_dequeue(&b));
    }

    fcb_free(&b);
}

void double_grow(void)
{
    FCB b = fcb_new(2);
    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'c'); // aa c-

    assert('a' == fcb_dequeue(&b)); // -a c-

    fcb_enqueue(&b, 'c');
    fcb_enqueue(&b, 'c'); // -a ccc---

    assert(b.old_top == 2);
    assert(fcb_size(&b) == 4);
    assert(b.capacity == 8);
    fcb_free(&b);
}

void make_buffer_circular_again(void)
{
    FCB b = fcb_new(2);

    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'c'); // aa c-

    assert('a' == fcb_dequeue(&b));
    assert('a' == fcb_dequeue(&b));

    assert(b.old_top == b.capacity);
    assert(b.old_size == 0);
    fcb_free(&b);
}

void check_accounting(void)
{
    FCB b = fcb_new(10);

    fcb_enqueue(&b, 42);
    assert(fcb_dequeue(&b) == 42);
    assert(fcb_is_empty(&b));
    fcb_free(&b);
}

void full2circular(void)
{
    FCB b = fcb_new(2);

    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'a');
    fcb_enqueue(&b, 'c');
    fcb_enqueue(&b, 'c'); // aa cc

    assert('a' == fcb_dequeue(&b));
    assert('a' == fcb_dequeue(&b)); // --cc

    assert(b.old_top == b.capacity);
    assert(b.old_size == 0);

    fcb_enqueue(&b, 'd'); // d-cc

    const char expected[] = {'c', 'c', 'd'};
    for(size_t i = 0; ! fcb_is_empty(&b); i++) {
        assert(i <= sizeof(expected));
        assert(expected[i] == fcb_dequeue(&b));
    }
    fcb_free(&b);
}

void underflow(void)
{
    FCB b = fcb_new(2);
    fcb_dequeue(&b);
    fcb_free(&b);
}

int main(void)
{
    check_accounting();
    check_growing();
    double_grow();
    make_buffer_circular_again();
    full2circular();

    // TODO: make this test work
    // underflow(); // must crash

    printf("[INFO] fcb-test completed\n");
    return 0;
}