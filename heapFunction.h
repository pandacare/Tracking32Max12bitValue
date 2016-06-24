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
#ifndef HEAPFUNCTION_H_
#define HEAPFUNCTION_H_
	#include "type.h"
	void heapsort(void);
	void heapify(uint8,uint8);
	void buildHeap(void);
	void heapHandle(uint16 );
	void heapInsert(uint16 , uint8);
	void heapInsertRoot(uint16);
#endif