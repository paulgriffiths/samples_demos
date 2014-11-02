#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe_utils.h"
#include "process_utils.h"

int main(void)
{
    pid_t pid[2];
    int pipe_fds[2];

    make_pipes(pipe_fds, NULL);

    if ( (pid[0] = fork_or_die()) == 0 ) {
        make_std_writer(pipe_fds);

        char * args[] = {"cat", "wordfile.asc", NULL};
        execvp_or_die("cat", args);
    };

    if ( (pid[1] = fork_or_die()) == 0 ) {
        make_std_reader(pipe_fds);

        char * args[] = {"uniq", "-c", NULL};
        execvp_or_die("uniq", args);
    };

    close_pipe_pair(pipe_fds);
    
    for ( size_t i = 0; i < 2; ++i ) {
        if ( waitpid(pid[i], NULL, 0) == -1 ) {
            perror("error calling waitpid()");
            return EXIT_FAILURE;
        }
    }

    return 0;
}
