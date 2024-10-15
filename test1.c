# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

// Function executed by each thread
void *thread_function(void *arg) {
    char *message = (char *)arg;
    
    // Print message and simulate some work with sleep
    for (int i = 0; i < 5; i++) {
        printf("%s: Iteration %d\n", message, i);
        sleep(1);  // Simulate work with 1-second sleep
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads, passing different messages to each
    pthread_create(&thread1, NULL, thread_function, "Thread 1");
    pthread_create(&thread2, NULL, thread_function, "Thread 2");

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads finished execution.\n");

    return 0;
}
