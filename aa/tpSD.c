#include <stdlib.h>
#include <stdio.h>

/* Basic heap macros */
#define h_parent(i) (i/2)
#define h_left(i) (2*i)
#define h_right(i) (2*i+1)

void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

typedef struct {
	int *data;
	int length; //length of data
	int size;
} Heap;

/**
	Reading and writing data
 */
void read_data( FILE *datain, int **dataout, int *n, int *k ) {
	int *data;

	fscanf(datain, "%d", n);
	fscanf(datain, "%d", k);
	*dataout = (int *)malloc( (*n) * sizeof(int) );
	data=*dataout;

	for ( int i=0; i< *n; ++i, ++data )
		fscanf( datain, "%d", data );
}

void print_data(int *tableau, int taille) {
    for( int i=0; i<taille; ++i)
		printf( "%d ", tableau[i] );
	printf("\n");
}

void print_data_decrease(int *data, int n){
	for( int i=n-1; i>=0; --i)
		printf( "%d ", data[i] );
	printf("\n");
}

/* écrire une fonction qui traite un tableau*/
void bubble_sort_k(int *data, int n, int k){
	for(int j=0; j < k; ++j){
		for(int i = 0; i < n-1; ++i){
			if( data[i] > data[i+1] )
				swap(data + i, data + i + 1);
		}
	}
}

void heap_percolateUp(Heap *heap, int x){
	int i = x;
	int j = h_parent(i);
	while(j > 0 && heap->data[j] < heap->data[i]){
		swap(heap->data+i, heap->data+j);
		i = j;
		j = h_parent(i);
	}
}

void heap_add(Heap *heap, int e){
	if(heap->size < heap->length){
		heap->size += 1;
		heap->data[heap->size] = e;
		heap_percolateUp(heap, heap->size);
	}
}

void heap_percolateDown(Heap *heap, int i){
	int l = h_left(i);
	int r = h_right(i);

	int m = ((l < heap->size) && (heap->data[i] < heap->data[l])) ? l : i;

	if((r < heap->size) && (heap->data[m] < heap->data[r])) m = r;

	if( m != i ){
		swap(heap->data+i, heap->data+m);
		heap_percolateDown(heap, m);
	}
}

void heap_buildHeap(Heap *heap){
	for( int i = (heap->length-1)/2; i >= 0; --i)
		heap_percolateDown(heap, i);
}

int heap_remove(Heap *heap){
	int m = heap->data[0];
	heap->data[0] = heap->data[heap->size-1];
	heap->size -= 1;
	heap_percolateDown(heap, 0);
	return m;
}

void print_greater_k_heap(int *data, int n, int k){
	int *res = (int*) malloc(k*sizeof(int));
	Heap heap = {data, n, n};
	heap_buildHeap(&heap);
	for (int i = 0; i < k; ++i)
		res[i] = heap_remove(&heap);
	print_data(res, k);
	free(res);
}

void print_greater_k_heap_add(int *data, int n, int k){
	int *heap_data = (int*) malloc((n+5)*sizeof(int));
	Heap heap = {heap_data, n+5, 0};
	for(int i = 0; i < n; ++i){
		heap_add(&heap, data[i]);
	}
	for(int i = 0; i < k; ++i){
		//TODO
	}
}

void print_greater_k(int *data, int n, int k, int method){
	switch(method){
		case 1 :
			printf("\nMethod 1 : bubble sort\n");
			bubble_sort_k(data, n, k);
			print_data_decrease(data+(n-k), k);
			break;
		case 2 :
			printf("\nMethod 2 : binary heap\n");
			print_greater_k_heap(data, n, k);
			break;
		default :
			printf("Unknow method\n");
	}
}

int main( int argc, char **argv ) {
	int *data;
	int n, k;
	FILE *f_in;

	if ( argc > 1 )
		f_in = fopen(argv[1], "r");
	else
		f_in = stdin;

	/* lecture des donnees */
	read_data( f_in, &data, &n, &k );

	/* affichage du tableau lu */
	if(n < 20) print_data(data,n);

	/* utiliser une fonction qui modifie data*/

	/* output result. */
	//print_greater_k(data, n, k, 1);
    print_greater_k(data, n, k, 2);


	 free(data);
	return 0;
}
