#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include "pipe_utils.h"
#include "process_utils.h"

int main(void)
{
    pid_t pid[3];
    int p1to2[2], p2to3[2];

    make_pipes(p1to2, p2to3, NULL);

    /*  Fork child to run cat and pipe output to uniq  */

    if ( (pid[0] = fork_or_die()) == 0 ) {
        make_std_writer(p1to2);
        close_pipe_pair(p2to3);

        char * args[] = {"cat", "wordfile.asc", NULL};
        execvp_or_die("cat", args);
    }

    /*  Fork child to run uniq, get input from
     *  cat, and pipe output to sort            */

    if ( (pid[1] = fork_or_die()) == 0 ) {
        make_std_reader(p1to2);
        make_std_writer(p2to3);

        char * args[] = {"uniq", "-c", NULL};
        execvp_or_die("uniq", args);
    }
    
    /*  Fork child to run sort, get input from uniq,
     *  and write output to standard output           */

    if ( (pid[2] = fork_or_die()) == 0 ) {
        close_pipe_pair(p1to2);
        make_std_reader(p2to3);

        char * args[] = {"sort", "-r", NULL};
        execvp_or_die("sort", args);
    }

    /*  Close pipes in parent and wait for children  */

    close_pipe_pair(p1to2);
    close_pipe_pair(p2to3);
    reap_children(pid, 3);

    return 0;
}
