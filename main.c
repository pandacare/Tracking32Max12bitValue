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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "global.h"
#include "fileHandle.h"
#include "heapFunction.h"
#include "main.h"

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
  /* while not the end of the file, get two 12bits data (3 BYTE)from the input file */
  while((fread(data.byteVal, sizeof(data.byteVal), 1, fp)) != 0){ 
		 heapHandle(FIRST_12BIT);
		 heapHandle(SECON_12BIT);
     printf("the position of stream is %ld\n", ftell(fp)); 
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
	uint8 oddReadOffset = (filePosition % 3);
  if(oddReadOffset){    
		heapHandle(FIRST_12BIT);
  }
  /*reorder the heap with heap sort*/
	heapsort();
	/*output everything required to the output file*/
  passDataOutputFile(argv[1],fp, heapIndex, filePosition, oddReadOffset);	
	/*close input file here*/
  fclose(fp);
  return 0;

}
