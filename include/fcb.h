#ifndef FCB_H
#define FCB_H

typedef struct {
    int* items;
    int capacity;
    int size;
    int write_ptr;
    int read_ptr;
    int old_top;
    int old_size;
} FCB;

FCB fcb_new(int capacity);
void fcb_free(FCB *q);
int fcb_is_empty(FCB* q);
int fcb_size(FCB* q);
void fcb_enqueue(FCB* q, int element);
int fcb_dequeue(FCB* q);

#endif // FCB_H

#ifdef FCB_IMPLEMENTATION

#define log_error printf

#define min(a, b) ((a) < (b))? (a) : (b)

FCB fcb_new(int capacity)
{
    if (capacity <= 0) {
        capacity = 0;
    }

    void *items = malloc(sizeof(int) * capacity);
    if (!items) {
        log_error("Memory allocation failed");
        return (FCB){0};
    }

    FCB result = {
        .items = items,
        .capacity = capacity,
        .old_top = capacity
    };

    return result;
}

void fcb_free(FCB *q)
{
    free(q->items);
}

int fcb_is_empty(FCB* q)
{
    return q->size == 0;
}

int fcb_size(FCB* q)
{
    return q->size;
}

void fcb_enqueue(FCB* q, int element)
{
    assert(q->old_top <= q->capacity);
    if (((q->size + 1 > q->capacity) && (q->capacity == q->old_top))
            || ((q->write_ptr == 0)  && (q->capacity != q->old_top)))
    {
        int new_capacity = 2*q->capacity;
        q->items = realloc(q->items, new_capacity * sizeof(*q->items));
        assert(q->items && "not enougth memory");
        q->write_ptr = q->capacity;
        q->capacity = new_capacity;
        q->old_size = q->size;
    }

    q->items[q->write_ptr++] = element;
    q->write_ptr %= q->capacity;
    q->size++;
}

int fcb_dequeue(FCB* q)
{
    int result = -1;
    if (q->size) {
        result = q->items[q->read_ptr++];
        q->read_ptr %= q->old_top;
        q->size--;
        if(q->old_size) {
            q->old_size--;
            if (!q->old_size) {
                q->read_ptr = q->old_top;
                q->old_top = q->capacity;
            }
        }
    }
    return result;
}

#endif // FCB_IMPLEMENTATION