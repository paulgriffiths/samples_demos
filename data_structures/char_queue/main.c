#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "char_queue.h"

CharQueue get_queue_from_file(void)
{
    CharQueue cq = char_queue_create(1024);
    FILE * fp = fopen("textfile.txt", "r");
    if ( !fp ) {
        perror("couldn't open file for reading");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while ( fgets(buffer, sizeof buffer, fp) ) {
        char_queue_enqueue_string(cq, buffer);
    }

    fclose(fp);
    return cq;
}

int main(void)
{
    CharQueue cq = get_queue_from_file();
    printf("Enqueued from file - size %zu, front %zu, back %zu, free %zu\n",
           char_queue_size(cq), char_queue_front(cq),
           char_queue_back(cq), char_queue_free(cq));
    printf("Number of lines in queue - %zu\n", char_queue_lines(cq));

    char buffer[1024];
    while ( !char_queue_is_empty(cq) ) {
        const size_t num_read = char_queue_dequeue_line(cq,
                                                        buffer,
                                                        sizeof buffer);
        printf("Read %zu characters: %s\n", num_read, buffer);
    }

    char_queue_destroy(cq);

    return 0;
}
