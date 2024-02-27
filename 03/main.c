/*	main.c
*
*	Kapetanios Antonios 10417
*	December 2023
*
*	049 - OS
*	hw assignment 3
*/
#include <sys/mman.h>
#include <fcntl.h>

#include "c_proc.h"
#include "sort.h"

#define SHARED_NAME "/shared_memory"

int main(void){

/* ───────────────────── CREATING AND HANDLING SHARED MEMORY ─────────────────────
*
*	RELATED DOCUMENTATION:
*	+	POSIX
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_08_03_02
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/shm_open.html
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/ftruncate.html
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/shm_unlink.html
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/mmap.html
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/mprotect.html
*		-	https://pubs.opengroup.org/onlinepubs/9699919799/functions/munmap.html
*	+	GNU	
*		-	https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html#index-shm_005fopen
*		-	https://www.gnu.org/software/libc/manual/html_node/File-Size.html#index-ftruncate
*		-	https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html#index-shm_005funlink
*		-	https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html#index-mmap
*		-	https://www.gnu.org/software/libc/manual/html_node/Memory-Protection.html
*		-	https://www.gnu.org/software/libc/manual/html_node/Memory_002dmapped-I_002fO.html#index-munmap
*/
	// Create shared memory
	int s_mem_file_descriptor;
	s_mem_file_descriptor=shm_open(SHARED_NAME,O_CREAT|O_RDWR,0666);
	if(s_mem_file_descriptor==-1){
		perror(strerror(errno));
		return errno;
	}

	// Set the size of the shared memory object
	int res=ftruncate(s_mem_file_descriptor,N*sizeof(process));
	if (res==-1){
		perror(strerror(errno));
		close(s_mem_file_descriptor);
		shm_unlink(SHARED_NAME);
		return errno;
	}

	// Map the shared memory object into the address space
	process* shared_mem_space;
	shared_mem_space=(process*) mmap(NULL,N*sizeof(process),PROT_READ|PROT_WRITE,MAP_SHARED,s_mem_file_descriptor,0);
	if(shared_mem_space==MAP_FAILED) {
		perror(strerror(errno));
		close(s_mem_file_descriptor);
		shm_unlink(SHARED_NAME);
		return errno;
	}
	
	// array of pointers to processes
	process** children=(process**) malloc(N*sizeof(process*));
	for(int i=0;i<N;i++)
		children[i]=&shared_mem_space[i];

// ───────────────────── CREATING AND HANDLING NEW PROCESSES ─────────────────────
	create_processes(children);

	int* index_arr=(int*) malloc(N*sizeof(int));
	index_sequence(children,index_arr);

	printf("────────────────────────────────────────────\n");
	for(int i=0;i<N;i++){
		int j=index_arr[i];
		printf("%s",children[j]->msg);
	}

// ───────────────────── CLEANUP ─────────────────────
	if(munmap(shared_mem_space,N*sizeof(process))==-1){
		perror(strerror(errno));
		return errno;
	}

	if(close(s_mem_file_descriptor)==-1){
		perror(strerror(errno));
		return errno;
	}
	
	free(children);
	return 0;
}
