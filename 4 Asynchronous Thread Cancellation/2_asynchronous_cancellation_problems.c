// Please take a look at this short code and you'll notice that tid1 allocates memory 
// but it can't dealocate it causing memory leaks. 
// In the next code you'll see the solution to that.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid1, tid2;
void *task(void *args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int *array=NULL;
    array = (int *) malloc(1000*sizeof(int));
    if(array == NULL){
        printf("Failed to allocate memory to array in task function\n");
        exit(1);
    }
    printf("Allocation is succesfull\n");
    for(int i=0; i<5;i++){
        printf("Thread 1 is working %d\n",i);
        sleep(1);
    }
    printf("Now will free the array\n");
    free(array);
    array = NULL;

    for(int i=0;i<5;i++){
        printf("Thread 1 is working again in the second loop for %d\n",i);
        sleep(1);
    }
    return NULL;
}

void *canceller(void *args){
    sleep(3);
    printf("Cancelling thread 1\n");
    pthread_cancel(tid1);
    return NULL;
}

int main(){
    if(pthread_create(&tid1, NULL, task, NULL) != 0){
        printf("Failed to create tid1\n");
        exit(1);
    }
    if(pthread_create(&tid2, NULL, canceller, NULL) != 0){
        printf("Failed to create tid2\n");
        exit(1);
    }
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
