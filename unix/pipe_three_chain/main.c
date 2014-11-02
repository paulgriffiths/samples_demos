#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include "pipe_utils.h"
#include "process_utils.h"

int main(void)
{
    pid_t pid;
    int p1to2[2], p2to3[2];

    make_pipes(p1to2, p2to3, NULL);

    if ( (pid = fork_or_die()) == 0 ) {
        make_std_writer(p1to2);
        close_pipe_pair(p2to3);

        char * args[] = {"cat", "wordfile.asc", NULL};
        execvp_or_die("cat", args);
    } else {
        if ( (pid = fork_or_die()) == 0 ) {
            make_std_reader(p1to2);
            make_std_writer(p2to3);

            char * args[] = {"uniq", "-c", NULL};
            execvp_or_die("uniq", args);
        } else {
            close_pipe_pair(p1to2);
            make_std_reader(p2to3);

            char * args[] = {"sort", "-r", NULL};
            execvp_or_die("sort", args);
        }
    }

    return 0;
}
