#include <stdio.h>
#include <stdlib.h>

	#include<stdio.h>
	void heapsort(void);
	void heapify(int[],int);
	void adjust(int[],int);
	void buildHeap(void);
	int a[11] = {0,60,4,7,40,9,23,7,
	            78,40,10};
	int heap[33] ;
	int output[32];
	int heapSize = 10;
	#define HEAPSIZE 10
	main() {
		int n,i;
    n =33;
		heapify(a,1);
    //buildHeap();
		for (i=1;i<n;i++)
		 printf("\t%d",a[i]);
	  //heapsort();
		
	  // printf("\n the sorted output is: \n");
	 		// for (i=0;i<32;i++)
		 // printf("\t%d",output[i]);
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
		heapify(a,1);
		
	}
}
void buildHeap(void){
	int i;
	for(i = 16; i > 0; i--){
		heapify(a,i);
	}
}
  
	void heapify(int a[],int n) {
		int temp = 0;
		int childIndex = n << 1;
		if(childIndex < heapSize){
			if(a[childIndex] > a[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
		if(a[childIndex]< a[n] ){
			temp = a[childIndex];
			a[childIndex] = a[n];
			a[n] = temp;
			n = childIndex;
			heapify(a,n);
		}

	}
