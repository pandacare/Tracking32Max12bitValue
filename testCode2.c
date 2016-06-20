#include <stdio.h>
#include <stdlib.h>

	#include<stdio.h>
	void heapsort(void);
	void heapify(int);
	void adjust(int[],int);
	void buildHeap(void);
	// int a[33] = {0,60,4,7,40,9,23,7,
	            // 78,40,10,56,66,44,36,23,
							// 78,89,40,40,13,14,56,70,
							// 66,77,45,46,56,88,76,24,
							// 87};
								int a[33] = {0,60,4,7,40,9,23,7,
	            8,40,0,56,66,56,36,23,
							8,89,4,40,13,14,56,70,
						6,77,45,46,56,88,7,24,
							87};
	int heap[33] ;
	int output[32];
	int heapSize = 32;
	#define HEAPSIZE 10
	main() {
		int n,i;
    n =33;
	  buildHeap();
		for (i=1;i<n;i++)
		 printf("\t%d",a[i]);
	  heapsort();
		
	   printf("\n the sorted output is: \n");
	 		 for (i=0;i<32;i++)
		printf("\t%d",output[i]);
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
	int i;
	int j = 0;
	for(i = 32; i >= 1; i--){
		output[j] = a[1];
		a[1] = a[i];
		heapSize--;
		heapify(1);
		j++;
		
	}
}
void buildHeap(void){
	int i;
	for(i = 16; i > 0; i--){
		heapify(i);
	}
}
  
	void heapify(int n) {
		int temp = 0;
		int childIndex = n << 1;
		if(childIndex < heapSize){
			if(a[childIndex] > a[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
		if(childIndex > heapSize){
			return;
		}
		if(a[childIndex]< a[n] ){
			temp = a[childIndex];
			a[childIndex] = a[n];
			a[n] = temp;
			n = childIndex;
			heapify(n);
		}
    return;
	}
