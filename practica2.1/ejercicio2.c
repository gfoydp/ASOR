#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>





int main() {
   
   if(setuid(0) == -1){
       perror("Error con perror");
       printf("Error %d: %s\n", errno, strerror(errno));
   }
   return 1;
}

