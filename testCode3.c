




//reorder the heap by heap sort
#include<stdio.h>
void heapsort(int[],int);
void heapify(int[],int);
void adjust(int[],int);
main() {
	int i;
	int n =32;
		int a[33] = {0,60,4,7,40,9,23,7,
	            78,40,10,56,66,44,36,23,
							78,89,40,40,13,14,56,70,
							66,77,45,46,56,88,76,24,
							87};
	// system("clear");
	// printf("\nEnter the limit:");
	// scanf("%d",&n);
	// printf("\nEnter the elements:");
	// for (i=0;i<n;i++)
	  // scanf("%d",&a[i]);
	heapsort(a,n);
	printf("\nThe Sorted Elements Are:\n");
	for (i=0;i<n;i++)
	  printf("\t%d",a[i]);
	printf("\n");
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
