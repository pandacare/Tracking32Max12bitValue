#ifndef    MAIN_H_
#define    MAIN_H_
  //#define DEBUG                      // define to print debug info
	//#define MEMORY_SAVE_SUPER          //optional, define in command line during make, defaul no memory save
	#define MEMORY_SAVE                //optional, define in command line during make, defaul no memory save
	#ifdef  MEMORY_SAVE_SUPER
		#define MEMORY_SAVE
	#endif
	#define  ROOT              1         // Store fisrt value in heapArray[1]
	#define  HEAP_SIZE        32         // Heap size
	#define  LAST_DATA_SIZE   32         // Heap size
	#define  HALF_HEAP_SIZE   16         // Half heap size = HEAP_SIZE/2
	#define  HEAP_ARRAY_SIZE  33         // HEAP_SIZE + 1, the real array size
	#define  FIRST_12BIT       (uint16)(data.Bit4Val.fourBit2 << 8) + (data.Bit4Val.fourBit1 << 4) + data.Bit4Val.fourBit4 // bit shift to get meaningful value from IO, risky- 
	#define  SECON_12BIT       (uint16)(data.Bit4Val.fourBit3 << 8) + (data.Bit4Val.fourBit6 << 4) + data.Bit4Val.fourBit5 // -if MCU doesn't have multiple shitfing
#endif

