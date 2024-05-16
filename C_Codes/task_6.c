// Task No. 6: Sorting

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define student structure
typedef struct Student {
  int rollNumber;
  char name[50];
  float marks;
} Student;

// Generate random student records
void generateRandomStudents(Student students[], int size) {
  for (int i = 0; i < size; i++) {
    students[i].rollNumber = i + 1;
    sprintf(students[i].name, "Student%d", i + 1);
    students[i].marks = (float)rand() / RAND_MAX * 100.0;
  }
}

// Swap two students
void swap(Student* a, Student* b) {
  Student temp = *a;
  *a = *b;
  *b = temp;
}

// Bubble Sort
void bubbleSort(Student students[], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (students[j].rollNumber > students[j + 1].rollNumber) {
        swap(&students[j], &students[j + 1]);
      }
    }
  }
}

// Insertion Sort
void insertionSort(Student students[], int size) {
  for (int i = 1; i < size; i++) {
    Student key = students[i];
    int j = i - 1;
    while (j >= 0 && students[j].rollNumber > key.rollNumber) {
      students[j + 1] = students[j];
      j--;
    }
    students[j + 1] = key;
  }
}

// Quick Sort partition
int partition(Student students[], int low, int high) {
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
void quickSort(Student students[], int low, int high) {
  if (low < high) {
    int pi = partition(students, low, high);
    quickSort(students, low, pi - 1);
    quickSort(students, pi + 1, high);
  }
}

// Display student records
void displayStudents(Student students[], int size) {
  printf("Student Records:\n");
  for (int i = 0; i < size; i++) {
    printf("Roll Number: %d, Name: %s, Marks: %.2f\n", students[i].rollNumber, students[i].name, students[i].marks);
  }
}

int main() {
  int size = 1000;
  Student* students = (Student*)malloc(size * sizeof(Student));

  // Generate random student records
  srand(time(NULL));
  generateRandomStudents(students, size);

  // Sort using different algorithms
  clock_t start, end;

  // Bubble Sort
  start = clock();
  bubbleSort(students, size);
  end = clock();
  printf("Bubble Sort Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  // Reset student records
  generateRandomStudents(students, size);

  // Insertion Sort
  start = clock();
  insertionSort(students, size);
  end = clock();
  printf("Insertion Sort Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  // Reset student records
  generateRandomStudents(students, size);

  // Quick Sort
  start = clock();
  quickSort(students, 0, size - 1);
  end = clock();
  printf("Quick Sort Time: %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

  // Display sorted student records
    displayStudents(students, size);

    free(students);
    return 0;
}
