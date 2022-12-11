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

    if(connect(sckt,(struct sockaddr *) result->ai_addr, result->ai_addrlen)==-1){
        perror("Error al realizar connect:");
		return -1;
    }


     while(!fin){
        bytes = read(0, buffer, 256);
        buffer[bytes] = '\0';

        if(buffer[0] == 'Q' && bytes == 2){
            fin = 1;
            close(sckt);
        }
        else{
        c = send(sckt, buffer, bytes+1, 0);
        if(c==-1){
             perror("Error al realizar send: ");
             close(sckt);
             return -1;
        }
        bytes = recv(sckt, buffer, 256, 0);
        buffer[bytes] = '\0';
        printf("%s", buffer);
        }
    }


    return 0;
   
}

