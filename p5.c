#include <stdio.h>
#include <pthread.h>
#define SIZE 100 // Array size
int data[SIZE]; // Array to search through
int found_index = -1; // Index of the found element
pthread_mutex_t lock; // Mutex for synchronizing access to found_index
// Step 1: Function to search for a number in a subarray
void* search(void* arg) {
int start = *(int*)arg; // Start index for this thread's subarray
for (int i = start; i < start + SIZE / 4; i++) {
if (data[i] == 50) { // Look for the number 50
pthread_mutex_lock(&lock); // Lock mutex before updating shared variable
found_index = i; // Update found index
pthread_mutex_unlock(&lock); // Unlock mutex after updating
return NULL; // Exit once number is found
}
}
return NULL; // Exit if number is not found
}
int main() {
pthread_t threads[4]; // Array of thread identifiers
int thread_ids[4]; // Array for starting indices for each thread
// Step 2: Initialize data array with values from 1 to 100
for (int i = 0; i < SIZE; i++) {
data[i] = i + 1; // Fill array with numbers 1 to 100
}
pthread_mutex_init(&lock, NULL); // Initialize the mutex
// Step 3: Create 4 threads, each searching one-quarter of the array

for (int i = 0; i < 4; i++) {
thread_ids[i] = i * (SIZE / 4); // Assign starting index for each thread
pthread_create(&threads[i], NULL, search, (void*)&thread_ids[i]); // Create thread
}
// Step 4: Wait for all threads to complete their execution
for (int i = 0; i < 4; i++) {
pthread_join(threads[i], NULL); // Join threads to ensure all finish
}
// Step 5: Print the result after all threads finish execution
if (found_index != -1) {
printf("Number 50 found at index: %d\n", found_index); // Number found
} else {
printf("Number 50 not found.\n"); // Number not found
}
pthread_mutex_destroy(&lock); // Destroy the mutex
return 0;
}
