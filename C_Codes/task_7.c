// Task No. 7: Hashing

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 997 // Prime number for better hash distribution

// Structure to represent a student
struct Student {
  int rollNumber;
  char name[50];
  float marks;
  struct Student* next;
};

// Hash function to map roll number to index
int hashFunction(int rollNumber) {
  return rollNumber % TABLE_SIZE;
}

// Hash table (array of pointers to student records)
struct Student* hashTable[TABLE_SIZE];

// Initialize the hash table (set all elements to NULL)
void initHashTable() {
  for (int i = 0; i < TABLE_SIZE; i++) {
    hashTable[i] = NULL;
  }
}

// Insert a student record into the hash table
void insertStudent(int rollNumber, char name[], float marks) {
  int index = hashFunction(rollNumber);
  struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
  newStudent->rollNumber = rollNumber;
  strcpy(newStudent->name, name);
  newStudent->marks = marks;
  newStudent->next = NULL;

  // Handle collision (existing student at the same index)
  if (hashTable[index] == NULL) {
    hashTable[index] = newStudent;
  } else {
    struct Student* temp = hashTable[index];
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newStudent;
  }
  printf("Student with roll number %d inserted.\n", rollNumber);
}

// Search for a student record in the hash table
struct Student* searchStudent(int rollNumber) {
  int index = hashFunction(rollNumber);
  struct Student* temp = hashTable[index];
  while (temp != NULL) {
    if (temp->rollNumber == rollNumber) {
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

// Delete a student record from the hash table
void deleteStudent(int rollNumber) {
  int index = hashFunction(rollNumber);
  struct Student* temp = hashTable[index];
  struct Student* prev = NULL;

  // Check for student at the head of the linked list
  if (temp != NULL && temp->rollNumber == rollNumber) {
    hashTable[index] = temp->next;
    free(temp);
    printf("Student with roll number %d deleted.\n", rollNumber);
    return;
  }

  // Traverse the linked list searching for the student
  while (temp != NULL && temp->rollNumber != rollNumber) {
    prev = temp;
    temp = temp->next;
  }

  // Student not found
  if (temp == NULL) {
    printf("Student with roll number %d not found.\n", rollNumber);
    return;
  }

  // Remove the student from the linked list
  prev->next = temp->next;
  free(temp);
  printf("Student with roll number %d deleted.\n", rollNumber);
}

int main() {
  initHashTable();

  // Insert student records
  insertStudent(1, "John", 85.5);
  insertStudent(2, "Beth", 92.0);
  insertStudent(3, "Rip", 78.2);
  insertStudent(998, "Lloyd", 90.0);

  // Search for a student
  struct Student* foundStudent = searchStudent(2);
  if (foundStudent != NULL) {
    printf("Found student: Roll Number: %d, Name: %s, Marks: %.2f\n",
           foundStudent->rollNumber, foundStudent->name, foundStudent->marks);
  } else {
    printf("Student not found.\n");
  }

  // Delete a student
  deleteStudent(3);

    // Search for a deleted student
    foundStudent = searchStudent(3);
    if (foundStudent == NULL) {
    printf("Student with roll number 3 deleted successfully.\n");
    }

    return 0;
}
