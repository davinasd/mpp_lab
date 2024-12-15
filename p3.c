#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define SIZE 3 // Matrix size
int A[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int B[SIZE][SIZE] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int C[SIZE][SIZE]; // Resultant matrix
// Structure to hold both row index and thread ID
typedef struct {
int row;
pthread_t thread_id;
} thread_data;
// Step 1: Function to add elements of matrices
void* add_matrices(void* arg) {
thread_data* data = (thread_data*)arg;
int i = data->row;
printf("Thread ID: %lu is processing row %d\n", (unsigned long)pthread_self(), i);
for (int j = 0; j < SIZE; j++) {
C[i][j] = A[i][j] + B[i][j]; // Element-wise addition
}
free(data); // Free the allocated memory for thread data
return NULL;
}

int main() {
pthread_t threads[SIZE]; // Thread array
// Step 2: Create threads for each row
for (int i = 0; i < SIZE; i++) {
thread_data* data = malloc(sizeof(thread_data)); // Allocate memory for thread data
data->row = i; // Set the row index
pthread_create(&threads[i], NULL, add_matrices, data);
}
// Step 3: Join threads
for (int i = 0; i < SIZE; i++) {
pthread_join(threads[i], NULL);
}
// Step 4: Print the resultant matrix
printf("Resultant Matrix:\n");
for (int i = 0; i < SIZE; i++) {
for (int j = 0; j < SIZE; j++) {
printf("%d ", C[i][j]);
}
printf("\n");
}
return 0;
}
