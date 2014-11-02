#ifndef PG_SAMPLES_AND_DEMOS_PROCESS_UTILS_H
#define PG_SAMPLES_AND_DEMOS_PROCESS_UTILS_H

#include <unistd.h>
#include <sys/types.h>

pid_t fork_or_die(void);
void execv_or_die(const char * path, char * const argv[]);
void execvp_or_die(const char * path, char * const argv[]);
void reap_children(pid_t * ids, const size_t count);

#endif      /*  PG_SAMPLES_AND_DEMOS_PROCESS_UTILS_H  */
