#include <stdio.h>
#include <errno.h>
#include <sys/time.h>


int main() {

    struct timeval ti, tf;
    int i;

    if((gettimeofday(&ti,NULL)) != 0){
        perror("Error: ");
        return -1;
    }
    for(i=0;i<1000000;i++){

    }

    if((gettimeofday(&tf,NULL)) != 0){
        perror("Error: ");
        return -1;
    }

    printf("El bucle ha tardado %d microsegundos",tf.tv_usec-ti.tv_usec);


   return 1;
}

