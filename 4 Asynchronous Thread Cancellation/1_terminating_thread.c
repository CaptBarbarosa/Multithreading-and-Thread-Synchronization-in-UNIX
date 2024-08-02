#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *cancel_thread(void *args){
    printf("Entered the cancel_thread\n");
    pthread_exit(NULL);  // With pthread_exit you can terminate naughty threads
    printf("I won't be able to print this. For I got exited.\n");
    printf("Terminated.\n");
    printf("Retired from life.\n");
    printf("You cut me from life you little POS.\n");
    printf("You were supposed to love me for god's sake.\n");
}

int main(){
    pthread_t naughty_thread;
    if(pthread_create(&naughty_thread, NULL, cancel_thread,NULL) != 0){
        printf("Failed to create thread\n");
        exit(1);
    }
    pthread_join(naughty_thread,NULL);
    return 0;
}
