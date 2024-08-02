#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Define a structure for the class
typedef struct {
    pthread_mutex_t mutex;
} MyClass;

// Initialize the class with a recursive mutex
void MyClass_init(MyClass *myClass) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&myClass->mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

// Destroy the mutex in the class
void MyClass_destroy(MyClass *myClass) {
    pthread_mutex_destroy(&myClass->mutex);
}

// Define MethodA which locks the mutex and calls MethodB
void MethodB(MyClass *myClass);

void MethodA(MyClass *myClass) {
    pthread_mutex_lock(&myClass->mutex);
    printf("In MethodA\n");
    MethodB(myClass);
    pthread_mutex_unlock(&myClass->mutex);
}

// Define MethodB which also locks the mutex
void MethodB(MyClass *myClass) {
    pthread_mutex_lock(&myClass->mutex);
    printf("In MethodB\n");
    pthread_mutex_unlock(&myClass->mutex);
}

// Define the function to be run by a thread
void* thread_function(void* arg) {
    MyClass *myClass = (MyClass *)arg;
    MethodA(myClass);
    return NULL;
}

int main() {
    MyClass myClass;
    MyClass_init(&myClass);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_function, &myClass);
    pthread_create(&thread2, NULL, thread_function, &myClass);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    MyClass_destroy(&myClass);
    return 0;
}

