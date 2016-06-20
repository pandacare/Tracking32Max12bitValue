#include <stdio.h>
#include <stdlib.h>
#include "type.h"
	#define ROOT 1
	void heapsort(void);
	void heapify(uint8,uint8);
	void buildHeap(void);
	// int a[33] = {0,60,4,7,40,9,23,7,
	            // 78,40,10,56,66,44,36,23,
							// 78,89,40,40,13,14,56,70,
							// 66,77,45,46,56,88,76,24,
							// 87};
								int heapArray[33] = {0,60,4,7,40,9,23,7,
	            8,40,0,56,66,56,36,23,
							8,89,4,40,13,14,56,70,
						6,77,45,46,56,88,7,24,
							87};
	int heap[33] ;
	int output[32];

	
	#define HEAPSIZE 10
	main() {
		int n,i;
    n =33;
	  buildHeap();
		for (i=1;i<n;i++)
		 printf("\t%d",heapArray[i]);
	  heapsort();
		
	   printf("\n the sorted output is: \n");
	 		 for (i=1;i<n;i++)
		printf("\t%d",heapArray[i]);
	 printf("\n done \n");
		//system("clear");
	// printf("\nEnter the limit:");
		// scanf("%d",&n);
	// printf("\nEnter the elements:");
	// for (i=0;i<n;i++)
		  // scanf("%d",&a[i]);
		//heapsort(a,n);
		//heapify(a,1);
		// printf("\nThe Sorted Elements Are:\n");
	
}
void heapsort(void) {
	uint16 temp;
	uint8 heapifySize = 32;
	while(heapifySize >= 1){
		temp = heapArray[heapifySize];
		heapArray[heapifySize] = heapArray[ROOT]; // here should be replaced by real output file write
		heapArray[ROOT] = temp;
		heapifySize--;
		heapify(heapifySize, ROOT);
	}
}
void buildHeap(void){
	uint8 i;
	uint8 heapifySize = 32;
	for(i = 16; i > 0; i--){
		heapify(heapifySize,i);
	}
}
  
	void heapify(uint8 size, uint8 n) {
		uint16 temp = 0;
		uint8 childIndex = n << 1;
		if(childIndex < size){
			if(heapArray[childIndex] > heapArray[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
		if(childIndex > size){
			return;
		}
		if(heapArray[childIndex]< heapArray[n] ){
			temp = heapArray[childIndex];
			heapArray[childIndex] = heapArray[n];
			heapArray[n] = temp;
			n = childIndex;
			heapify(size,n);
		}
    return;
	}
