/*
 *  utility functions
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static const size_t BUFFSIZE = 1024;

/*  Calls lseek() and exits on error  */

off_t x_lseek(int fd, off_t offset, int whence)
{
    const off_t result = lseek(fd, offset, whence);
    if ( result == -1 ) {
        perror("lseek() error");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*  Calls write() and exits on error  */

ssize_t x_write(int fd, void * buf, size_t count)
{
    const ssize_t result = write(fd, buf, count);
    if ( result == -1 ) {
        perror("write() error");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*  Calls read() and exits on error  */

ssize_t x_read(int fd, void * buf, size_t count)
{
    const ssize_t result = read(fd, buf, count);
    if ( result == -1 ) {
        perror("write() error");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*  Calls ftruncate() and exits on error  */

int x_ftruncate(int fd, off_t length)
{
    const int result = ftruncate(fd, length);
    if ( result == -1 ) {
        perror("ftruncate() error");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*  Calls open() and exits on error  */

int x_open(const char * pathname, int flags, mode_t mode)
{
    const int result = open(pathname, flags, mode);
    if ( result == -1 ) {
        perror("open() error");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*  Calls close() and exits on error  */

int x_close(int fd)
{
    const int result = close(fd);
    if ( result == -1 ) {
        perror("close() error");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*  Prints an input prompt  */

void print_input_prompt(void)
{
    printf("> ");
    fflush(stdout);
}

/*  Gets a string from standard input and trims newline, if present  */

void get_string(char * buffer, const size_t bufsize)
{
    if ( !fgets(buffer, bufsize, stdin) ) {
        fprintf(stderr, "Couldn't get line in get_string().\n");
        exit(EXIT_FAILURE);
    }

    const size_t buflen = strlen(buffer);
    if ( buflen && buffer[buflen - 1] == '\n' ) {
        buffer[buflen - 1] = '\0';
    }
    else {
        while ( true ) {
            char discard[BUFFSIZE];
            if ( !fgets(discard, BUFFSIZE, stdin) ) {
                fprintf(stderr, "Couldn't get line in get_string().\n");
                exit(EXIT_FAILURE);
            }

            const size_t discard_len = strlen(discard);
            if ( discard_len && discard[discard_len - 1] == '\n' ) {
                break;
            }
        }
    }
}

/*  Gets an integer from standard input  */

int get_integer(void)
{
    long input;
    bool good_input = false;

    while ( !good_input ) {
        char buffer[BUFFSIZE];
        get_string(buffer, BUFFSIZE);

        char * endptr;
        input = strtol(buffer, &endptr, 0);
        if ( *endptr ) {
            printf("Invalid integer - try again.\n");
            print_input_prompt();
        }
        else if ( input > INT_MAX ) {
            printf("Integer too large - try again.\n");
            print_input_prompt();
        }
        else {
            good_input = true;
        }
    };

    return (int) input;
}
