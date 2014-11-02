#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe_utils.h"
#include "process_utils.h"

int main(void)
{
    pid_t pid[3];
    int p1to2[2], p2to3[2];

    make_pipes(p1to2, p2to3, NULL);

    if ( (pid[0] = fork_or_die()) == 0 ) {
        make_std_writer(p1to2);
        close_pipe_pair(p2to3);

        char * args[] = {"cat", "wordfile.asc", NULL};
        execvp_or_die("cat", args);
    }

    if ( (pid[1] = fork_or_die()) == 0 ) {
        make_std_reader(p1to2);
        make_std_writer(p2to3);

        char * args[] = {"uniq", "-c", NULL};
        execvp_or_die("uniq", args);
    }
    
    if ( (pid[2] = fork_or_die()) == 0 ) {
        close_pipe_pair(p1to2);
        make_std_reader(p2to3);

        char * args[] = {"sort", "-r", NULL};
        execvp_or_die("sort", args);
    }

    close_pipe_pair(p1to2);
    close_pipe_pair(p2to3);

    for ( size_t i = 0; i < 3; ++i ) {
        if ( waitpid(pid[i], NULL, 0) == -1 ) {
            perror("error calling waitpid()");
            return EXIT_FAILURE;
        }
    }

    return 0;
}
