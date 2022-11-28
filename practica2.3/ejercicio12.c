#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


volatile int ints = 0;
volatile int stops = 0;
volatile int c = 0;


void handlerint(int arg){
    ints++;
    c++;

}

void handlerstp(int arg){
 stops++;
 c++;
}

int main(int argc, char **argv) {

    struct sigaction sing,sstp ;

    sing.sa_handler = handlerint;
    sigaction(SIGINT, &sing, NULL);

    sstp.sa_handler = handlerstp;
    sigaction(SIGTSTP , &sstp, NULL);

    while(c < 10){};

    printf("%d SIGINT recibidos\n",ints);
    printf("%d SIGTSTP recibidos\n",stops);

    return 0;
   
}

