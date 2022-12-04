#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>



int main(int argc, char** argv) {

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int s;
    char buffer[100];

    if(argc != 2) {
    fprintf(stderr, "Usage: %s <host>",argv[0]);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    
    hints.ai_socktype = 0; 
    hints.ai_flags = AI_PASSIVE;    
    hints.ai_protocol = 0;          
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;


    s = getaddrinfo(argv[1],NULL, &hints, &result);

    if(s != 0){
        fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
		return -1;
    }

     for (rp = result; rp != NULL; rp = rp->ai_next) {
        s = getnameinfo(rp->ai_addr, rp->ai_addrlen, buffer, 100, NULL, 0, NI_NUMERICHOST);
		if (s != 0) {
			fprintf(stderr, "Error getnameinfo(): %s\n", gai_strerror(s));
			return -1;
		}
		printf("%s\t%d\t%d\n", buffer, rp->ai_family, rp->ai_socktype);
        }

    return 0;
   
}

