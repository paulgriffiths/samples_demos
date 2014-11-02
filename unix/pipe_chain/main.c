#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include "pipe_utils.h"
#include "process_utils.h"

int main(void)
{
    pid_t pid[2];
    int pipe_fds[2];

    make_pipes(pipe_fds, NULL);

    /*  Fork child to run cat and pipe output to uniq  */

    if ( (pid[0] = fork_or_die()) == 0 ) {
        make_std_writer(pipe_fds);

        char * args[] = {"cat", "wordfile.asc", NULL};
        execvp_or_die("cat", args);
    };

    /*  Fork child to run uniq, get input from
     *  cat, and write output to standard output  */

    if ( (pid[1] = fork_or_die()) == 0 ) {
        make_std_reader(pipe_fds);

        char * args[] = {"uniq", "-c", NULL};
        execvp_or_die("uniq", args);
    };

    /*  Close pipes in parent and wait for children  */

    close_pipe_pair(pipe_fds);
    reap_children(pid, 2);

    return 0;
}
