#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "pipe_utils.h"

/*  Creates a pipe for each array in the NULL terminated arg list  */

void make_pipes(int * p, ...)
{
    va_list ap;
    va_start(ap, p);
    while ( p ) {
        if ( pipe(p) == -1 ) {
            perror("error calling pipe()");
            exit(EXIT_FAILURE);
        }
        p = va_arg(ap, int *);
    }
    va_end(ap);
}

/*  Closes a pipe pair and exits on error */

void close_pipe_pair(int * p)
{
    if ( close(p[0]) == -1 || close(p[1]) == -1 ) {
        perror("error calling close() in close_pipe_pair()");
        exit(EXIT_FAILURE);
    }
}

/*  Closes the write end of a pipe and duplicates
 *  the read end into STDIN_FILENO, exiting on error  */

void make_std_reader(int * p)
{
    static const int read_end = 0;
    static const int write_end = 1;

    if ( close(p[write_end]) == -1 ) {
        perror("error calling close() in make_std_reader()");
        exit(EXIT_FAILURE);
    }

    if ( p[read_end] != STDIN_FILENO ) {
        if ( dup2(p[read_end], STDIN_FILENO) == -1 ) {
            perror("error calling dup2() in make_std_reader()");
            exit(EXIT_FAILURE);
        }
        if ( close(p[read_end]) == -1 ) {
            perror("error calling close() in make_std_reader()");
            exit(EXIT_FAILURE);
        }
    }
}

/*  Closes the read end of a pipe and duplicates
 *  the write end into STDOUT_FILENO, exiting on error  */

void make_std_writer(int * p)
{
    static const int read_end = 0;
    static const int write_end = 1;

    if ( close(p[read_end]) == -1 ) {
        perror("error calling close() in make_std_writer()");
        exit(EXIT_FAILURE);
    }

    if ( p[write_end] != STDOUT_FILENO ) {
        if ( dup2(p[write_end], STDOUT_FILENO) == -1 ) {
            perror("error calling dup2() in make_std_writer()");
            exit(EXIT_FAILURE);
        }
        if ( close(p[write_end]) == -1 ) {
            perror("error calling close() in make_std_writer()");
            exit(EXIT_FAILURE);
        }
    }
}
