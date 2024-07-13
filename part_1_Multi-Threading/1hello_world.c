#include<stdio.h>
#include<stdlib.h>
#include<pthread.h> //This is a POSIX thread library. POSIX stands for "portable operating system interface". Meaning it works in every OS.
#include<unistd.h>

/*
   Please note that if the parent thread (main thread) dies, so do all child threads. This makes sense because when the main thread terminates, the process itself ends. When a process ends, all its threads are terminated as well.

   For a parent thread to die gracefully without affecting child threads, it can call pthread_exit(NULL), allowing the process to remain alive until all threads have completed their execution. Alternatively, the parent thread can use pthread_join to wait for child threads to finish before terminating.
   
   However, if the main thread ends with a return statement (e.g., return 0;), it causes the entire process to terminate immediately. Since threads are part of the process, they cannot continue to run once the process has ended.
*/


void create_a_thread();
static void * printer(void *);
void sleep_one_second(void);


int main(int argc, char **argv){
    create_a_thread();
    sleep_one_second();
    return 0;
}


void create_a_thread(){
    //pthread_t is an opaque onject. You don't have to know its internals
    pthread_t pthread1;
    static char *thread_input = "I'm thread number 1. Hello World\n\n"; //This will be passed to the thread.
    pthread_t tid= pthread_create(&pthread1, /*If succesfully created it returns 0*/
            NULL,
            printer,
            (void *)thread_input); /*The thread_input has to be either heap or static.*/
    pthread_join(tid,NULL);
}

static void *printer(void *thread_input){
    char *what_to_print = (char *) thread_input;
    printf("%s",what_to_print);
}

void sleep_one_second(void){
    printf("The parent thread is in the \"sleep_one_second\" function and is sleeping for a second.\nPlease note that only the parent thread comes here and not the child thread\n");
    sleep(1);
}
