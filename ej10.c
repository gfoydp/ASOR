#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>



int main() {

    int uid = getuid();

    struct passwd *pass;

    if((pass = getpwuid(uid)) == NULL){
        perror("Error: ");
        return -1;
    }
    else{
        printf("Nombre de usuario: %s \n", pass->pw_name);
        printf("Directorio de usuario: %s \n", pass->pw_dir);
        printf("Descripcion de usuario: %s \n", pass->pw_gecos);


    }





   return 1;
}

