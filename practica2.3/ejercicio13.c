#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile int sigus = 0;
volatile int sigalarm = 0;



void handlerAlarm(int arg){    
    sigalarm = 1;
}

void handlerSIGUSR1(int arg){
    sigus = 1;
}



int main(int argc, char **argv) {

     if (argc < 2) {
		fprintf(stderr, "Usage: %s <time>\n",argv[0]);
		return -1;
	}

    int sec = atoi(argv[1]);
    sigset_t s;
	struct sigaction alarma, sigusr1;


    sigfillset(&s);
	sigdelset(&s, SIGALRM);
	sigdelset(&s, SIGUSR1);

    alarma.sa_handler = handlerAlarm;
	sigusr1.sa_handler = handlerSIGUSR1;

    sigaction(SIGUSR1, &sigusr1, NULL);
    sigaction(SIGALRM, &alarma, NULL);


    alarm(sec);
    sigsuspend(&s);



    if(sigus){
        printf("Se ha evitado el borrado con la señal SIGUSR1 \n");
    }
    if(sigalarm){
        remove(argv[0]);
        printf("Ejecutable %s eliminado correctamente \n", argv[0]);
    }


    return 0;
   
}

