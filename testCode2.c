#include <stdio.h>
#include <stdlib.h>

	#include<stdio.h>
	void heapsort(int[],int);
	void heapify(int[],int);
	void adjust(int[],int);
	main() {
		int n,i;
    n =10;
    int a[10] = {3,4,7,2,2,4,8,6,4,5};
    
		//system("clear");
	// printf("\nEnter the limit:");
		// scanf("%d",&n);
	// printf("\nEnter the elements:");
	// for (i=0;i<n;i++)
		  // scanf("%d",&a[i]);
		heapsort(a,n);
		// printf("\nThe Sorted Elements Are:\n");
		for (i=0;i<n;i++)
		   printf("\t%d",a[i]);
}
 void heapsort(int a[],int n) {
		int i,t;
		heapify(a,n);
		for (i=n-1;i>0;i--) {
			 t = a[0];
			 a[0] = a[i];
			 a[i] = t;
			 adjust(a,i);
		 }
		printf(" the static test point value is %d\n", testPoint);
		testPoint++;
		printf(" the new static test point value is %d\n", testPoint);
	}
	void heapify(int a[],int n) {
		int k,i,j,item;
		for (k=1;k<n;k++) {
			item = a[k];
			i = k;
			j = (i-1)/2;
			while((i>0)&&(item>a[j])) {
				a[i] = a[j];
				i = j;
				j = (i-1)/2;
			}
			a[i] = item;
		}
	}
	void adjust(int a[],int n) {
		int i,j,item;
		j = 0;
		item = a[j];
		i = 2*j+1;
		while(i<=n-1) {
			if(i+1 <= n-1)
			   if(a[i] <a[i+1])
			    i++;
			if(item<a[i]) {
				a[j] = a[i];
				j = i;
				i = 2*j+1;
			} else
			   break;
		}
		a[j] = item;
	}
  

