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
#include <string.h>
#include "type.h"
#include "global.h"
#include "fileHandle.h"
#include "heapFunction.h"

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
  //static uint8 heapIndex = ROOT;  make it global
	#ifndef MEMORY_SAVE
		/*first store val to last_32.lastDataArray*/
		lastDataArray[dataIndex.val++] = num;
	#endif
  /*if heap not full, insert new value from bottom*/
  if(!(heapIndex > HEAP_SIZE) ){
    heapInsert(num,heapIndex);
		#ifdef DEBUG
			printf("the heapIndex is %d\n",heapIndex);
		#endif
    heapIndex++;
		#ifdef DEBUG
			printf("the heapIndex is %d\n",heapIndex);
		#endif
  }	
	/*if heap is full and new input smaller than root, insert new value from root*/
	#ifdef MEMORY_SAVE_SUPER
		else if(num > readIndexBuffer(ROOT) ){ 	     
	#else
		else if(num > heapArray[ROOT] ){ 
	#endif
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

	#ifdef MEMORY_SAVE_SUPER
		uint16 readIndexBuffer_location;
		uint16 readIndexBuffer_parentIndex;
		writeIndexBuffer(location, num );	
		while(location > 1){
			parentIndex = location >>1;
			readIndexBuffer_location = readIndexBuffer(location);
			readIndexBuffer_parentIndex = readIndexBuffer(parentIndex);
			/*swap value in heap if break heap rule*/  
			if (readIndexBuffer_location < readIndexBuffer_parentIndex){
				temp = readIndexBuffer_parentIndex;
				writeIndexBuffer(parentIndex, readIndexBuffer_location );	
				writeIndexBuffer(location, temp );
				location = parentIndex;
			}
			else{
				break;
			} 
		}
	#else
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
	#endif
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
	#ifdef MEMORY_SAVE_SUPER
		uint16 readIndexBuffer_location;
	  uint16 readIndexBuffer_childIndex;
	  writeIndexBuffer(location, num );	            // assign new input to root
		while(location <= HALF_HEAP_SIZE){
			childIndex = location <<1;
			if(childIndex < HEAP_SIZE){
				if(readIndexBuffer(childIndex) > readIndexBuffer(childIndex + 1)){
					childIndex = childIndex + 1; 
				} 
			}
			readIndexBuffer_childIndex = readIndexBuffer(childIndex);
			readIndexBuffer_location = readIndexBuffer(location);
			/*swap value in heap*/    
			if (readIndexBuffer_childIndex < readIndexBuffer_location ){
				temp = readIndexBuffer_childIndex;
				writeIndexBuffer(childIndex, readIndexBuffer_location);
				writeIndexBuffer(location, temp);
				location = childIndex;
			}
			else{
				break;
			}
		}
	#else
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
	#endif
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
		#ifdef MEMORY_SAVE_SUPER
			temp = readIndexBuffer(heapifySize);
			writeIndexBuffer(heapifySize,readIndexBuffer(ROOT)); // here should be replaced by real output file write
			writeIndexBuffer(ROOT,temp);
		#else
			temp = heapArray[heapifySize];
			heapArray[heapifySize] = heapArray[ROOT]; // here should be replaced by real output file write
			heapArray[ROOT] = temp;
		#endif
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
		#ifdef MEMORY_SAVE_SUPER		
			uint16 readIndexBuffer_childIndex;
			uint16 readIndexBuffer_n;
			if(childIndex < size){
				if(readIndexBuffer(childIndex) > readIndexBuffer(childIndex + 1)){
					childIndex = childIndex + 1; 
				} 
			}
			
			/*quit heapify when go through the whole subtree*/
			if(childIndex > size){
				return;
			}
			readIndexBuffer_childIndex = readIndexBuffer(childIndex);
			readIndexBuffer_n = readIndexBuffer(n);
			if(readIndexBuffer_childIndex < readIndexBuffer_n ){
				temp = readIndexBuffer_childIndex;
				writeIndexBuffer(childIndex,readIndexBuffer_n );
				writeIndexBuffer(n,temp );
				n = childIndex;
				heapify(size,n);
			}
		#else
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
		#endif
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