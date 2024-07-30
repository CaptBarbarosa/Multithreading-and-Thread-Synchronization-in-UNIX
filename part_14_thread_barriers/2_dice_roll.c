#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_barrier_t dice_roll_barrier;
int thread_results[8];

void *dice_rolls(void *args){
    int id = *((int *)args);
    thread_results[id] = rand()%6;
    pthread_barrier_wait(&dice_roll_barrier);
    int i,max=0;
    for(i=0;i<8;i++){
        //printf("thread_results[%d]: %d\n",i,thread_results[i]);
        if(thread_results[i] > max){
            max=thread_results[i];
        }
    }
    //printf("Max is: %d",max);
    if(id==1){
        for(i=0;i<8;i++){
            if(max== thread_results[i]){
                printf("Thread %d won\n",i);}
        }
    }
}



int main(){
    srand(time(NULL));
    pthread_barrier_init(&dice_roll_barrier, NULL, 8);
    int i,ids[8];
    pthread_t tarray[8];
    for(i=0; i<8; i++){
        ids[i]=i;
        if(pthread_create(&tarray[i], NULL, dice_rolls, &ids[i])!=0){
            printf("Failed to create thread\n");
            exit(1);
        }
    }

    for (i = 0; i < 8; i++) {
        pthread_join(tarray[i], NULL);}

    pthread_barrier_destroy(&dice_roll_barrier);

    return 0;
}


