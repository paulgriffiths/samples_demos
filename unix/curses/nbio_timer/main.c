#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <curses.h>
#include <sys/select.h>
#include "curses_utils.h"
#include "simple_timer.h"

int main(void)
{
    sigset_t unblocked, blocked, oldmask;

    /*  Store current mask in both blocked and unblocked,
     *  and block SIGALRM in blocked, but unblock SIGALRM
     *  in unblocked. These masks are used in the pselect()
     *  call below, see comment in main loop.                */

    if ( sigprocmask(SIG_BLOCK, NULL, &unblocked) == -1 ||
         sigprocmask(SIG_BLOCK, NULL, &blocked) == -1 ) {
        perror("error calling sigprocmask() to init blocked and unblocked");
        exit(EXIT_FAILURE);
    }

    if ( sigaddset(&blocked, SIGALRM) == -1 ||
         sigdelset(&unblocked, SIGALRM) == -1 ) {
        perror("error setting blocked and unblocked");
        exit(EXIT_FAILURE);
    }

    /*  Block SIGALRM prior to entering main loop  */

    if ( sigprocmask(SIG_BLOCK, &blocked, &oldmask) == -1 ) {
        perror("error calling sigprocmask to block SIGALRM");
        exit(EXIT_FAILURE);
    }

    int input = '0';        /*  Set to something printable  */
    int num_loops = 0;      /*  Number of times through main loop  */
    int num_timer = 0;      /*  Number of times timer has fired  */
    int num_inputs = 0;     /*  Number of times input has been ready  */

    /*  Start curses and start timer  */

    CursesHandle handle = start_curses();
    timer_start(1, 1);

    /*  Main loop  */

    while ( input != 'q' && input != 'Q' ) {

        /*  Output messages  */

        mvprintw(3, 3, "Main loop entered %d times", ++num_loops);
        mvprintw(4, 3, "Timer has fired %d times", num_timer);
        mvprintw(5, 3, "Input has been ready %d times", num_inputs);
        mvprintw(6, 3, "Last character input was %c", input);
        mvprintw(7, 3, "Press 'q' to quit");
        refresh();

        /*  pselect() modifies the fd_sets passed to it,
         *  so zero and set them prior to each call.      */

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        /*  Wait for input or timeout  */

        int status;

        if ( (status = pselect(STDIN_FILENO + 1, &fds, NULL,
                               NULL, NULL, &unblocked)) == -1 ) {

            /*  pselect() returned with an error.  */

            if ( errno == EINTR ) {

                /*  If interrupted by a signal, no problem,
                 *  keep going...                            */

                ++num_timer;
            }
            else {

                /*  ...otherwise, quit.  */

                stop_curses(handle);
                perror("perror calling select()");
                return EXIT_FAILURE;
            }
        }
        else if ( status == 1 ) {
            ++num_inputs;

            /*  Only call getch() if input is ready.
             *  getch() will not block when we do it this way.  */

            if ( (input = getch()) == ERR ) {
                stop_curses(handle);
                fprintf(stderr, "ERR returned from getch()\n");
                return EXIT_FAILURE;
            }
        }
        else {
            stop_curses(handle);
            fprintf(stderr, "pselect() returned something unexpected.\n");
            return EXIT_FAILURE;
        }
    }

    timer_stop();

    /*  Restore original signal mask  */

    if ( sigprocmask(SIG_BLOCK, &oldmask, NULL) == -1 ) {
        perror("error calling sigprocmask() to restore old mask");
        exit(EXIT_FAILURE);
    }

    stop_curses(handle);
    return 0;
}
