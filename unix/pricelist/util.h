/*
 *  utility functions
 */

#ifndef PG_PRICELIST_UTIL_H
#define PG_PRICELIST_UTIL_H

#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

off_t x_lseek(int fd, off_t offset, int whence);
ssize_t x_write(int fd, void * buf, size_t count);
ssize_t x_read(int fd, void * buf, size_t count);
int x_ftruncate(int fd, off_t length);
int x_open(const char * pathname, int flags, mode_t mode);
int x_close(int fd);
void print_input_prompt(void);
void get_string(char * buffer, const size_t bufsize);
int get_integer(void);

#endif      /*  PG_PRICELIST_UTIL_H  */
