# NBIO Timer

This program demonstrates the use of a `SIGALRM` timer to interrupt
a blocking call to `getch()`. This technique is useful when tasks
must regularly be performed while waiting for input, avoiding the
need for continuous polling.
