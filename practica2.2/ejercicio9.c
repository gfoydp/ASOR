#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>




int main(int argc, char ** argv) {
    struct stat sb;

    if (argc != 2) {
		printf("Usage: ./ejercicio9 <file>\n");
		return -1;
	}

    if(stat(argv[1], &sb)==-1){
        perror("Error: ");
        return -1;
    }


    if (S_ISREG(sb.st_mode)) {
    printf("Fichero regular \n");
    }
    else if (S_ISDIR(sb.st_mode)) {
    printf("Directorio \n");
    }
    else if (S_ISLNK(sb.st_mode)) {
    printf("Enlace simbolico \n");
    }

    printf("Major: %d\n",major(sb.st_dev));
    printf("Minor: %d\n",minor(sb.st_dev));
    printf("Inodo: %d\n",sb.st_ino);
    printf("Ultima fecha de acceso: %s",ctime(&sb.st_mtime));

    return 0;
   
}

