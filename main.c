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
int heapArray[33];// min heap, i.e. the smallest value is in heap[1]
int heapSize = 0;
typedef struct {
  unsigned char byteValue [3];
}threeByteForm_t;
threeByteForm_t threeByteForm;
void heapFunction(int element){
 //no return for now 
  
}

int main(int argc, char *argv[]){
  
  FILE *fp;

  /**open file*/
  
  //taking card of error conditions for reading file
  if(argc != 2){   // Check the files
    fprintf(stderr, "ERROR: Missing input file, please refer to readMe.txt");
    return(-1);
    
  }
  if((fp = fopen(argv[1], "rb")) == NULL){
    fprintf(stderr, "ERROR opening file %s: %s", argv[1], strerror(errno));
    return(errno);
  }
  fprintf(stdout, "reading sensor data out of %s\n", argv[1]);
  int i = 0;
  while((fread(&threeByteForm, sizeof(threeByteForm), 1, fp)) != 0){
     printf("the %d th value is %#06x\n", i, threeByteForm);
     printf("the position of stream is %d\n", ftell(fp)); 
     printf("the value of feof() is %d\n", feof(fp));
     printf("_________________________\n", feof(fp));
     i++;
  }
  if(!feof(fp)){
    //error during file reading
    fprintf(stderr, "ERROR reading file %s: %s", argv[1], strerror(errno));
    return(errno);
  }
  //check if have the odd 12bits data, have to use division here, risky
  if(ftell(fp)%3){
    printf("the data have odd number of 12bit data");
  }

  
  

  fclose(fp);
  return 0;
  //call openFile function 

/*****************************************************/
// while not the end of the file, get two 12bits data from the input file

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
//reorder the heap with heap sort
//output it to the output file

//output the last 32 to the output file





}
