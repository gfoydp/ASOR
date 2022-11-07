#include <stdio.h>
#include <errno.h>
#include <time.h>


int main() {

    time_t t;
    struct tm *y;

    t = time(&t);

    if((y=localtime(&t)) == NULL){
        perror("Error: ");
        return -1;
    }


    printf("El año es %d \n",y->tm_year + 1900);


   return 1;
}

