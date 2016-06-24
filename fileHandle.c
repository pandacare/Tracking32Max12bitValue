/**
 * @file fileHandle.c
 * @author Chengliu Li
 * @date 18 June 2016
 * @brief tracking 32 maximum values
 */
/*****************************************************
*Handle file operation i.e. data read/write
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "global.h"
#include "heapFunction.h"
#include "fileHandle.h"

#define DATA_SIZE_IN_BYTE 48           //buffer size when use memory super save mode i.e. 32*12/8 = 48 bytes

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

void passDataOutputFile(char*fileName, FILE* inputFile, uint8 heapIndex,long int filePostion, uint8 oddReadOffset){
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
			printf("filePosition before adjust is %ld\n",filePostion);
			filePostion = filePostion - oddReadOffset - DATA_SIZE_IN_BYTE;
			printf("filePosition is %ld\n",filePostion);
			printf("the position of stream before fseek is %ld\n", ftell(inputFile)); 
			if(fseek(inputFile,- oddReadOffset - DATA_SIZE_IN_BYTE,SEEK_END)){
				fprintf(stderr, "ERROR reading file 1 %s: %s", fileName, strerror(errno));
				return;
			}
			printf("filePosition after fseek is %ld\n",filePostion);
			printf("the position of stream after fseek is %ld\n", ftell(inputFile)); 
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
	/*close file */
	fclose(fp);
  /* open input file scuccessfully*/
  fprintf(stdout, "All data write to %s\n", fileName);   
  return;	
}

#ifdef MEMORY_SAVE_SUPER
		/**************************************************************************
	 *  Function: readIndexBuffer
	 *     NOTE:build heap out of random array, used for debug only
	 *  Args:N/A
	 *
	 *  Return: N/A 
	**************************************************************************/
	uint16 readIndexBuffer( uint8 i){ 
		/*  subtracted by 1 first when get in this function. due to heap definition*/
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
		/*  subtracted by 1 first when get in this function. due to heap definition*/
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
