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
    int s, bytes, fin = 0, sckt,i;
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV], buffer[256];
    struct tm * t_info;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    size_t sz;
    pid_t pid;


    if(argc != 3) {
    fprintf(stderr, "Usage: %s <host> <puerto>",argv[0]);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    
    hints.ai_socktype = SOCK_DGRAM; 
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

    for(i = 0;i < 5;i++){
        pid = fork();
        if(pid == -1){
            perror("Error al realizar fork:");
        }
        else if(pid == 0){
            while(!fin){
            bytes = recvfrom(sckt, buffer, 256, 0, (struct sockaddr *) &addr, &addrlen);
            buffer[bytes] = '\0';
            printf("Proceso con PID %d \n", getpid());

            s = getnameinfo((struct sockaddr *) &addr, addrlen, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
            printf("%d bytes de %s:%s\n", bytes, hbuf, sbuf);

            time_t t;
            t = time(NULL);
            t_info = localtime(&t);	

            if(buffer[0] != 't' && buffer[0] != 'q' && buffer[0] != 'd'){
                printf("Comando %c no soportado \n", buffer[0]);
            }

            if(buffer[0] == 't'){
                sz = strftime(buffer, 256, "%H:%M:%S", t_info);
            }
            if(buffer[0] == 'd'){
                sz = strftime(buffer, 256, "%Y-%m-%d", t_info);
            }      
            if(buffer[0] == 'q'){
                fin = 1;
                close(sckt);
                printf("Saliendo del proceso %d\n",getpid());


            }

            bytes = sendto(sckt, buffer, sz, 0, (struct sockaddr *) &addr, addrlen);
        }  
        }
        // else{
        //     wait(NULL);
        // }
    }

    for(i = 0;i < 5;i++){
        wait(NULL);
    }
    



    return 0;
   
}

