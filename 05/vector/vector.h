/* vector/vector.h
 *
 * Kapetanios Antonios 10417
 * January 2024
 *
 *
 * 049 - OS
 * hw assignment 5
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <errno.h>

#define INITIAL_CAPACITY 4
#define NULL_MSG fprintf(stderr,"The vector has not been initialized properly.\n");

/* Dynamic size array similar to C++'s `std::vector`.
 * The elements are stored contiguously. */
typedef struct Vector{
	void* data;
	int size;
	int capacity;
	int elemSize;
}Vector;

/* Constructs a Vector struct `v`.
 * Returns 0 upon success
 * and -1 upon failure. */
int vector_init(Vector* vec, int elemSize);

/* Destroys a Vector struct `vec`. */
void vector_destroy(Vector* vec);

/* Appends the given element
 * `value` to the end of the
 * Vector `vec`. Returns 0 upon
 * success and -1 upon failure. */
int vector_push_back(Vector* vec, void* value);

/* Removes the last element of the
 * Vector `vec`. Its value is stored
 * in `out`. Returns 0 upon success
 * and -1 upon failure. */
int vector_pop(Vector* vec, void* out);

/* Erases the element of the `index`-th entry
 * of Vector `vec`. Returns 0 upon success
 * and -1 upon failure. */
int vector_remove(Vector* vec, int index);


/* ╭───────────────────────╮
   │ ┏━━━━━━━━━━━━━━━━━━━┓ │
   │ ┃AUXILIARY FUNCTIONS┃ │
   │ ┗━━━━━━━━━━━━━━━━━━━┛ │
   ╰───────────────────────╯ */

/* Returns the number of elements
 * of the array of `v`. */
size_t get_size(Vector* v);

/* Checks if `v` is empty. */
bool is_empty(Vector* v);

/* Checks if `v` is full. */
bool is_full(Vector* v);

/* When `v` is full, `extend_mem` allocates
 * additional memory. The new size of
 * `v->array` is `2*max_size`. If successful
 * or if there is no need to increase the
 * capacity of `v` the function returns 0.
 * If there is no available space to perform
 * the capacity increase, it returns -1. */
int extend_mem(Vector* v);

/* Returns the element of the vector stored
 * at `index` through `val`. If the vector is empty
 * the return code of the function is -1. If
 * successful the return code is 0. */
int get_element(Vector* v, size_t index, void* val);

#endif