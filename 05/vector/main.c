#include "vector.h"

int main(void){
	Vector* v=(Vector*) malloc(sizeof(Vector));
	if(vector_init(v,sizeof(int))==0){

		printf("\nSize=%d\n",v->size);
		printf("Capacity=%d\n",v->capacity);
		printf("isEmpty %d\n\n",is_empty(v));
		int value=0;
		for(int i=0;i<6;i++){
			vector_push_back(v,(void*)&value);
			value+=10;
		}
		int vout;
		vector_pop(v,(void*)&vout);
		printf("vout=%d\n\n",vout);
		int val;
		vector_remove(v,2);
		printf("\nSize=%d\n",v->size);
		printf("Capacity=%d\n\n",v->capacity);
		for(size_t i=0;i<=v->size-1;i++)
			if(!get_element(v,i,&val))
				printf("v[%ld]=%d\n",i,val);
	}
	vector_destroy(v);

	return 0;
}