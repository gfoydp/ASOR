#include <time.h>
#include <stdio.h>
#include <errno.h>



int main() {

    time_t t;
    if((t = time(&t)) == -1){
        perror("Error: ");
    }
    else{
    printf("Nombre de segundos: %d \n", t);

    }

   return 1;
}

