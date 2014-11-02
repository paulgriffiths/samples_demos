#ifndef PG_SAMPLES_AND_DEMOS_PIPE_UTILS_H
#define PG_SAMPLES_AND_DEMOS_PIPE_UTILS_H

void make_pipes(int * p, ...);
void close_pipe_pair(int * p);
void make_std_reader(int * p);
void make_std_writer(int * p);

#endif      /*  PG_SAMPLES_AND_DEMOS_PIPE_UTILS_H  */
