#include <stdio.h>
#include <errno.h>
#include <stdlib.h>



int main(int argc, char **argv) {

    if (argc < 2) {
		fprintf(stderr, "Usage: %s <command>\n",argv[0]);
		return -1;
	}

    if(execvp(argv[1],&argv[1])== -1){
        perror("Error al ejecutar execvp ");
        return -1;
    }
    printf("El comando terminó de ejecutarse\n"); //Nunca se va a mostrar


    return 0;
   
}

