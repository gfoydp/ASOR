#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>



int main() {

    printf("El UID real es: %d \n", getuid());
    printf("El UID efectivo: %d \n", geteuid());

   return 1;
}

