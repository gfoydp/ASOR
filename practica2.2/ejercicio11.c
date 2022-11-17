#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>




int main(int argc, char ** argv) {
    struct stat sb;
    if(stat(argv[1], &sb)==-1){
        perror("Error: ");
        return -1;
    }

    if (S_ISREG(sb.st_mode)) {

        //char * destino;
        char * hard, sym;
        //destino = malloc(strlen(argv[1])+6);

        char *destino = malloc(strlen(argv[1])+6);
        sprintf(destino, "%s.hard", argv[1]);
        if(link(argv[1],destino)==-1){
            perror("Eror al crear enlace duro");
            return -1;
        }
        sprintf(destino, "%s.sym", argv[1]);
        if(symlink(argv[1],destino)==-1){
            perror("Eror al crear enlace simbolico");
            return -1;
        }

   // free(destino);

    }


    return 0;
   
}

