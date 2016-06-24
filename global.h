#ifndef GLOBAL_H_
#define GLOBAL_H_
#include "main.h"
	#ifdef MEMORY_SAVE_SUPER
		extern Bit24_t bit24_16[16];              // 48 bytes buffer to save heap in memory super save mode
	#endif
	extern Data_t data;                         // union to read out 3 bytes from IO, then auto transmit to two 12bits value
	extern dataIndex_t dataIndex;               //in no memory save mode, used during output data to output file
	#ifndef MEMORY_SAVE
		extern uint16 lastDataArray [LAST_DATA_SIZE] ;// store the last 32 data
	#endif
	#ifndef MEMORY_SAVE_SUPER
		extern uint16 heapArray[HEAP_ARRAY_SIZE] ;  // min heap, i.e. the smallest value is in heap[1], used when not in memory super sage mode
	#endif
		extern uint8 heapIndex;

#endif
