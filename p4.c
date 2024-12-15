#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 4 // Number of threads to use
#define SIZE 16 // Size of the array
int array[SIZE] = {38, 27, 43, 3, 9, 82, 10, 29, 42, 2, 1, 8, 5, 6, 7, 4};
int sorted[SIZE]; // Array to hold the sorted elements
pthread_mutex_t mutex; // Mutex for synchronized access
typedef struct {
int left;
int right;
int thread_id;
} thread_data;
// Merge function to combine two sorted halves
void merge(int left, int mid, int right) {
int i, j, k;
int n1 = mid - left + 1;
int n2 = right - mid;
// Create temporary arrays

int* L = (int*)malloc(n1 * sizeof(int));
int* R = (int*)malloc(n2 * sizeof(int));
for (i = 0; i < n1; i++)
L[i] = array[left + i];
for (j = 0; j < n2; j++)
R[j] = array[mid + 1 + j];
// Merge the temporary arrays
i = 0; // Initial index of first sub-array
j = 0; // Initial index of second sub-array
k = left; // Initial index of merged sub-array
while (i < n1 && j < n2) {
if (L[i] <= R[j]) {
array[k] = L[i];
i++;
} else {
array[k] = R[j];
j++;
}
k++;
}
// Copy the remaining elements of L[]
while (i < n1) {
array[k] = L[i];
i++;
k++;
}
// Copy the remaining elements of R[]
while (j < n2) {
array[k] = R[j];
j++;
k++;
}
free(L);
free(R);
}
// Merge sort function
void* merge_sort(void* arg) {
thread_data* data = (thread_data*)arg;
int left = data->left;
int right = data->right;
if (left < right) {
int mid = left + (right - left) / 2;

thread_data left_data = {left, mid, data->thread_id};
thread_data right_data = {mid + 1, right, data->thread_id};
// Create threads for left and right halves
pthread_t left_thread, right_thread;
pthread_create(&left_thread, NULL, merge_sort, (void*)&left_data);
pthread_create(&right_thread, NULL, merge_sort, (void*)&right_data);
pthread_join(left_thread, NULL);
pthread_join(right_thread, NULL);
// Merge the sorted halves
merge(left, mid, right);
}
return NULL;
}
int main() {
pthread_t threads[NUM_THREADS];
pthread_mutex_init(&mutex, NULL);
// Step 1: Create threads for sorting the entire array
thread_data initial_data = {0, SIZE - 1, 0};
pthread_create(&threads[0], NULL, merge_sort, (void*)&initial_data);
// Wait for the sorting thread to finish
pthread_join(threads[0], NULL);
// Print the sorted array
printf("Sorted Array:\n");
for (int i = 0; i < SIZE; i++) {
printf("%d ", array[i]);
}
printf("\n");
pthread_mutex_destroy(&mutex);
return 0;
}
