#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process_utils.h"

/*  Calls fork() and exits on error  */

pid_t fork_or_die(void)
{
    pid_t p = fork();
    if ( p == -1 ) {
        perror("error calling fork()");
        exit(EXIT_FAILURE);
    }
    return p;
}

/*  Calls execv() and exits on error  */

void execv_or_die(const char * path, char * const argv[])
{
    if ( execv(path, argv) == -1 ) {
        perror("error calling execv()");
        exit(EXIT_FAILURE);
    }
}

/*  Calls execvp() and exits on error  */

void execvp_or_die(const char * path, char * const argv[])
{
    if ( execvp(path, argv) == -1 ) {
        perror("error calling execvp()");
        exit(EXIT_FAILURE);
    }
}

/*  Waits for an array of children  */

void reap_children(pid_t * ids, const size_t count)
{
    for ( size_t i = 0; i < count; ++i ) {
        if ( waitpid(ids[i], NULL, 0) == -1 ) {
            perror("error calling waitpid()");
            exit(EXIT_FAILURE);
        }
    }
}
