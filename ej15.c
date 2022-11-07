#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <locale.h>



int main() {

    time_t t;
    char buffer[50];
    struct tm *lt;

    t = time(&t);

    if((lt=localtime(&t)) == NULL){
        perror("Error: ");
        return -1;
    }

	setlocale(LC_ALL,"es_ES");

    strftime(buffer,50,"%A, %d de %B de %Y, %R",lt);

    printf("Dia: %s \n",buffer);


   return 1;
}
