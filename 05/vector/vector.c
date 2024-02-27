#include "vector.h"

int vector_init(Vector* vec, int elemSize){
	if(vec==NULL)
		return -1;

	// allocate memory for the array
	vec->capacity=INITIAL_CAPACITY;
	vec->elemSize=elemSize;
	vec->data=malloc(vec->capacity*elemSize);

	if(vec->data==NULL){
		perror(strerror(errno));
		printf("Aborting...\n");
		return -1;
	}

	vec->size=0; //empty vector
	return 0;
}

void vector_destroy(Vector* vec){
	if(vec!=NULL){
		free(vec->data);
		vec->data=NULL;
		vec->size=0;
		vec->capacity=0;
		vec->elemSize=0;
		return;
	}
}

int vector_push_back(Vector* vec, void* value){

	if(vec==NULL || vec->data==NULL) {
		NULL_MSG
		return -1;
	}

	get_size(vec);
	if(vec->capacity<=0){
		fprintf(stderr, "There is no vector!\n");
		printf("Aborting");
		return -1;
	}
	if(!is_full(vec)){
		size_t offset=(size_t) vec->size * vec->elemSize;
		memcpy(vec->data + offset, value, vec->elemSize);
		vec->size+=1;
		return 0;
	}else{
		if(extend_mem(vec)==0){
			size_t offset=(size_t) vec->size * vec->elemSize;
			memcpy(vec->data + offset, value, vec->elemSize);
			vec->size+=1;
		}
		return 0;
	}

	fprintf(stderr, "Unknown error.\n");
	printf("Aborting...\n");
	return -1;
}

int vector_pop(Vector* vec, void* out){

	if(vec==NULL || vec->data==NULL) {
		NULL_MSG
		return -1;
	}
	// store in `out` the element that was popped
	size_t offset=(size_t) (vec->size-1)*vec->elemSize;
	memcpy(out,vec->data+offset,vec->elemSize);
	vec->size-=1;
	return 0;
}

int vector_remove(Vector* vec, int index){

	if(vec==NULL || vec->data==NULL) {
		NULL_MSG
		return -1;
	}

	if(index<0 || index>=vec->size){
		fprintf(stderr,"Index out of bounds. Provide an index that is greater than or equal to zero and less than %d.\n",vec->size);
		return -1;
	}

	size_t nElem=(size_t)vec->size-index-1;
	void* tmp_data=malloc(vec->elemSize*nElem);

	if(tmp_data==NULL){
		fprintf(stderr,"Failed to remove element.\n");
		return -1;
	}

	vec->size-=1;
	for(int i=index;i<=vec->size-1;i++){
		size_t d_offset=i*vec->elemSize;
		size_t s_offset=(i+1)*vec->elemSize;
		memcpy(vec->data+d_offset,vec->data+s_offset,vec->elemSize);
	}

	return 0;
}

/* ╭───────────────────────╮
   │ ┏━━━━━━━━━━━━━━━━━━━┓ │
   │ ┃AUXILIARY FUNCTIONS┃ │
   │ ┗━━━━━━━━━━━━━━━━━━━┛ │
   ╰───────────────────────╯ */

size_t get_size(Vector* v){
	if(v==NULL || v->data==NULL) {
		NULL_MSG
		return -1;
	}

	return v->size;
}

bool is_empty(Vector* v){
	if(v == NULL || v->data == NULL) {
		NULL_MSG
		exit(EXIT_FAILURE);
	}

	if(v->size==0)
		return true;

	return false;
}

bool is_full(Vector* v){
	if(v == NULL || v->data == NULL) {
		NULL_MSG
		exit(EXIT_FAILURE);
	}

	if(v->size==v->capacity)
		return true;

	return false;
}

int extend_mem(Vector* v){
	if(v == NULL || v->data == NULL) {
		NULL_MSG
		return -1;
	}

	if(is_full(v)==false || is_empty(v)==true)
		return 0; // no need to extend the vector

	size_t new_capacity=2*(v->capacity);

	void* address=realloc(v->data,new_capacity*(v->elemSize));

	if(address==NULL){
		perror(strerror(errno));
		fprintf(stderr, "Unable to extend the memory of the vector.\n");
		return -1;
	}
	v->data=address; // update the address of the array
	v->capacity=new_capacity; // update the maximum capacity of the vector
	return 0;
}

int get_element(Vector* v, size_t index, void* val){

	if(v==NULL || v->data==NULL || is_empty(v)) {
		NULL_MSG
		return -1;
	}

	if(index<=v->size && index>=0){
		memcpy(val,v->data+index*v->elemSize, v->elemSize);
		return 0;
	}
	else{
		fprintf(stderr,"Index out of bounds! Provide an index less than or equal to %d.\n",v->size-1);
		return -1;
	}
}