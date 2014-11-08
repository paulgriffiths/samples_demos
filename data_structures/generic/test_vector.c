#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "test_vector.h"
#include "test_logging.h"

static void test_vector_basic(void)
{
    Vector vector = vector_create(3, DATATYPE_INT, 0);
    if ( !vector ) {
        perror("couldn't create vector");
        exit(EXIT_FAILURE);
    }

    int n;
    size_t sz;
    bool status;
        
    sz = vector_length(vector);
    tests_log_test(sz == 3, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 3, "vector_capacity() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 0, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    status = vector_element_at_index(vector, 4, &n);
    tests_log_test(!status, "vector_element_at_index() didn't return false");

    status = vector_delete_index(vector, 4);
    tests_log_test(!status, "vector_delete_at_index() didn't return false");

    status = vector_set_element_at_index(vector, 0, 4);
    tests_log_test(status, "vector_set_element_at_index() didn't return true");

    status = vector_set_element_at_index(vector, 1, 5);
    tests_log_test(status, "vector_set_element_at_index() didn't return true");

    status = vector_set_element_at_index(vector, 2, 6);
    tests_log_test(status, "vector_set_element_at_index() didn't return true");

    status = vector_element_at_index(vector, 0, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 4, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 5, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 6, "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 3, "vector_length() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");

    status = vector_prepend(vector, 3);
    tests_log_test(status, "vector_prepend() didn't return true");

    status = vector_element_at_index(vector, 0, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 3, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 4, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 5, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 3, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 6, "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 4, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 6, "vector_capacity() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 2, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    status = vector_insert(vector, 2, 7);
    tests_log_test(status, "vector_insert_index() didn't return true");

    status = vector_element_at_index(vector, 0, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 3, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 4, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 7, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 3, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 5, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 4, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 6, "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 5, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 6, "vector_capacity() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 1, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    status = vector_append(vector, 8);
    tests_log_test(status, "vector_append() didn't return true");

    status = vector_element_at_index(vector, 0, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 3, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 4, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 7, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 3, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 5, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 4, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 6, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 5, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 8, "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 6, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 6, "vector_capacity() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 0, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    status = vector_delete_front(vector);
    tests_log_test(status, "vector_delete_front() failed");

    status = vector_delete_back(vector);
    tests_log_test(status, "vector_delete_back() failed");

    status = vector_delete_index(vector, 2);
    tests_log_test(status, "vector_delete_back() failed");

    status = vector_element_at_index(vector, 0, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 4, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 7, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 6, "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 3, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 6, "vector_capacity() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 3, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    status = vector_set_element_at_index(vector, 0, 11);
    tests_log_test(status, "vector_set_element_at_index() didn't return true");

    status = vector_set_element_at_index(vector, 2, 9);
    tests_log_test(status, "vector_set_element_at_index() didn't return true");

    status = vector_element_at_index(vector, 0, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 11, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 7, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &n);
    tests_log_test(status, "vector_element_at_index() didn't return true");
    tests_log_test(n == 9, "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 3, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 6, "vector_capacity() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 3, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    vector_destroy(vector);
}

static void test_vector_free_strings(void)
{
    Vector vector = vector_create(1, DATATYPE_STRING, GDS_FREE_ON_DESTROY);
    if ( !vector ) {
        perror("couldn't create vector");
        exit(EXIT_FAILURE);
    }

    bool status;
    size_t sz;
    char * pc;

    sz = vector_length(vector);
    tests_log_test(sz == 1, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 1, "vector_length() gave wrong value");

    status = vector_append(vector, strdup("First string"));
    tests_log_test(status, "vector_append() failed");

    sz = vector_length(vector);
    tests_log_test(sz == 2, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 2, "vector_length() gave wrong value");

    status = vector_append(vector, strdup("Second string"));
    tests_log_test(status, "vector_append() failed");

    sz = vector_length(vector);
    tests_log_test(sz == 3, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 4, "vector_length() gave wrong value");

    status = vector_append(vector, strdup("Third string"));
    tests_log_test(status, "vector_append() failed");

    sz = vector_length(vector);
    tests_log_test(sz == 4, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 4, "vector_length() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 0, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    status = vector_element_at_index(vector, 0, &pc);
    tests_log_test(status, "vector_element_index() failed");
    tests_log_test(pc == NULL, "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 1, &pc);
    tests_log_test(status, "vector_element_index() failed");
    tests_log_test(!strcmp(pc, "First string"),
                   "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 2, &pc);
    tests_log_test(status, "vector_element_index() failed");
    tests_log_test(!strcmp(pc, "Second string"),
                   "vector_element_at_index() gave wrong value");

    status = vector_element_at_index(vector, 3, &pc);
    tests_log_test(status, "vector_element_index() failed");
    tests_log_test(!strcmp(pc, "Third string"),
                   "vector_element_at_index() gave wrong value");

    status = vector_delete_index(vector, 2);
    tests_log_test(status, "vector_delete_index() failed");

    status = vector_element_at_index(vector, 2, &pc);
    tests_log_test(status, "vector_element_index() failed");
    tests_log_test(!strcmp(pc, "Third string"),
                   "vector_element_at_index() gave wrong value");

    sz = vector_length(vector);
    tests_log_test(sz == 3, "vector_length() gave wrong value");

    sz = vector_capacity(vector);
    tests_log_test(sz == 4, "vector_length() gave wrong value");

    sz = vector_free_space(vector);
    tests_log_test(sz == 1, "vector_free_space() gave wrong value");

    status = vector_is_empty(vector);
    tests_log_test(!status, "vector_is_empty() gave wrong value");
    
    vector_destroy(vector);
}

static void test_vector_find(void)
{
    Vector vector = vector_create(1, DATATYPE_UNSIGNED_LONG_LONG,
                                  GDS_RESIZABLE);
    if ( !vector ) {
        perror("couldn't create vector");
        exit(EXIT_FAILURE);
    }

    vector_set_element_at_index(vector, 0, 10ULL);
    vector_append(vector, 20ULL);
    vector_append(vector, 40ULL);
    vector_append(vector, 30ULL);

    bool status;
    size_t index;

    status = vector_find(vector, &index, 10ULL);
    tests_log_test(status, "vector_find() failed to find element");
    tests_log_test(index == 0, "vector_find() gave wrong index");

    status = vector_find(vector, &index, 20ULL);
    tests_log_test(status, "vector_find() failed to find element");
    tests_log_test(index == 1, "vector_find() gave wrong index");

    status = vector_find(vector, &index, 40ULL);
    tests_log_test(status, "vector_find() failed to find element");
    tests_log_test(index == 2, "vector_find() gave wrong index");

    status = vector_find(vector, &index, 30ULL);
    tests_log_test(status, "vector_find() failed to find element");
    tests_log_test(index == 3, "vector_find() gave wrong index");

    status = vector_find(vector, &index, 50ULL);
    tests_log_test(!status, "vector_find() failed to find element");

    vector_destroy(vector);
}

void test_vector(void)
{
    test_vector_basic();
    test_vector_free_strings();
    test_vector_find();
}
