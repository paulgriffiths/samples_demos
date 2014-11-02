#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

/*  Struct to contain curses info  */

struct curinfo {
    WINDOW * main_window;
    int old_cursor;
};

/*  Starts curses and populates the passed struct  */

struct curinfo * start_curses(void)
{
    struct curinfo * new_info = malloc(sizeof *new_info);
    if ( !new_info ) {
        perror("couldn't allocate memory for curses handle");
        exit(EXIT_FAILURE);
    }

    if ( (new_info->main_window = initscr()) == NULL ) {
        fprintf(stderr, "Error calling initscr()\n");
        exit(EXIT_FAILURE);
    }

    noecho();
    keypad(new_info->main_window, TRUE);
    crmode();
    new_info->old_cursor = curs_set(0);
    refresh();

    return new_info;
}

/*  Stops curses and cleans up  */

void stop_curses(struct curinfo * info)
{
    curs_set(info->old_cursor);
    endwin();
    free(info);
}
