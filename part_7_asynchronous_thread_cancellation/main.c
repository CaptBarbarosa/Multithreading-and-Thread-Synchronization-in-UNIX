#include "glthread.c"
#include <stdlib.h>
#include <stdio.h>
// Now assume that we have two threads. thread_1 and thread_2. They both are in operation and thread_1 tries to cancel thread_2. The thread_1 sends a cancellation request [CR(pthread_cancel)].

// When a thread tries to cancel another threat, the cancellation request [CR(pthread_cancel())] is queued by OS. It isn't delivered immediately.

// The OS afterwards, looks for an opportunity to terminate thread T2.

// OS may not terminate the thread instantly (Asynchronous).

int main(){
    return 0;
}


