#include <time.h>
#include <stdio.h>
#include <errno.h>



int main() {

    time_t t;
    if((t = time(&t)) == -1){
        perror("Error: ");
    }
    else{
    printf("Numero de segundos desde EPOCH: %d \n", t);

    }

   return 1;
}

