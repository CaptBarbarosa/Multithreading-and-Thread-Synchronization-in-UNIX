#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex_1;
int condition=0;

void *waiting_thread(void *arg){
    printf("Deneme");
}


void *signalling_thread(void *arg){
    prints("Deneme2");
}

int main(){
    int i;
    pthread_t my_threads[2];
    for(i=0;i<2;i++){
        if(i==1){
            if(pthread_create(&my_threads[0], NULL, waiting_thread, NULL) != 0){
                perror("Failed to create first thread\n");
                exit(1);
            }
        }
        
        else{
            if(pthread_create(&my_threads[1], NULL, signalling_thread, NULL)){
                perror("Failed to create second thread\n");
                exit(1);
            }
        }
    }
    for(i=0; i<2; i++){
        if(pthread_join(my_threads[i], NULL) != 0){
            perror("Thread %d failed to join\n",i);
            exit(1);
        }
    }
    return 0;
}
