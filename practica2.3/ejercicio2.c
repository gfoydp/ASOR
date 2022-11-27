#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>



int main() {
   int sch, param, max, min;

   struct sched_param parametro;

   sch = sched_getscheduler(0);
   if(sch == -1){
    perror("Error al obtener la politica de planificacion: ");
    return -1;
   }
    switch(sch) {
        case SCHED_OTHER:
            printf("Politica de planificacion SCHED_OTHER \n");
            break;
        case SCHED_FIFO:
            printf("Politica de planificacion SCHED_FIFO \n");
            break;
        case SCHED_RR:
            printf("Politica de planificacion SCHED_RR \n");
            break;
        default : break;
    }  

    param =sched_getparam(0,&parametro);
   if(param == -1){
    perror("Error al obtener la prioridad de planificacion: ");
    return -1;
   }

   max = sched_get_priority_max(sch);
    if(max == -1){
    perror("Error al obtener la prioridad maxima: ");
    return -1;
   }

   min = sched_get_priority_min(sch);
    if(min == -1){
    perror("Error al obtener la prioridad minima: ");
    return -1;
   }

   printf("Prioridad %d \nMax %d \nMin %d \n",parametro.sched_priority,max,min);

    return 0;
   
}

