/*	sort.c
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 2
*/
#include "sort.h"

void swap(void* a, void* b){
	int tmp=*(int*) a;
	*(int*) a=*(int*) b;
	*(int*) b=tmp;
	return;
}

int index_sequence(process** p_arr, int* index_arr){

	pid_t* tmp=(pid_t*) malloc(N*sizeof(pid_t));
	for(int i=0;i<N;i++){
		tmp[i]=p_arr[i]->pid;
		index_arr[i]=i;
	}

	int i,j;
	bool swapped;
	for(i=0;i<N-1;i++){
		swapped=false;
		for(j=0;j<N-i-1;j++){
			if(tmp[j]>tmp[j+1]){
				// https://ftp.gnu.org/old-gnu/Manuals/glibc-2.2.3/html_node/libc_554.html
				// int and pid_t are of the same size.
				swap(&tmp[j],&tmp[j+1]);
				swap(&index_arr[j],&index_arr[j+1]);
				swapped=true;
			}
		}
		if(swapped==false) break;
	}

	free(tmp);
	return 0;
}