// Task No. 8: Priority Queues

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure to represent a student enrollment request
struct Request {
  int rollNumber;
  float academicPerformance;
};

// Structure to represent a priority queue using a max-heap
struct PriorityQueue {
  struct Request arr[MAX_SIZE];
  int size;
};

// Function to create a new priority queue
struct PriorityQueue* createPriorityQueue() {
  struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
  pq->size = 0;
  return pq;
}

// Function to swap two requests
void swap(struct Request* a, struct Request* b) {
  struct Request temp = *a;
  *a = *b;
  *b = temp;
}

// Function to maintain the max-heap property by bubbling up elements
void heapifyUp(struct PriorityQueue* pq, int index) {
  int largest = index;
  int parent = (index - 1) / 2;

  // Find the parent with higher academic performance (max-heap)
  if (parent >= 0 && pq->arr[parent].academicPerformance < pq->arr[index].academicPerformance) {
    largest = parent;
  }

  // Swap elements if a child has higher academic performance
  if (largest != index) {
    swap(&pq->arr[index], &pq->arr[largest]);
    heapifyUp(pq, largest);
  }
}

// Function to maintain the max-heap property by bubbling down elements
void heapifyDown(struct PriorityQueue* pq, int index) {
  int largest = index;
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  // Find the largest child (max-heap)
  if (left < pq->size && pq->arr[left].academicPerformance > pq->arr[largest].academicPerformance) {
    largest = left;
  }
  if (right < pq->size && pq->arr[right].academicPerformance > pq->arr[largest].academicPerformance) {
    largest = right;
  }

  // Swap elements if a child has higher academic performance
  if (largest != index) {
    swap(&pq->arr[index], &pq->arr[largest]);
    heapifyDown(pq, largest);
  }
}

// Function to insert a student enrollment request
void insertRequest(struct PriorityQueue* pq, int rollNumber, float academicPerformance) {
  if (pq->size == MAX_SIZE) {
    printf("Error: Priority queue is full.\n");
    return;
  }

  pq->arr[pq->size].rollNumber = rollNumber;
  pq->arr[pq->size].academicPerformance = academicPerformance;
  heapifyUp(pq, pq->size); // Maintain max-heap property
  pq->size++;
  printf("Student enrollment request with roll number %d inserted.\n", rollNumber);
}

// Function to extract the highest priority request (student with highest academic performance)
struct Request extractHighestPriorityRequest(struct PriorityQueue* pq) {
  if (pq->size == 0) {
    printf("Error: Priority queue is empty.\n");
    struct Request emptyRequest = {0, 0.0};
    return emptyRequest;
  }

  struct Request highestPriorityRequest = pq->arr[0];
  pq->arr[0] = pq->arr[pq->size - 1];
  pq->size--;
  heapifyDown(pq, 0); // Maintain max-heap property after extraction
  return highestPriorityRequest;
}

// Function to update the priority (academic performance) of a request
void updatePriority(struct PriorityQueue* pq, int rollNumber, float newAcademicPerformance) {
  for (int i = 0; i < pq->size; i++) {
    if (pq->arr[i].rollNumber == rollNumber) {
      pq->arr[i].academicPerformance = newAcademicPerformance;
      int parent = (i - 1) / 2;

      // Maintain max-heap property after update (may need bubbling up or down)
      if (newAcademicPerformance > pq->arr[parent].academicPerformance) {
        heapifyUp(pq, i); // Bubble up if new performance is higher
      } else {
        heapifyDown(pq, i); // Bubble down if new performance is lower
      }
      printf("Priority updated for student with roll number %d.\n", rollNumber);
      return;
    }
  }
  printf("Student with roll number %d not found in the priority queue.\n", rollNumber);
}

// Step 3: Scenario-based Testing
int main() {
  struct PriorityQueue* pq = createPriorityQueue();

  // Insert student enrollment requests
  insertRequest(pq, 1, 92.5);
  insertRequest(pq, 2, 88.0);
  insertRequest(pq, 3, 95.0);
  insertRequest(pq, 4, 90.2);

  // Extract and process highest priority requests
  struct Request highestPriorityRequest = extractHighestPriorityRequest(pq);
  printf("Highest priority request: Roll Number: %d, Academic Performance: %.2f\n",
         highestPriorityRequest.rollNumber, highestPriorityRequest.academicPerformance);
  highestPriorityRequest = extractHighestPriorityRequest(pq);
  printf("Highest priority request: Roll Number: %d, Academic Performance: %.2f\n",
         highestPriorityRequest.rollNumber, highestPriorityRequest.academicPerformance);

  // Update priority for a student
  updatePriority(pq, 2, 94.0);

  // Extract remaining requests
  while (pq->size > 0) {
    highestPriorityRequest = extractHighestPriorityRequest(pq);
    printf("Highest priority request: Roll Number: %d, Academic Performance: %.2f\n",
           highestPriorityRequest.rollNumber, highestPriorityRequest.academicPerformance);
  }
  free(pq);
  return 0;
}
