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















int main(int argc, char **argv){
    create_a_thread();
    printf("main fn is paused\n");
    return 0;
}




void create_a_thread(){
    //pthread_t is an opaque onject. You don't have to know its internals
    pthread_t pthreadl;
    static char *thread_input = "I'm thread number 1. Hello World"; //This will be passed to the thread.
    int is_successful = pthread_create
}




