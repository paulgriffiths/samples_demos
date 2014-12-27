/*
 *  pricelist
 *  =========
 *
 *  A simple database application to demonstrate
 *  simple UNIX file handling with fixed-size records.
 *
 *  Copyright (C) Paul Griffiths
 *  December 26, 1024
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util.h"
#include "db.h"
#include "record.h"
#include "menu.h"

/*  Main function  */

int main(int argc, char ** argv)
{
    if ( argc != 2 ) {
        fprintf(stderr, "Usage: pricelist FILENAME\n");
        return EXIT_FAILURE;
    }

    const int dbfd = x_open(argv[1], O_RDWR | O_CREAT, 0644);

    bool should_quit = false;

    while ( !should_quit ) {
        print_summary(dbfd, argv[1]);
        int choice = get_menu_choice();

        struct record record;

        switch ( choice ) {
            case MENU_LIST:
                list_records(dbfd);
                break;

            case MENU_ADD:
                get_new_record(&record);
                write_record(dbfd, &record, -1);
                break;

            case MENU_DELETE:
                printf("Enter record number to delete: ");
                fflush(stdout);
                delete_record(dbfd, get_integer());
                break;

            case MENU_QUIT:
                printf("Goodbye!\n");
                should_quit = true;
                break;

            default:
                printf("Invalid menu choice. Try again.\n\n");
                break;
        }
    }

    x_close(dbfd);

    return 0;
}
