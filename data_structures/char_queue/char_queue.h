#ifndef PG_CHAR_QUEUE_H
#define PG_CHAR_QUEUE_H

#include <stdbool.h>

typedef struct char_queue * CharQueue;

CharQueue char_queue_create(const size_t capacity);
void char_queue_destroy(CharQueue queue);

size_t char_queue_enqueue(CharQueue, const char c);
size_t char_queue_enqueue_string(CharQueue queue, const char * str);
char char_queue_peek(CharQueue queue);
char char_queue_dequeue(CharQueue queue);
size_t char_queue_dequeue_string(CharQueue queue, char * str, const size_t n);
size_t char_queue_dequeue_line(CharQueue queue, char * str, const size_t n);
size_t char_queue_front(CharQueue queue);
size_t char_queue_back(CharQueue queue);
size_t char_queue_capacity(CharQueue queue);
size_t char_queue_size(CharQueue queue);
size_t char_queue_free(CharQueue queue);
size_t char_queue_lines(CharQueue queue);

bool char_queue_is_empty(CharQueue queue);
bool char_queue_is_full(CharQueue queue);

#endif      /*  PG_CHAR_QUEUE_H  */
