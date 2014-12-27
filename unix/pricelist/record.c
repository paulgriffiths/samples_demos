/*
 *  record functions
 *  ================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"
#include "db.h"
#include "util.h"

/*  Sets the file offset to the start of the record at
 *  the specified (one-based) index in the database. If
 *  index is -1, seeks to end of file. Returns 0 if index
 *  is invalid or out-of-range.                            */

int seek_record(const int fd, const int index)
{
    if ( index == -1 ) {
        x_lseek(fd, 0, SEEK_END);
    }
    else if ( index < 1 ) {
        return 0;
    }
    else {
        const off_t start = (index - 1) * RECORDSIZE;
        if ( start >= file_size(fd) ) {
            return 0;
        }
        else {
            x_lseek(fd, start, SEEK_SET);
        }
    }

    return 1;
}

/*  Gets a new record from standard input  */

void get_new_record(struct record * record)
{
    memset(record, 0, sizeof *record);

    printf("Enter record name (max. %d characters): ", MAX_NAME - 1);
    fflush(stdout);
    get_string(record->name, MAX_NAME);

    printf("Enter record price: ");
    fflush(stdout);
    record->price = get_integer();

    printf("\n");
}

/*  Writes a record at a (one-based) index in the database file  */

void write_record(const int fd, struct record * record, const int index)
{
    if ( !seek_record(fd, index) ) {
        fprintf(stderr, "Invalid record index in write_record().\n");
        exit(EXIT_FAILURE);
    }

    if ( x_write(fd, record, sizeof *record) != sizeof *record ) {
        fprintf(stderr, "Failed to write entire record.\n");
        exit(EXIT_FAILURE);
    }
}

/*  Retrieves a record at a (one-based) index in the database file  */

int retrieve_record(const int fd, struct record * record, const int index)
{
    if ( !seek_record(fd, index) ) {
        return 0;
    }

    if ( x_read(fd, record, sizeof *record) != sizeof *record ) {
        return 0;
    }

    return 1;
}

/*  Deletes the record at the specified (one-based) index  */

void delete_record(const int fd, const int index)
{
    const off_t nr = num_records(fd);
    if ( index < 1 || index > nr ) {
        fprintf(stderr, "Invalid record index in delete_record()\n");
        exit(EXIT_FAILURE);
    }

    for ( int i = index + 1; i <= nr; ++i ) {
        struct record record;
        retrieve_record(fd, &record, i);
        write_record(fd, &record, i - 1);
    }

    x_ftruncate(fd, (nr - 1) * RECORDSIZE);
}

/*  Prints all the records in the database file  */

void list_records(const int fd)
{
    struct record record;
    int record_num = 1;

    while ( retrieve_record(fd, &record, record_num) ) {
        printf("%d: %s, %d groats\n", record_num++, record.name, record.price);
    }

    printf("\n");
}
