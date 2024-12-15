#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 100
#define NUM_THREADS 4
int array[SIZE]; // Array to sort
int temp[SIZE]; // Temporary array for merging
// Merge function for merging two sorted arrays
void merge(int left, int mid, int right) {
int i = left, j = mid + 1, k = left;
while (i <= mid && j <= right) {
if (array[i] < array[j]) {
temp[k++] = array[i++];
} else {
temp[k++] = array[j++];
}
}
while (i <= mid) {
temp[k++] = array[i++];
}
while (j <= right) {
temp[k++] = array[j++];
}
for (i = left; i <= right; i++) {
array[i] = temp[i];
}
}
// Iterative merge sort for each thread's portion of the array
void merge_sort(int left, int right) {
if (left >= right) return;
int mid = (left + right) / 2;
merge_sort(left, mid);
merge_sort(mid + 1, right);

merge(left, mid, right);
}
// Thread function to sort a portion of the array
void* thread_sort(void* arg) {
int thread_part = *(int*)arg;
int left = thread_part * (SIZE / NUM_THREADS);
int right = (thread_part + 1) * (SIZE / NUM_THREADS) - 1;
merge_sort(left, right);
pthread_exit(NULL);
}
// Final merging of all parts
void merge_all_parts() {
int part_size = SIZE / NUM_THREADS;
for (int i = 1; i < NUM_THREADS; i++) {
merge(0, i * part_size - 1, (i + 1) * part_size - 1);
}
}
int main() {
pthread_t threads[NUM_THREADS];
int thread_ids[NUM_THREADS];
// Initialize array with random numbers
for (int i = 0; i < SIZE; i++) {
array[i] = rand() % 1000; // Random numbers between 0-999
}
// Create threads for parallel sorting
for (int i = 0; i < NUM_THREADS; i++) {
thread_ids[i] = i;
pthread_create(&threads[i], NULL, thread_sort, (void*)&thread_ids[i]);
}
// Join threads
for (int i = 0; i < NUM_THREADS; i++) {
pthread_join(threads[i], NULL);
}
// Merge all sorted parts
merge_all_parts();
// Print sorted array
printf("Sorted Array:\n");

for (int i = 0; i < SIZE; i++) {
printf("%d ", array[i]);
}
printf("\n");
return 0;
}
