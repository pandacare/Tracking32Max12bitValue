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
		// for (i=n-1;i>0;i--) {
			// t = a[0];
			// a[0] = a[i];
			// a[i] = t;
			// adjust(a,i);
		// }
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
  
  
  /**************************************************************************
 * ReadData
 *     NOTE: At PUR, Int regs are 0'd   p. 34-42
 *  CLEAR, then UPDATE the global "RF_Int Status" flag
 *    If needed, Aux is read (Main INT & 0x01) and shifted into MSB
 *    both reads form the Status flag <AuxINT|MainINT>
 *  Update Log section of flux buf with values read.... Begin Log @ 512 (0x200) to 767 (0x2FF)
 *  Remove ALL interrupt bits we DON'T currently process....
 *  Args: N/A
 *
 *  Return: N/A - However, this function CLEARS, then UPDATES the global RF_IntStatus flag
**************************************************************************/

uint16 readIndexBuffer( uint8 i){ // i is subtracted by 1 before pass to this function. due to heap definition, and also right shift one bit
     if(i & 1){
       i >>= 1;
       return (uint16)(bit24_16[i]).secon4 +(((bit24_16[i]).secon8 )<<4);
     }
     else{
       i >>= 1;
       return (uint16)(bit24_16[i]).first8 +(((bit24_16[i]).first4 )<<8);
     }
       
}

/**************************************************************************
 * WriteData
 *     NOTE: At PUR, Int regs are 0'd   p. 34-42
 *  CLEAR, then UPDATE the global "RF_Int Status" flag
 *    If needed, Aux is read (Main INT & 0x01) and shifted into MSB
 *    both reads form the Status flag <AuxINT|MainINT>
 *  Update Log section of flux buf with values read.... Begin Log @ 512 (0x200) to 767 (0x2FF)
 *  Remove ALL interrupt bits we DON'T currently process....
 *  Args: N/A
 *
 *  Return: N/A - However, this function CLEARS, then UPDATES the global RF_IntStatus flag
**************************************************************************/

void writeIndexBuffer(uint8 i, uint16 val){
  if(i & 1){
    i >>= 1;
    (bit24_16[i]).secon4 = val;
    (bit24_16[i]).secon8 = val >> 4;
  }
  else{
    i >>= 1;
   (bit24_16[i]).first8 = val;
   (bit24_16[i]).first4 = val >> 8;
  }
}
