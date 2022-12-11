#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>




int main(int argc, char** argv) {

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, bytes, fin = 0, sckt,c;
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV], buffer[256];
    struct tm * t_info;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    size_t sz;


    if(argc != 3) {
    fprintf(stderr, "Usage: %s <host> <puerto>",argv[0]);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;    


    s = getaddrinfo(argv[1],argv[2], &hints, &result);

    if(s != 0){
        fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
		return -1;
    }


    sckt = socket(result->ai_family,result->ai_socktype, result->ai_protocol);

    if(sckt == -1){
        perror("Error al crear el socket:");
		return -1;
    }

    if(bind(sckt,(struct sockaddr *) result->ai_addr, result->ai_addrlen)==-1){
        perror("Error al realizar bind:");
		return -1;
    }

    if((listen(sckt,5))==-1){
        perror("Error al realizar listen:");
		return -1;
    }
    while(1){
        int clisd = accept(sckt, (struct sockaddr *) &addr, &addrlen);

        pid_t pid = fork();

        if(pid == -1){
            perror("Error al realizar fork:");
            return -1;
        }
        else if(pid == 0){
        s = getnameinfo((struct sockaddr *) &addr, addrlen, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        printf("Conexión desde %s:%s PID %d\n", hbuf, sbuf,getpid());
        while (c = recv(clisd, buffer, 256, 0)) { 
            if(c==-1){
                perror("Error al realizar recv: ");
                close(clisd);
                return -1;
            }
        send(clisd, buffer, c, 0);
        }
        printf("Saliendo del proceso %d\n",getpid());
        }
        else{
            close(clisd);
        }
    }
   

    return 0;
   
}

