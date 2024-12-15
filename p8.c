#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_BREAD 10
int bread_count = 0; // Current number of bread loaves
pthread_mutex_t lock; // Mutex for synchronizing access to bread_count
pthread_cond_t cond; // Condition variable
// Function for the producer thread
void* producer(void* arg) {
while (1) {
pthread_mutex_lock(&lock);
while (bread_count >= MAX_BREAD) {
pthread_cond_wait(&cond, &lock); // Wait if bread_count reaches MAX_BREAD
}
bread_count++; // Produce a loaf of bread
printf("Produced bread. Total: %d\n", bread_count);
pthread_cond_broadcast(&cond); // Wake up all waiting threads
pthread_mutex_unlock(&lock);
sleep(1); // Simulate time taken to produce bread
}
return NULL;
}
// Function for the consumer thread
void* consumer(void* arg) {
while (1) {
pthread_mutex_lock(&lock);
while (bread_count <= 0) {
pthread_cond_wait(&cond, &lock); // Wait if there's no bread to consume
}
bread_count--; // Consume a loaf of bread
printf("Consumed bread. Remaining: %d\n", bread_count);
pthread_cond_broadcast(&cond); // Wake up all waiting threads
pthread_mutex_unlock(&lock);
sleep(1); // Simulate time taken to consume bread
}
return NULL;
}
int main() {
pthread_t prod_thread, cons_thread;
// Initialize mutex and condition variable
pthread_mutex_init(&lock, NULL);
pthread_cond_init(&cond, NULL);
// Create producer and consumer threads
pthread_create(&prod_thread, NULL, producer, NULL);
pthread_create(&cons_thread, NULL, consumer, NULL);
// Join threads (they will run indefinitely in this example)
pthread_join(prod_thread, NULL);
pthread_join(cons_thread, NULL);
// Destroy mutex and condition variable
pthread_mutex_destroy(&lock);
pthread_cond_destroy(&cond);
return 0;

}
