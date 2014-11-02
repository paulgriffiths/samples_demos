#ifndef PG_SAMPLES_AND_DEMOS_CURSES_UTILS_H
#define PG_SAMPLES_AND_DEMOS_CURSES_UTILS_H

typedef struct curinfo * CursesHandle;

CursesHandle start_curses(void);
void stop_curses(CursesHandle handle);

#endif      /*  PG_SAMPLES_AND_DEMOS_CURSES_UTILS_H  */
