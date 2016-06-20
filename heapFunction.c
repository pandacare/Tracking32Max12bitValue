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
#define  ROOT 1;          // store fisrt value in heapBuff[1]
const uint8  heapSize = 32;
const uint8  halfHeapSize = heapSize >> 1;
const uint8  heapBuffSize = heapSize + 1;
uint16 heapBuff[heapBuffSize];

main(){
  
}
/**************************************************************************
 *  heapHandle
 *     
 *  CLEAR, then UPDATE the global "RF_Int Status" flag
 *    If needed, Aux is read (Main INT & 0x01) and shifted into MSB
 *    both reads form the Status flag <AuxINT|MainINT>
 *  Update Log section of flux buf with values read.... Begin Log @ 512 (0x200) to 767 (0x2FF)
 *  Remove ALL interrupt bits we DON'T currently process....
 *  Args: N/A
 *
 *  Return: N/A - However, this function CLEARS, then UPDATES the global RF_IntStatus flag
**************************************************************************/
void heapHandle(uint16 num){
  static uint8 heapIndex = ROOT;  //initialized everytime when execute the .exe, need to be modified when in embedded environment
  /*if heap not full, insert new value from bottom*/
  if(!(heapIndex > heapSize) ){
    heapInsertBottom(num,heapIndex);
    heapIndex++;
  }
  /*if heap is full and new input smaller than root, insert new value from root*/
  else if(num < heapBuff[ROOT] ){      
    heapInsertRoot(uint16 num);
  }
}

/**************************************************************************
 *  heapInsert
 *     make sure store the maximum 32 data, but don't worry the order yet
 *  CLEAR, then UPDATE the global "RF_Int Status" flag
 *    If needed, Aux is read (Main INT & 0x01) and shifted into MSB
 *    both reads form the Status flag <AuxINT|MainINT>
 *  Update Log section of flux buf with values read.... Begin Log @ 512 (0x200) to 767 (0x2FF)
 *  Remove ALL interrupt bits we DON'T currently process....
 *  Args: N/A
 *
 *  Return: N/A - However, this function CLEARS, then UPDATES the global RF_IntStatus flag
**************************************************************************/
void heapInsertBottom(uint16 num, uint8 location ){
  uint16 temp;
  uint8  parentIndex;
  heapBuff[location] = num;
  while(location > 1){
    parentIndex = location >>1;
    /*swap value in heap*/  
    if (heapBuff[location] < heapBuff[parentIndex]){
			temp = heapBuff[parentIndex];
			heapBuff[parentIndex] = heapBuff[location];
			heapBuff[location] = temp;
			location = parentIndex;
    }
    else{
      break;
    }
    
  }
	return;
}
/**************************************************************************
 *  heapInsert
 *     make sure store the maximum 32 data, but don't worry the order yet
 *  CLEAR, then UPDATE the global "RF_Int Status" flag
 *    If needed, Aux is read (Main INT & 0x01) and shifted into MSB
 *    both reads form the Status flag <AuxINT|MainINT>
 *  Update Log section of flux buf with values read.... Begin Log @ 512 (0x200) to 767 (0x2FF)
 *  Remove ALL interrupt bits we DON'T currently process....
 *  Args: N/A
 *
 *  Return: N/A - However, this function CLEARS, then UPDATES the global RF_IntStatus flag
**************************************************************************/
void heapInsertRoot(uint16 num ){
  uint8 location = ROOT;
  uint16 temp;
  uint8  childIndex;
  heapBuff[location] = num;             // assign new input to root
  while(location <= halfHeapSize){
    childIndex = location <<1;
		if(childIndex < HeapSize){
			if(heapBuff[childIndex] > heapBuff[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
   
    /*swap value in heap*/    
    if (heapBuff[childIndex] < heapBuff[location]){
			temp = heapBuff[childIndex];
			heapBuff[childIndex] = heapBuff[location];
			heapBuff[location] = temp;
			location = childIndex;
    }
    else{
      break;
    }
    
  }
	return;
}

/**************************************************************************
 *  heapSort
 *     Make sure the heap is in sequence order 
 *  CLEAR, then UPDATE the global "RF_Int Status" flag
 *    If needed, Aux is read (Main INT & 0x01) and shifted into MSB
 *    both reads form the Status flag <AuxINT|MainINT>
 *  Update Log section of flux buf with values read.... Begin Log @ 512 (0x200) to 767 (0x2FF)
 *  Remove ALL interrupt bits we DON'T currently process....
 *  Args: N/A
 *
 *  Return: N/A - However, this function CLEARS, then UPDATES the global RF_IntStatus flag
**************************************************************************/
void heapSort(int location){
	
}

/**************************************************************************
 *  heapify
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
void heapify(uint8 location ){
  uint8 location = ROOT;
  uint16 temp;
  uint8  childIndex;
  heapBuff[location] = num;             // assign new input to root
  while(location <= halfHeapSize){
    childIndex = location <<1;
		if(childIndex < HeapSize){
			if(heapBuff[childIndex] > heapBuff[childIndex + 1]){
				childIndex = childIndex + 1; 
			} 
		}
   
    /*swap value in heap*/    
    if (heapBuff[childIndex] < heapBuff[location]){
			temp = heapBuff[childIndex];
			heapBuff[childIndex] = heapBuff[location];
			heapBuff[location] = temp;
			location = childIndex;
    }
    else{
      break;
    }
    
  }
	return;
}

