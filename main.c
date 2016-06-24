/**
 * @file main.c
 * @author Chengliu Li
 * @date 17 June 2016
 * @brief tracking 32 maximum values
 *
 *
 *
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#define MEMORY_SAVE_SUPER
#define MEMORY_SAVE
#ifdef  MEMORY_SAVE_SUPER
	#define MEMORY_SAVE
#endif
#define DATA_SIZE_IN_BYTE 48
#define  ROOT              1         // Store fisrt value in heapArray[1]
#define  HEAP_SIZE        32         // Heap size
#define  LAST_DATA_SIZE   32         // Heap size
#define  HALF_HEAP_SIZE   16         // Half heap size = HEAP_SIZE/2
#define  HEAP_ARRAY_SIZE  33         // HEAP_SIZE + 1, the real array size
#define  FIRST_12BIT       (uint16)(data.Bit4Val.fourBit2 << 8) + (data.Bit4Val.fourBit1 << 4) + data.Bit4Val.fourBit4
#define  SECON_12BIT       (uint16)(data.Bit4Val.fourBit3 << 8) + (data.Bit4Val.fourBit6 << 4) + data.Bit4Val.fourBit5
typedef unsigned short int uint16;
typedef unsigned  int      uint32;
typedef unsigned char      uint8;
#ifdef MEMORY_SAVE_SUPER
typedef struct{
  uint8 first8 :8;
  uint8 first4 :4;
  uint8 secon4 :4;
  uint8 secon8 :8;
} Bit24_t;
Bit24_t bit24_16[16];
uint16 readIndexBuffer( uint8 );
void writeIndexBuffer(uint8 , uint16);
#endif

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
Data_t data;
typedef struct{
	uint8 val :5; 
}dataIndex_t;
dataIndex_t dataIndex;
#ifndef MEMORY_SAVE
uint16 lastDataArray [LAST_DATA_SIZE] ;// store the last 32 data
#endif
#ifndef MEMORY_SAVE_SUPER
uint16 heapArray[HEAP_ARRAY_SIZE] ;// min heap, i.e. the smallest value is in heap[1]
#endif
uint8 heapIndex = ROOT;
void heapsort(void);
void heapify(uint8,uint8);
void buildHeap(void);
void heapHandle(uint16 );
void heapInsert(uint16 , uint8);
void heapInsertRoot(uint16);
FILE* openFile(int , char*);
void passDataOutputFile(char*, FILE*, uint8, long, uint8);

int main(int argc, char *argv[]){
  #ifdef MEMORY_SAVE_SUPER
	printf("super memory save mode\n");
	#else
		#ifdef MEMORY_SAVE
	printf(" memory save mode\n");
  #else
	printf(" no memory save mode\n");
	#endif
	#endif
  /**open input file*/
  FILE *fp = NULL;
  fp = openFile(argc, argv[1]);  
	if(fp == NULL){
		return -1;
	}
  int i = 1;
  /* while not the end of the file, get two 12bits data (3 BYTE)from the input file */
  while((fread(data.byteVal, sizeof(data.byteVal), 1, fp)) != 0){ 
		 heapHandle(FIRST_12BIT);
		 heapHandle(SECON_12BIT);
     printf("the position of stream is %d\n", ftell(fp)); 
     printf("the value of feof() is %d\n", feof(fp));
  }
  /*error during file reading*/
  if(!feof(fp)){ 
    fprintf(stderr, "ERROR reading file %s: %s", argv[1], strerror(errno));
    return(errno);
  }
  /*check current postion of the file*/
	long int filePosition = ftell(fp);
  if(filePosition == -1){ 
     fprintf(stderr, "ERROR checking file %s position: %s", argv[1], strerror(errno));
     return(errno);
  }
	/*check if have the odd 12bits data, have to use division here, risky!!*/
	uint8 oddReadOffset = 0;
  if(filePosition % 3){    
		heapHandle(FIRST_12BIT);
		oddReadOffset = 2;
  }
  /*reorder the heap with heap sort*/
	 heapsort();
	/*output everything required to the output file*/
  passDataOutputFile(argv[1],fp, heapIndex, filePosition, oddReadOffset);	
	/*close input file here*/
  fclose(fp);
  return 0;

}

/**************************************************************************
 *  Function: openFile
 *     NOTE: Handle file open, open bin file as input, read only
 *  Args: 
 *     argc:      Command line number when call main should be 2 
 *     *fileName: Input file name
 *
 *  Return: FILE pointer 
**************************************************************************/

FILE* openFile(int argc, char*fileName){
	FILE* fp = NULL;
	/*No input file typed */
  if(argc != 2){
    fprintf(stderr, "ERROR: Missing input file, please refer to readMe.txt");
    return(NULL);
  }
  /*Invalid input file */
  if((fp = fopen(fileName, "rb")) == NULL){   
    fprintf(stderr, "ERROR opening file %s: %s", fileName, strerror(errno));
    return(NULL);
  }
  /* open input file scuccessfully*/
  fprintf(stdout, "reading sensor data out of %s\n", fileName);   
  return fp;	
}


/**************************************************************************
 *  Function: passDataOutputFile
 *     NOTE: pass data to output file
 *  Args: 
 *     *fileName: Input file name, name will be changed to *.out to match
 *                the example format
 *     *inputFile: get the input file 
 *     filePostion: the position to start the last 32 bytes data
 *
 *  Return: N/A 
**************************************************************************/

void passDataOutputFile(char*fileName, FILE* inputFile, uint8 heapIndex,long filePostion, uint8 oddReadOffset){
	FILE* fp = NULL;
	/*adjust fileName to match the example*/
	int fileNameIndex = strlen(fileName);
	*(fileName + fileNameIndex - 1) = 't';
	*(fileName + fileNameIndex - 2) = 'u';
	*(fileName + fileNameIndex - 3) = 'o';
  /*Invalid file */
  if((fp = fopen(fileName, "w")) == NULL){   
    fprintf(stderr, "ERROR opening file %s: %s", fileName, strerror(errno));
    return;
  }
	/*output it to the output file*/
	/*write heapsort data*/
  fprintf(fp, "--Sorted Max 32 Values--\n");
	uint8 i;
	for(i = heapIndex - 1; i > 0; i--){
		#ifdef MEMORY_SAVE_SUPER
			fprintf(fp,"%d\n", readIndexBuffer(i) );
		#else
			fprintf(fp,"%d\n", heapArray[i] );
	  #endif
	}
	/*write the last 32 to the output file*/
	fprintf(fp, "--Last 32 Valeus--\n");
	fprintf(fp,"the heapIndex is %d\n",heapIndex);
	if(heapIndex > HEAP_SIZE){
		#ifdef MEMORY_SAVE
		printf("filePosition before adjust is %d\n",filePostion);
			filePostion = filePostion - oddReadOffset - DATA_SIZE_IN_BYTE;
			printf("filePosition is %d\n",filePostion);
			printf("the position of stream before fseek is %d\n", ftell(inputFile)); 
			if(fseek(inputFile,- oddReadOffset - DATA_SIZE_IN_BYTE,SEEK_END)){
				fprintf(stderr, "ERROR reading file 1 %s: %s", fileName, strerror(errno));
				return;
			}
			printf("filePosition after fseek is %d\n",filePostion);
			printf("the position of stream after fseek is %d\n", ftell(inputFile)); 
			/*in case of odd number of 12bit data,start output from second 12bit value of first loop*/ 
			if(oddReadOffset){
				for(i = 0; i < 16; i++){
					if(!fread(data.byteVal, sizeof(data.byteVal), 1, inputFile)){
						fprintf(stderr, "ERROR reading file 2 %s: %s", fileName, strerror(errno));
						return;
					}
					/*start output from second 12bit value of first loop*/ 
					if(!i){
						fprintf(fp,"%d\n",SECON_12BIT);
					}
					else{
						fprintf(fp,"%d\n",FIRST_12BIT);
						fprintf(fp,"%d\n",SECON_12BIT);
					}
			
				}		
				/*output the last odd 12bit*/
				fread(data.byteVal, sizeof(data.byteVal), 1, inputFile);
				fprintf(fp,"%d\n",FIRST_12BIT); 
			}
			/*in case of no odd number of 12bit data,start output from first 12bit value of first loop*/ 
			else{	
				for(i = 0; i < 16; i++){
					if(!fread(data.byteVal, sizeof(data.byteVal), 1, inputFile)){
						fprintf(stderr, "ERROR reading file 3 %s: %s", fileName, strerror(errno));
						return;
					}
					fprintf(fp,"%d\n",FIRST_12BIT);
			    fprintf(fp,"%d\n",SECON_12BIT);
				}
			}
    #else			
		for(i = 0; i < LAST_DATA_SIZE; i++){
			printf("the number is %d\n", i );
			fprintf(fp,"%d\n",lastDataArray[dataIndex.val++]);
		}
    #endif
	}
	else{
		#ifdef MEMORY_SAVE
			if(fseek(inputFile,0,SEEK_SET)){
				fprintf(stderr, "ERROR reading file 4 %s: %s", fileName, strerror(errno));
				return;
			}
			while((fread(data.byteVal, sizeof(data.byteVal), 1, inputFile)) != 0){ 
				fprintf(fp,"%d\n",FIRST_12BIT);
			  fprintf(fp,"%d\n",SECON_12BIT);
			}
			/*error during file reading*/
			if(!feof(inputFile)){ 
				fprintf(stderr, "ERROR reading file 5 %s: %s", fileName, strerror(errno));
				return;
			}
			/*in case of no odd number of 12bit data,output the last one*/
			if(oddReadOffset){
				fprintf(fp,"%d\n",FIRST_12BIT);
			}	
		#else	
		for(i = 0; i < dataIndex.val; i++){
			fprintf(fp,"%d\n",lastDataArray[i]);
		}
		#endif
	}
	//use fseek to locate the position of the input file with refer to end of file 
	//get one out and put it to the output
	/*close file */
	fclose(fp);
  /* open input file scuccessfully*/
  fprintf(stdout, "All data write to %s\n", fileName);   
  return;	
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
  //static uint8 heapIndex = ROOT;  make it global
	#ifndef MEMORY_SAVE
	/*first store val to last_32.lastDataArray*/
	lastDataArray[dataIndex.val++] = num;
	#endif
  /*if heap not full, insert new value from bottom*/
  if(!(heapIndex > HEAP_SIZE) ){
    heapInsert(num,heapIndex);
		printf("the heapIndex is %d\n",heapIndex);
    heapIndex++;
		printf("the heapIndex is %d\n",heapIndex);
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
		uint16 readIndexBuffer_childIndex;
		uint16 readIndexBuffer_n;
		#ifdef MEMORY_SAVE_SUPER
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
#ifdef MEMORY_SAVE_SUPER
	/**************************************************************************
 *  Function: readIndexBuffer
 *     NOTE:build heap out of random array, used for debug only
 *  Args:N/A
 *
 *  Return: N/A 
**************************************************************************/
uint16 readIndexBuffer( uint8 i){ // i is subtracted by 1 first when get in this function. due to heap definition, and also right shift one bit
     i = i - 1;
		 /*read second index*/
     if(i & 1){
			 i >>= 1;
       return (uint16)(bit24_16[i]).secon4 +(((bit24_16[i]).secon8 )<<4);
     }
		 /*read first index*/
     else{
       i >>= 1;
			 return (uint16)(bit24_16[i]).first8 +(((bit24_16[i]).first4 )<<8);
     }
       
}
	/**************************************************************************
 *  Function: writeIndexBuffer
 *     NOTE:build heap out of random array, used for debug only
 *  Args:N/A
 *
 *  Return: N/A 
**************************************************************************/
void writeIndexBuffer(uint8 i, uint16 val){
	i = i - 1;
	/*read second index*/
  if(i & 1){
    i >>= 1;
    (bit24_16[i]).secon4 = val;
    (bit24_16[i]).secon8 = val >> 4;
  }
	/*read first index*/
  else{
    i >>= 1;
   (bit24_16[i]).first8 = val;
   (bit24_16[i]).first4 = val >> 8;
  }
}
#endif

