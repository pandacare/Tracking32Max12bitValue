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
int heapArray[33] =  {0,60,4,7,40,9,23,7,
                                     8,40,0,56,66,56,36,23,
																	   8,89,4,40,13,14,56,70,
																	   6,77,45,46,56,88,7,24,
																	   87};// min heap, i.e. the smallest value is in heap[1]
int heapSize = 0;
typedef struct {
  unsigned char byteValue [3];
}threeByteForm_t;
threeByteForm_t threeByteForm;

void heapFunction(int element){
 //no return for now 
  
}
FILE* openFile(int , char*);
void passDataOutputFile(char*, FILE*, long);
int main(int argc, char *argv[]){
  /**open input file*/
  FILE *fp = NULL;
  fp = openFile(argc, argv[1]);  
	if(fp == NULL){
		return -1;
	}
  int i = 0;
  /* while not the end of the file, get two 12bits data from the input file */
  while((fread(&threeByteForm, sizeof(threeByteForm), 1, fp)) != 0){   
     	// see if first value can be put into the 32 heap array?
  		//check if the heap array is full?
   			// in not full condition
     				//insert the value to heap array
  			// in full condition
    				//check if the value is bigger than heapArray[1]
       					//if the value is bigger
          						//replace heap[1] with the new element

	// see if second value can be put into the 32 heap array?
  		//check if the heap array is full?
   			// in not full condition
     				//insert the value to heap array
  			// in full condition
    				//check if the value is bigger than heapArray[1]
       					//if the value is bigger
          						//replace heap[1] with the new element
     printf("the %d th value is %#06x\n", i, threeByteForm);
     printf("the position of stream is %d\n", ftell(fp)); 
     printf("the value of feof() is %d\n", feof(fp));
     printf("_________________________\n", feof(fp));
     i++;
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
  if(filePosition % 3){    
    printf("the data have odd number of 12bit data");
    threeByteForm.byteValue[2] = 0;
    printf("the last value is %#06x\n ", threeByteForm);
  }


  /*reorder the heap with heap sort*/
	/*output everything required to the output file*/
  passDataOutputFile(argv[1],fp, 2);
	
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

void passDataOutputFile(char*fileName, FILE* inputFile, long filePostion){
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
	int i;
	for(i = 1; i < 33; i++){
		fprintf(fp,"%d\n", heapArray[i] );
	}
	/*write the last 32 to the output file*/
	fprintf(fp, "--Last 32 Valeus--\n");

	//use fseek to locate the position of the input file with refer to end of file 
	//get one out and put it to the output
	/*close file */
	fclose(fp);
  /* open input file scuccessfully*/
  fprintf(stdout, "All data write to %s\n", fileName);   
  return;	
}
