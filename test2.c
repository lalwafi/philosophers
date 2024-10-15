# include <stdio.h>
# include <pthread.h>
# include <unistd.h>

pthread_mutex_t lock;

void *thread_function(void *arg) {
    char *message = (char *)arg;
    
    for (int i = 0; i < 5; i++) {
        // Lock the mutex before printing
        pthread_mutex_lock(&lock);
        
        printf("%s: Iteration %d\n", message, i);
        
        // Unlock the mutex after printing
        pthread_mutex_unlock(&lock);

        // Simulate some work
        sleep(1);
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
