#include <stdio.h>
#include <errno.h>
#include <stdlib.h>






int main(int argc, char **argv) {

    if (argc < 2) {
		fprintf(stderr, "Usage: %s <\"command\">\n",argv[0]);
		return -1;
	}

    if(system(argv[1])== -1){
        perror("Error al ejecutar system ");
        return -1;
    }
    printf("El comando terminó de ejecutarse\n");

    


    return 0;
   
}

