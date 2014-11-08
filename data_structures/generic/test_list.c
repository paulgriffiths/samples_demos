#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "test_list.h"
#include "test_logging.h"

static void test_list_basic(void)
{
    List list = list_create(DATATYPE_INT, 0);
    if ( !list ) {
        perror("couldn't create list");
        exit(EXIT_FAILURE);
    }

    int n;
    size_t sz;
    bool status;
        
    sz = list_length(list);
    tests_log_test(sz == 0, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(status, "list_is_empty() gave wrong value");
    
    status = list_element_at_index(list, 0, &n);
    tests_log_test(!status, "list_element_at_index() didn't return false");

    status = list_delete_index(list, 0);
    tests_log_test(!status, "list_delete_at_index() didn't return false");

    status = list_insert(list, 0, 4);
    tests_log_test(status, "list_insert_index() didn't return true");

    status = list_element_at_index(list, 0, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 4, "list_element_at_index() gave wrong value");

    sz = list_length(list);
    tests_log_test(sz == 1, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");
    
    status = list_insert(list, 0, 5);
    tests_log_test(status, "list_insert_index() didn't return true");

    status = list_element_at_index(list, 0, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 5, "list_element_at_index() gave wrong value");

    sz = list_length(list);
    tests_log_test(sz == 2, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");
    
    status = list_element_at_index(list, 1, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 4, "list_element_at_index() gave wrong value");

    status = list_insert(list, 2, 7);
    tests_log_test(status, "list_insert_index() didn't return true");

    status = list_element_at_index(list, 2, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 7, "list_element_at_index() gave wrong value");

    sz = list_length(list);
    tests_log_test(sz == 3, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");
    
    status = list_element_at_index(list, 0, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 5, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 1, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 4, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 3, &n);
    tests_log_test(!status, "list_element_at_index() didn't return false");

    status = list_delete_index(list, 3);
    tests_log_test(!status, "list_delete_at_index() didn't return false");

    status = list_delete_front(list);
    tests_log_test(status, "list_delete_front() didn't return true");

    sz = list_length(list);
    tests_log_test(sz == 2, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");
    
    status = list_element_at_index(list, 0, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 4, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 1, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 7, "list_element_at_index() gave wrong value");

    status = list_delete_back(list);
    tests_log_test(status, "list_delete_back() didn't return true");

    sz = list_length(list);
    tests_log_test(sz == 1, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");
    
    status = list_element_at_index(list, 0, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 4, "list_element_at_index() gave wrong value");

    status = list_delete_back(list);
    tests_log_test(status, "list_delete_back() didn't return true");

    sz = list_length(list);
    tests_log_test(sz == 0, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(status, "list_is_empty() gave wrong value");

    status = list_append(list, 11);
    tests_log_test(status, "list_append() didn't return true");

    status = list_append(list, 12);
    tests_log_test(status, "list_append() didn't return true");

    status = list_prepend(list, 10);
    tests_log_test(status, "list_prepend() didn't return true");

    status = list_prepend(list, 9);
    tests_log_test(status, "list_prepend() didn't return true");

    sz = list_length(list);
    tests_log_test(sz == 4, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");

    status = list_element_at_index(list, 0, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 9, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 1, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 10, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 2, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 11, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 3, &n);
    tests_log_test(status, "list_element_at_index() didn't return true");
    tests_log_test(n == 12, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 4, &n);
    tests_log_test(!status, "list_element_at_index() didn't return false");

    while ( !list_is_empty(list) ) {
        status = list_delete_front(list);
        tests_log_test(status, "list_delete_front() didn't return true");
    }

    sz = list_length(list);
    tests_log_test(sz == 0, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(status, "list_is_empty() gave wrong value");


    
    list_destroy(list);
}

static void test_list_free_strings(void)
{
    List list = list_create(DATATYPE_STRING, GDS_FREE_ON_DESTROY);
    if ( !list ) {
        perror("couldn't create list");
        exit(EXIT_FAILURE);
    }

    bool status;
    size_t sz;
    char * pc;

    status = list_append(list, strdup("First string"));
    tests_log_test(status, "list_append() failed");

    status = list_append(list, strdup("Second string"));
    tests_log_test(status, "list_append() failed");

    status = list_append(list, strdup("Third string"));
    tests_log_test(status, "list_append() failed");

    sz = list_length(list);
    tests_log_test(sz == 3, "list_length() gave wrong value");

    status = list_is_empty(list);
    tests_log_test(!status, "list_is_empty() gave wrong value");
    
    status = list_element_at_index(list, 0, &pc);
    tests_log_test(status, "list_element_index() failed");
    tests_log_test(!strcmp(pc, "First string"),
                   "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 1, &pc);
    tests_log_test(status, "list_element_index() failed");
    tests_log_test(!strcmp(pc, "Second string"),
                   "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 2, &pc);
    tests_log_test(status, "list_element_index() failed");
    tests_log_test(!strcmp(pc, "Third string"),
                   "list_element_at_index() gave wrong value");

    list_destroy(list);
}

static void test_list_set_element(void)
{
    List list = list_create(DATATYPE_UNSIGNED_LONG, 0);
    if ( !list ) {
        perror("couldn't create list");
        exit(EXIT_FAILURE);
    }

    bool status;
    unsigned long l;

    status = list_append(list, 42UL);
    tests_log_test(status, "list_append() failed");

    status = list_append(list, 53UL);
    tests_log_test(status, "list_append() failed");

    status = list_append(list, 65UL);
    tests_log_test(status, "list_append() failed");

    status = list_append(list, 76UL);
    tests_log_test(status, "list_append() failed");

    status = list_element_at_index(list, 0, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 42, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 1, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 53, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 2, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 65, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 3, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 76, "list_element_at_index() gave wrong value");

    status = list_set_element_at_index(list, 1, 87UL);
    tests_log_test(status, "list_set_element_at_index() failed");

    status = list_set_element_at_index(list, 2, 98UL);
    tests_log_test(status, "list_set_element_at_index() failed");

    status = list_element_at_index(list, 0, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 42, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 1, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 87, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 2, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 98, "list_element_at_index() gave wrong value");

    status = list_element_at_index(list, 3, &l);
    tests_log_test(status, "list_element_at_index() failed");
    tests_log_test(l == 76, "list_element_at_index() gave wrong value");

    list_destroy(list);
}

void test_list(void)
{
    test_list_basic();
    test_list_free_strings();
    test_list_set_element();
}
