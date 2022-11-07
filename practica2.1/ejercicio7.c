#include <stdio.h>
#include <unistd.h>




int main() {

    long link,path, name;

    if((link = pathconf("/home/cursoredes/Desktop/P1/ASOR/",_PC_LINK_MAX)) == -1){
        perror("Error al obtener el numero maximo de enlaces");
        return -1;
    }
    if((path = pathconf("/home/cursoredes/Desktop/P1/ASOR/",_PC_PATH_MAX)) == -1){
        perror("Error al obtener el tamaño maximo de ruta");
        return -1;
    }
    if((name = pathconf("/home/cursoredes/Desktop/P1/ASOR/",_PC_NAME_MAX)) == -1){
        perror("Error al obtener el tamaño maximo de nombre");
        return -1;
    }

    printf("Numero maximo de enlaces: %ld \n", link);
    printf("Tamaño maximo de ruta: %ld \n", path );
    printf("Tamaño maximo de nombre: %ld \n", name);

   return 1;
}

