#ifndef    FILE_HANDLE_H_
#define    FILE_HANDLE_H_
	FILE* openFile(int, char*);
	void passDataOutputFile(char*, FILE* , uint8,long int, uint8);
	#ifdef MEMORY_SAVE_SUPER
		uint16 readIndexBuffer( uint8 );   // read data out of 48 bytes buffer in memory super save mode 
		void writeIndexBuffer(uint8 , uint16); // write data into 48 bytes buffer in memory super save mode
  #endif	
#endif

