#include <pthread.h>
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t mutex_1;
int condition=0;

void *waiting_thread(void *arg){
    int i;
    for (i=0; i<5;i++){
        pthread_mutex_lock(&mutex_1);
        condition++;
        //printf("->Condition is: %d\n",condition);
        pthread_mutex_unlock(&mutex_1);
    }
    return NULL;
}


void *signalling_thread(void *arg){
    {
        pthread_mutex_lock(&mutex_1);
        condition--;
        //printf("-->Condition is: %d\n",condition);
        pthread_mutex_unlock(&mutex_1);
    }
    return NULL;
}

int main(){
    int i;
    pthread_mutex_init(&mutex_1, NULL);
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
            perror("Failed to join\n");
            exit(1);
        }
    }
    return 0;
}
