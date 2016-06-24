#ifndef    TYPE_H_
#define    TYPE_H_
	typedef unsigned char       uint8;
	typedef unsigned short int  uint16;
	typedef unsigned long  int  uint32;

	typedef struct{
		uint8 first8 :8;
		uint8 first4 :4;
		uint8 secon4 :4;
		uint8 secon8 :8;
	} Bit24_t;

	typedef struct{
		uint8 fourBit1 :4;
		uint8 fourBit2 :4;
		uint8 fourBit3 :4;
		uint8 fourBit4 :4;
		uint8 fourBit5 :4;
		uint8 fourBit6 :4;
	} Bit4_t;

	typedef union  {
		Bit4_t Bit4Val;
		uint8 byteVal[3];
	}Data_t;

	typedef struct{
		uint8 val :5; 
	}dataIndex_t;
#endif

