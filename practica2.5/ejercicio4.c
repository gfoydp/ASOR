#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>




int main(int argc, char** argv) {

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s, bytes, fin = 0, sckt;
    char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV], buffer[256];
    struct tm * t_info;
    struct sockaddr_storage addr;
    socklen_t addrlen = sizeof(addr);
    size_t sz;
    fd_set set;


    if(argc != 3) {
    fprintf(stderr, "Usage: %s <host> <puerto>",argv[0]);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    
    hints.ai_socktype = SOCK_DGRAM; 
    // hints.ai_flags = AI_PASSIVE;     


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

    while(!fin){

        FD_ZERO(&set);
	    FD_SET(0, &set); 
		FD_SET(sckt, &set);
        s = select(sckt + 1, &set,0,0,0);
        if(sckt == -1){
        perror("Error al hacer el select:");
		return -1;
        }
        if (FD_ISSET(0, &set)) {
				bytes = read(0, buffer, 256);
				printf("Recibidos %d bytes de la entrada estándar\n", bytes);
		}
        else{
        bytes = recvfrom(sckt, buffer, 256, 0, (struct sockaddr *) &addr, &addrlen);
        buffer[bytes] = '\0';

        s = getnameinfo((struct sockaddr *) &addr, addrlen, hbuf, NI_MAXHOST, sbuf, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        printf("%d bytes de %s:%s\n", bytes, hbuf, sbuf);
        }
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
        }
        if (FD_ISSET(0, &set)) printf("%s\n", buffer);
	
        else bytes = sendto(sckt, buffer, sz, 0, (struct sockaddr *) &addr, addrlen);
        

    }

    close(sckt);
    printf("Saliendo...\n");


    return 0;
   
}

