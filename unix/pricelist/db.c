/*
 *  database functions
 *  ==================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "db.h"
#include "record.h"
#include "util.h"

/*  Returns number of bytes in the database file  */

off_t file_size(const int fd)
{
    return x_lseek(fd, 0, SEEK_END);
}

/*  Returns number of records in the database file  */

off_t num_records(const int fd)
{
    return file_size(fd) / RECORDSIZE;
}

/*  Prints summary information about the database file  */

void print_summary(const int fd, const char * filename)
{
    printf("Database file     : %s\n", filename);
    printf("Size of file      : %jd bytes\n", (intmax_t) file_size(fd));
    printf("Number of records : %jd\n", (intmax_t) num_records(fd));
    printf("\n");
}
