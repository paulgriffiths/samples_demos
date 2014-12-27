/*
 *  database functions
 *  ==================
 */

#ifndef PG_PRICELIST_DB_H
#define PG_PRICELIST_DB_H

#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>

off_t file_size(const int fd);
off_t num_records(const int fd);
void print_summary(const int fd, const char * filename);

#endif      /*  PG_PRICELIST_DB_H  */
