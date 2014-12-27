/*
 *  record functions
 *  ================
 */

#ifndef PG_PRICELIST_RECORD_H
#define PG_PRICELIST_RECORD_H

#define MAX_NAME 20

struct record {
    char name[MAX_NAME];
    int price;
};

static const int RECORDSIZE = sizeof(struct record);

int seek_record(const int fd, const int index);
void get_new_record(struct record * record);
void write_record(const int fd, struct record * record, const int index);
int retrieve_record(const int fd, struct record * record, const int index);
void delete_record(const int fd, const int index);
void list_records(const int fd);

#endif      /*  PG_PRICELIST_RECORD_H  */
