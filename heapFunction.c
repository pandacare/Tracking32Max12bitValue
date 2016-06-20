/**
 * @file heapFunction.c
 * @author Chengliu Li
 * @date 19 June 2016
 * @brief heap feature
 *
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#define  ROOT              1         // Store fisrt value in heapArray[1]
#define  HEAP_SIZE        32         // Heap size
#define  HALF_HEAP_SIZE   16         // Half heap size = HEAP_SIZE/2
#define  HEAP_ARRAY_SIZE  33         // HEAP_SIZE + 1, the real array size

uint16 heapArray[HEAP_ARRAY_SIZE] = {0,60,4,7,40,9,23,7,
                                     8,40,0,56,66,56,36,23,
																	   8,89,4,40,13,14,56,70,
																	   6,77,45,46,56,88,7,24,
																	   87};
// uint16 heapArray[HEAP_ARRAY_SIZE] = {0,60,4,7,40,9,23,7,
// 78,40,10,56,66,44,36,23,
// 78,89,40,40,13,14,56,70,
// 66,77,45,46,56,88,76,24,
// 87};
void heapsort(void);
void heapify(uint8,uint8);
void buildHeap(void);
void heapHandle(uint16 );
void heapInsert(uint16 , uint8);
void heapInsertRoot(uint16);



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
	
}
/**************************************************************************
 *  Function: heapHandle
 *     NOTE: Check the heap array occupied space and call function accordingly 
 *     Make sure store the maximum 32 data, but don't worry the final order yet.
 *
 *  Args: 
 *     num:      New input data 
 *
 *  Return: N/A
**************************************************************************/
void heapHandle(uint16 num){
	/*initialized everytime when execute the .exe, need to be modified when in embedded environment*/
  static uint8 heapIndex = ROOT;  
  /*if heap not full, insert new value from bottom*/
  if(!(heapIndex > HEAP_SIZE) ){
    heapInsert(num,heapIndex);
    heapIndex++;
  }
  /*if heap is full and new input smaller than root, insert new value from root*/
  else if(num < heapArray[ROOT] ){      
    heapInsertRoot(num);
  }
}

/**************************************************************************
 *  Function: heapInsert
 *     NOTE: Call if head array is not full. Make sure store the maximum 
 *     32 data, but don't worry the final order yet.
 *
 *  Args: 
 *     num:      New input data 
 *     location: Indicate the place to insert the new input data
 *
 *  Return: N/A
**************************************************************************/
void heapInsert(uint16 num, uint8 location ){
  uint16 temp;
  uint8  parentIndex;
  heapArray[location] = num;
  while(location > 1){
    parentIndex = location >>1;
    /*swap value in heap if break heap rule*/  
    if (heapArray[location] < heapArray[parentIndex]){
			temp = heapArray[parentIndex];
			heapArray[parentIndex] = heapArray[location];
			heapArray[location] = temp;
			location = parentIndex;
    }
    else{
      break;
    } 
  }
	return;
}
/**************************************************************************
 *  Function: heapInsert
 *     NOTE: make sure store the maximum 32 data, but don't worry the final 
 *     order yet
 *
 *  Args: 
 *     num: 
 *
 *  Return: N/A
**************************************************************************/
void heapInsertRoot(uint16 num ){
  uint8 location = ROOT;
  uint16 temp;
  uint8  childIndex;
  heapArray[location] = num;             // assign new input to root
  while(location <= HALF_HEAP_SIZE){
    childIndex = location <<1;
		if(childIndex < HEAP_SIZE){
			if(heapArray[childIndex] > heapArray[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
   
    /*swap value in heap*/    
    if (heapArray[childIndex] < heapArray[location]){
			temp = heapArray[childIndex];
			heapArray[childIndex] = heapArray[location];
			heapArray[location] = temp;
			location = childIndex;
    }
    else{
      break;
    }
    
  }
	return;
}

/**************************************************************************
 *  Function: heapSort
 *     Note: sort heap array in order as requested. Could save some time if
 *           put the output function here
 *  Args: N/A
 *
 *  Return: N/A
**************************************************************************/
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

/**************************************************************************
 *  Function: heapify
 *     NOTE:N/A
 *  Args: 
 *     size: Subsize of the heap array to be heapified (i.e. the last data 
 *           in heap that is included in heapify handling)		       
 *		 n:    root node of the subtree in heap array to be heapified
 *
 *  Return: N/A 
**************************************************************************/
	void heapify(uint8 size, uint8 n) {
		uint16 temp = 0;
		uint8 childIndex = n << 1;
		if(childIndex < size){
			if(heapArray[childIndex] > heapArray[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
		/*quit heapify when go through the whole subtree*/
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
	
	/**************************************************************************
 *  Function: buildHeap
 *     NOTE:build heap out of random array, used for debug only
 *  Args:N/A
 *
 *  Return: N/A 
**************************************************************************/
	void buildHeap(void){
	uint8 i;
	uint8 heapifySize = 32;
	for(i = 16; i > 0; i--){
		heapify(heapifySize,i);
	}
}
