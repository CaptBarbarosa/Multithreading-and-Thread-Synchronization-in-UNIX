#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

# define NUM_OF_THREADS 2
pthread_barrier_t barrier;
int rps_output[2]={-1,-1};

void *rps_result(void *args){
    int id = *((int *)args);
    printf("Thread %d has arrived but waiting\n",id);
    pthread_barrier_wait(&barrier);
    printf("Barrier is crossed\n");
    rps_output[id] = rand()%3;
    //0 = Rock, 1= Paper, 2 =Scissors
    if(rps_output[0]!= -1 && rps_output[1]!=-1){
        if(rps_output[0]==rps_output[1]){
            printf("DRAW\n");}
        else if(rps_output[0]==0 && rps_output[1]==1){
            printf("Thread 0 loses\n");
        }
        else if(rps_output[0]==1 && rps_output[1]==0){
            printf("Thread 0 loses\n");
        }
        else if(rps_output[0]==2 && rps_output[1]==0){
            printf("Thread 0 loses\n");
        }
        else{
            printf("Thread 0 wins\n");
        }
    }
}


int main(){
    srand(time(NULL));
    pthread_barrier_init(&barrier, NULL, 2);
    pthread_t threads[2];
    int result[2];
    int i;
    for(i=0;i<2;i++){
        if(pthread_create(&threads[i], NULL, rps_result, &i) != 0){
            printf("Failed to create thread\n");
            exit(1);
        }
        usleep(500000);
    }
    for(i=0;i<2;i++){
        if(pthread_join(threads[i],NULL)!=0){
            printf("Failed to join thread[%d]\n",i);
            exit(1);
        }
    }
    pthread_barrier_destroy(&barrier);
}



