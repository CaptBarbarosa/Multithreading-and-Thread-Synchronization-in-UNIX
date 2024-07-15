#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *printer(void *given_number){
    int to_print = *(int *)given_number;
    printf("%d\n",to_print);
    return NULL;
}

int main(){
    pthread_t *my_threads;
    int number, i;
    printf("Enter N: ");
    scanf("%d", &number);
    if ((my_threads = (pthread_t *) malloc(sizeof(pthread_t)*number)) == NULL){
        printf("Failure to create pthread_t array\n");
        exit(1);
    }
    for(i=number; i>0 ; i--){
        if((pthread_create(&my_threads[i-1], NULL, printer, &i)) != 0 ){
            printf("Failed to create thread");
            exit(1);
        }
        if(pthread_join(my_threads[i-1], NULL) != 0){
            printf("Failed to join");
            exit(1);
        }
    }
    free(my_threads);
    return 0;
}
