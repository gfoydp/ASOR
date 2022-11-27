#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>





int main() {

    pid_t p;

    p = fork();

    if(p == -1){
        perror("Error al crear hijo");

    }
    else if(p == 0){
        int pid, ppid, pgid, sid;
        struct rlimit rlim;
        char buffer[20];

        if(setsid()==-1){
            perror("Error al crear sesion ");
            return -1;
        }

        if(chdir("/tmp")==-1){
            perror("Error al cambiar la ruta ");
            return -1;
        }

        pid = getpid();
        ppid = getppid();
        pgid = getpgid(pid);
        sid = getsid(pid);

        if((getrlimit(RLIMIT_NOFILE, &rlim))==-1){
            perror("Error al obtener el maximo de ficheros");
            return -1;
        }

        if((getcwd(buffer, sizeof(buffer))) == NULL){
            perror("Error al obtener el directorio");
            return -1;

        }


        printf("PID %d \nPPID %d \nPGID %d \nSID %d\n ",pid,ppid,pgid,sid);
        printf("Maximo de ficheros que se puede abrir %d\n ",rlim.rlim_max);
        printf("Directorio de trabajo actual %s ",buffer);

    }
   




    return 0;
   
}

