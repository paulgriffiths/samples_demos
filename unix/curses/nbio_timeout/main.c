#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <curses.h>
#include <sys/select.h>
#include "curses_utils.h"

int main(void)
{
    int secs = 1;
    int usecs = 0;

    CursesHandle handle = start_curses();

    int input = '0';        /*  Set to something printable  */
    int num_loops = 0;      /*  Number of times through main loop  */

    while ( input != 'q' && input != 'Q' ) {

        /*  Output messages  */

        mvprintw(3, 3, "Main loop entered %d times", ++num_loops);
        mvprintw(4, 3, "Last character input was %c", input);
        mvprintw(5, 3, "Press 'q' to quit");
        refresh();

        /*  select() modifies the fd_sets passed to it,
         *  so zero and set them prior to each call.     */

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        /*  Same deal for the struct timeval, select() may
         *  modify it, it may not, so recreate to be portable.  */

        struct timeval tv;
        tv.tv_sec = secs;
        tv.tv_usec = usecs;

        /*  Wait for input or timeout  */

        if ( select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == -1 ) {

            /*  select() returned with an error.  */

            if ( errno != EINTR ) {

                /*  If interrupted by a signal, no problem,
                 *  keep going. Otherwise, let's just quit.  */

                stop_curses(handle);
                perror("error calling select()");
                return EXIT_FAILURE;
            }
        }
        else if ( FD_ISSET(STDIN_FILENO, &fds) ) {

            /*  Only call getch() if input is ready.
             *  getch() will not block when we do it this way.  */

            if ( (input = getch()) == ERR ) {
                stop_curses(handle);
                fprintf(stderr, "ERR returned from getch()\n");
                return EXIT_FAILURE;
            }
        }
    }

    stop_curses(handle);
    return 0;
}
