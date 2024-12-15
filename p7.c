#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 5
int account_balance = 1000; // Initial account balance
pthread_mutex_t lock; // Mutex for synchronizing access to account balance
// Step 1: Function for threads to perform transactions
void* perform_transaction(void* arg) {
int amount = *((int*)arg);
pthread_mutex_lock(&lock); // Lock the mutex
// Step 2: Critical Section
if (account_balance + amount >= 0) { // Ensure no overdraft
account_balance += amount; // Update balance
printf("Transaction successful. New balance: %d\n", account_balance);
} else {
printf("Transaction denied. Insufficient funds.\n");
}
pthread_mutex_unlock(&lock); // Unlock the mutex
return NULL;
}
int main() {
pthread_t threads[NUM_THREADS];
int transactions[NUM_THREADS] = {-200, 100, -300, 150, -400}; // Transactions to perform
pthread_mutex_init(&lock, NULL); // Initialize mutex
// Step 3: Create threads to perform transactions
for (int i = 0; i < NUM_THREADS; i++) {
pthread_create(&threads[i], NULL, perform_transaction, (void*)&transactions[i]);
}
// Step 4: Join threads
for (int i = 0; i < NUM_THREADS; i++) {
pthread_join(threads[i], NULL);
}
printf("Final account balance: %d\n", account_balance);
pthread_mutex_destroy(&lock); // Destroy mutex
return 0;
}
