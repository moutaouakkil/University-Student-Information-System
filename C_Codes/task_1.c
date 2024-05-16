// Task No. 1: Arrays and Structures

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a student
struct Student {
  int rollNumber;
  char name[50];
  float marks;
};

// Function to generate random student records
void generateRandomStudents(struct Student students[], int numStudents) {
  srand(time(NULL));
  for (int i = 0; i < numStudents; i++) {
    students[i].rollNumber = i + 1;
    sprintf(students[i].name, "Student%d", i + 1);
    students[i].marks = (float)rand() / RAND_MAX * 100.0;
  }
}

// Function to swap two students
void swap(struct Student* a, struct Student* b) {
  struct Student temp = *a;
  *a = *b;
  *b = temp;
}

// Function to perform a sorting algorithm on student records
// Takes a sorting function pointer and its arguments
void sortStudents(struct Student students[], int numStudents, void (*sortFunction)(struct Student[], int)) {
  clock_t start, end;
  start = clock();
  sortFunction(students, numStudents);
  end = clock();
  printf("%s Sort:\n", (*sortFunction == bubbleSort) ? "Bubble" :
         (*sortFunction == insertionSort) ? "Insertion" : "Quick");
  printf("Sorting Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

// Bubble Sort
void bubbleSort(struct Student students[], int numStudents) {
  for (int i = 0; i < numStudents - 1; i++) {
    for (int j = 0; j < numStudents - i - 1; j++) {
      if (students[j].rollNumber > students[j + 1].rollNumber) {
        swap(&students[j], &students[j + 1]);
      }
    }
  }
}

// Insertion Sort
void insertionSort(struct Student students[], int numStudents) {
  for (int i = 1; i < numStudents; i++) {
    struct Student key = students[i];
    int j = i - 1;
    while (j >= 0 && students[j].rollNumber > key.rollNumber) {
      students[j + 1] = students[j];
      j--;
    }
    students[j + 1] = key;
  }
}

// Quick Sort - Partition function
int partition(struct Student students[], int low, int high) {
  int pivot = students[high].rollNumber;
  int i = low - 1;
  for (int j = low; j <= high - 1; j++) {
    if (students[j].rollNumber < pivot) {
      i++;
      swap(&students[i], &students[j]);
    }
  }
  swap(&students[i + 1], &students[high]);
  return i + 1;
}

// Quick Sort
void quickSort(struct Student students[], int low, int high) {
  if (low < high) { // Base Case: If low is greater than or equal to high, the subarray is sorted
    int pi = partition(students, low, high);
    quickSort(students, low, pi - 1);
    quickSort(students, pi + 1, high);
  }
}

// Function to display student records
void displayStudents(struct Student students[], int numStudents) {
  printf("Student Records:\n");
  for (int i = 0; i < numStudents; i++) {
    printf("Roll Number: %d, Name: %s, Marks: %.2f\n", students[i].rollNumber, students[i].name, students[i].marks);
  }
}

int main() {
  int numStudents = 1000;
  struct Student* students = (struct Student*)malloc(numStudents * sizeof(struct Student));

  // Generate random student records
  generateRandomStudents(students, numStudents);

  // Sort using different algorithms
  sortStudents(students, numStudents, bubbleSort);

    // Reset student records for next sort
  generateRandomStudents(students, numStudents);

  printf("Insertion Sort:\n");
  sortStudents(students, numStudents, insertionSort);

  // Reset student records for next sort
  generateRandomStudents(students, numStudents);

  printf("Quick Sort:\n");
  sortStudents(students, numStudents, quickSort);

  // Free the allocated memory
  free(students);

  return 0;
}
