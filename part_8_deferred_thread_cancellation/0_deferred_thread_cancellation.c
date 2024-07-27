#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_t tid1, tid2;

void memory_cleaner(void *arg){
    int *array = (int *)arg;
    if(array != NULL){
        printf("->At the memory_cleaner\n->Cleaning the memory allocation.\n");
        free(array);
        array = NULL;
    }
}

void file_cleaner(void *arg){
    printf("-->At the file_cleaner\n-->Closing the file stream\n");
    fclose((FILE *)arg);
}

void *task(void *args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    
    int *array=NULL;
    array = (int *) malloc(1000*sizeof(int));
    if(array == NULL){
        printf("Failed to allocate memory to array in task function\n");
        exit(1);
    }
    printf("Allocated the memory to array integer pointer\n");
    pthread_cleanup_push(memory_cleaner, array);

    FILE *my_stream;
    my_stream = fopen("delete_later.txt","w+");
    if(my_stream == NULL){
        printf("Failed to open the delete_later.txt for writing at the tesk function\n");
        exit(1);
    }
    pthread_cleanup_push(file_cleaner, my_stream);
    pthread_testcancel(); // I choosed here as a cancellation point because I already pushed to the cleanup functions. 

    for(int i=0; i<5;i++){
        printf("Thread 1 is working %d\n",i);
        sleep(1);
    }
    printf("Now will free the array\n");
    free(array);
    array = NULL;
    fclose(my_stream);
    pthread_cleanup_pop(0); // Removes the cleanup handler from the stack but doesn't execute it.
    pthread_cleanup_pop(0);
    for(int i=0;i<5;i++){
        printf("Thread 1 is working again in the second loop for %d\n",i);
        sleep(1);
    }
    return NULL;
}

void *canceller(void *args){
    sleep(3);
    printf("Thread 2 now cancelling the thread 1\n");
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
