#include <stdio.h>

#include <sys/utsname.h>


int main() {
    
    struct utsname buf;

    if(uname(&buf) != 0){
        perror("Error: ");
        return -1;
    }

    printf("Sistema operativo: %s \n", buf.sysname);
    printf("Node name: %s \n", buf.nodename);
    printf("Release: %s \n", buf.release);
    printf("Version: %s \n", buf.version);
    printf("Machine: %s \n", buf.machine);

   return 1;
}

