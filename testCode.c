#include <stdio.h>
#include <stdlib.h>

int main()
{
   FILE * fp;
   FILE * fpOutput;
   fpOutput = fopen("test/bOUtput.bin","w");
   fp = fopen ("test/bin", "rb");
   fprintf(fpOutput, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fp);
   fclose(fpOutput);
   return(0);
}