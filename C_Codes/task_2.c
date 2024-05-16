// Task No. 2: Stacks and Queues

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

// Stack Structure and Functions
struct Stack {
  int arr[MAX_SIZE];  // Array to store stack elements
  int top;           // Index of the top element
};

void initStack(struct Stack* stack) {
  stack->top = -1;  // Initialize top to -1 for empty stack
}

int isEmpty(struct Stack* stack) {
  return stack->top == -1;  // Check if top is -1 (empty)
}

int isFull(struct Stack* stack) {
  return stack->top == MAX_SIZE - 1;  // Check if top is at max size (full)
}

void push(struct Stack* stack, int item) {
  if (isFull(stack)) {
    printf("Error: Stack overflow.\n");
    return;
  }
  stack->arr[++stack->top] = item;  // Increment top, then assign item
  printf("%d pushed to stack.\n", item);
}

int pop(struct Stack* stack) {
  if (isEmpty(stack)) {
    printf("Error: Stack underflow.\n");
    return -1;
  }
  int item = stack->arr[stack->top--];  // Get item, then decrement top
  printf("%d popped from stack.\n", item);
  return item;
}

// Queue Structure and Functions
struct Queue {
  int arr[MAX_SIZE];  // Array to store queue elements
  int front, rear;    // Indices for front and rear elements
};

void initQueue(struct Queue* queue) {
  queue->front = 0;
  queue->rear = -1;  // Initialize rear to -1 for empty queue
}

int isQueueEmpty(struct Queue* queue) {
  return queue->front > queue->rear;  // Check if front is ahead of rear (empty)
}

int isQueueFull(struct Queue* queue) {
  return queue->rear == MAX_SIZE - 1;  // Check if rear is at max size (full)
}

void enqueue(struct Queue* queue, int item) {
  if (isQueueFull(queue)) {
    printf("Error: Queue overflow.\n");
    return;
  }
  queue->arr[++queue->rear] = item;  // Increment rear, then assign item
  printf("%d enqueued to queue.\n", item);
}

int dequeue(struct Queue* queue) {
  if (isQueueEmpty(queue)) {
    printf("Error: Queue underflow.\n");
    return -1;
  }
  int item = queue->arr[queue->front++];  // Get item, then increment front
  printf("%d dequeued from queue.\n", item);
  return item;
}

int main() {
  struct Stack stack;
  struct Queue queue;

  initStack(&stack);
  initQueue(&queue);

  // Simulate tasks (e.g., admissions) using stack (LIFO)
  push(&stack, 1);
  push(&stack, 2);
  push(&stack, 3);

  // Simulate tasks (e.g., enrollments) using queue (FIFO)
  enqueue(&queue, 10);
  enqueue(&queue, 20);
  enqueue(&queue, 30);

  // Process tasks
  pop(&stack);
  dequeue(&queue);
  pop(&stack);
  dequeue(&queue);
  pop(&stack);
  dequeue(&queue);

  return 0;
}
