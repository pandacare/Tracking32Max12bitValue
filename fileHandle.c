/**
 * @file fileHandle.c
 * @author Chengliu Li
 * @date 18 June 2016
 * @brief tracking 32 maximum values
 */
/*****************************************************
*Handle file operation
*****************************************************/



FILE* openFile(int argc, char*fileName){
	FILE* fp;
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
 

