#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "simple_timer.h"

int main(void)
{
    printf("About to start countdown...\n");

    timer_start(1, 1);

    for ( int i = 10; i > 0; --i ) {
        pause();        //  Wait for a signal
        printf("Counting down...%d\n", i);
    }

    timer_stop();

    printf("0 - countdown over!\n");

    return 0;
}
