#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "char_queue.h"

/*  Struct to hold a character queue  */

struct char_queue {
    char * data;
    size_t front;
    size_t back;
    size_t capacity;
    size_t lines;
};

/*  Creates a character queue with a specified capacity  */

struct char_queue * char_queue_create(const size_t capacity)
{
    struct char_queue * new_queue = malloc(sizeof *new_queue);
    if ( !new_queue ) {
        perror("couldn't allocate memory for char_queue");
        exit(EXIT_FAILURE);
    }

    new_queue->data = malloc(capacity);
    if ( !new_queue->data ) {
        perror("couldn't allocate memory for char_queue data");
        exit(EXIT_FAILURE);
    }

    new_queue->capacity = capacity;
    new_queue->front = 0;
    new_queue->back = 0;
    new_queue->lines = 0;

    return new_queue;
}

/*  Destroys a previously created character queue  */

void char_queue_destroy(struct char_queue * queue)
{
    free(queue->data);
    free(queue);
}

/*  Returns the character currently at the front of the queue  */

char char_queue_peek(struct char_queue * queue)
{
    assert(!char_queue_is_empty(queue));

    return queue->data[queue->front];
}

/*  Enqueues a character onto a character queue  */

size_t char_queue_enqueue(struct char_queue * queue, const char c)
{
    assert(!char_queue_is_full(queue));

    queue->data[queue->back++] = c;
    if ( queue->back == queue->capacity ) {
        queue->back = 0;
    }

    if ( c == '\n' ) {
        ++queue->lines;
    }

    return 1;
}

/*  Enqueues a string of characters onto a character queue  */

size_t char_queue_enqueue_string(struct char_queue * queue, const char * str)
{
    const size_t len = strlen(str);
    assert(len <= char_queue_free(queue));

    while ( *str ) {
        char_queue_enqueue(queue, *str++);
    }

    return len;
}

/*  Dequeues a single character from a character queue  */

char char_queue_dequeue(struct char_queue * queue)
{
    assert(!char_queue_is_empty(queue));

    const char retval = queue->data[queue->front++];
    if ( queue->front == queue->capacity ) {
        queue->front = 0;
    }

    if ( retval == '\n' ) {
        --queue->lines;
    }

    return retval;
}

/*  Dequeues n - 1 characters from a character queue
 *  and copies them into the supplied string.         */

size_t char_queue_dequeue_string(struct char_queue * queue,
                                 char * str, const size_t n)
{
    assert((n - 1) <= char_queue_size(queue));

    for ( size_t i = 0; i < (n - 1); ++i ) {
        *str++ = char_queue_dequeue(queue);
    }

    *str = 0;

    return n - 1;
}

/*  Dequeues a line from the queue, up to n - 1 characters.
 *  The newline character is *not* included in the dequeued line.  */

size_t char_queue_dequeue_line(struct char_queue * queue,
                               char * str, const size_t n)
{
    assert(!char_queue_is_empty(queue));

    const size_t iqs = char_queue_size(queue);

    size_t i;
    for ( i = 0; i < iqs && i < (n - 1); ++i ) {
        const char c = char_queue_dequeue(queue);

        if ( c == '\n' ) {
            break;
        }
        else {
            str[i] = c;
        }
    }

    str[i] = 0;
    return i;
}

/*  Debugging method to return the index of the front of the queue  */

size_t char_queue_front(struct char_queue * queue)
{
    return queue->front;
}

/*  Debugging method to return the index of the back of the queue  */

size_t char_queue_back(struct char_queue * queue)
{
    return queue->back;
}

/*  Returns the capacity of the queue  */

size_t char_queue_capacity(struct char_queue * queue)
{
    return queue->capacity;
}

/*  Returns the number of elements currently in the queue  */

size_t char_queue_size(struct char_queue * queue)
{
    if ( queue->back >= queue->front ) {
        return queue->back - queue->front;
    }
    else {
        return queue->capacity - (queue->front - queue->back);
    }
}

/*  Returns the number of free places in the queue  */

size_t char_queue_free(struct char_queue * queue)
{
    return char_queue_capacity(queue) - char_queue_size(queue);
}
 
/*  Returns the number of lines in the queue  */

size_t char_queue_lines(struct char_queue * queue)
{
    return queue->lines;
}

/*  Tests whether the queue is empty  */

bool char_queue_is_empty(struct char_queue * queue)
{
    return char_queue_size(queue) == 0;
}

/*  Tests whether the queue is full  */

bool char_queue_is_full(struct char_queue * queue)
{
    return char_queue_size(queue) == queue->capacity;
}
