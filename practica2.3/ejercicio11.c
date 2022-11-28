#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>




int main(int argc, char **argv) {
    char* sec;
    int seconds;

    sec = getenv("SLEEP_SECS");

    if(sec == NULL){
        perror("Error al obtener segundos SLEEP_SECS ");
        return -1;
    }
    seconds = atoi(sec);

    sigset_t blk_set, pending;

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);

    sigprocmask(SIG_BLOCK, &blk_set, NULL);

    sleep(seconds);
   
    sigpending(&pending);

    if(sigismember(&pending,SIGINT)){
        printf("Se ha recibido una señal SIGINT \n");
    }
    if(sigismember(&pending,SIGTSTP)){
        printf("Se ha recibido una señal SIGTSTP \n");
    }

    sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

    printf("SOLO SE MOSTRARA SI SE REANUDA EL PROCESO O NO RECIBE SEÑALES\n");

    return 0;
   
}

