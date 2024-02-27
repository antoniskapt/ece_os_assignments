/*	sort.h
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 3
*/
#ifndef SORT_H
#define SORT_H

#include <stdbool.h>

#include "c_proc.h"

/*	Swaps two elements whose size is the same as the size of int. */
void swap(void* a, void* b);

/*	A modified version of bubble sort. Returns __index_arr__ that represents the order to access elements in __p_arr__ in ascending order of __pid__. */
int index_sequence(process** p_arr, int* index_arr);

#endif
