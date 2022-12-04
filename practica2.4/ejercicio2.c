#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv) {

    int p_h[2];
    int h_p[2];

    char buffer[512];
    char c = 'l';
    int rd ,i;



    if(pipe(p_h) == -1){
    perror("Error al crear el pipe p_h: ");
    return -1;
   }
    if(pipe(h_p) == -1){
    perror("Error al crear el pipe h_p: ");
    return -1;
   }
    pid_t pid;

    pid = fork();

   if(pid == -1){
    perror("Error al realizar fork: ");
    return -1;
   }
    else if(pid == 0){
    close(p_h[1]);
    close(h_p[0]);

    for(i=0;i<10;i++){
        rd = read(p_h[0],buffer,512);
        buffer[rd] = '\0';
        printf("%s \n",buffer);
        sleep(1);
        if(i==9){
            write(h_p[1],"q",1);
        }
        else{
            write(h_p[1],"l",1);
        }
    }
    close(p_h[0]);
    close(h_p[1]);
 
   }
   else {

    close(p_h[0]);
    close(h_p[1]);
       
    while(c != 'q'){
       scanf("%s", buffer);
       write(p_h[1], buffer, strlen(buffer) + 1);
       read(h_p[0],&c,1);
    }

    close(p_h[1]);
    close(h_p[0]);

   }
   
    return 0;
   
}

