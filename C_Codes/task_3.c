// Task No. 3: Linked Lists

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked List Node Structure
struct Node {
  char name[50];  // Name of the club member
  struct Node* next;  // Pointer to the next node in the list
};

// Function to create a new node
struct Node* createNode(char name[]) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  strcpy(newNode->name, name);  // Copy name to the new node
  newNode->next = NULL;        // Set next pointer to NULL (end of list)
  return newNode;
}

// Function to add a member to the linked list
void addMember(struct Node** head, char name[]) {
  struct Node* newNode = createNode(name);
  if (*head == NULL) {
    *head = newNode;  // Set head to the new node (empty list)
  } else {
    struct Node* temp = *head;
    while (temp->next != NULL) {
      temp = temp->next;  // Traverse to the last node
    }
    temp->next = newNode;  // Add the new node at the end
  }
  printf("Member '%s' added to the list.\n", name);
}

// Function to delete a member from the linked list
void deleteMember(struct Node** head, char name[]) {
  struct Node* temp = *head, *prev = NULL;
  if (temp != NULL && strcmp(temp->name, name) == 0) {
    *head = temp->next;  // Update head if deleting the first node
    free(temp);
    printf("Member '%s' deleted from the list.\n", name);
    return;
  }
  while (temp != NULL && strcmp(temp->name, name) != 0) {
    prev = temp;
    temp = temp->next;  // Traverse and find the node to delete
  }
  if (temp == NULL) {
    printf("Member '%s' not found in the list.\n", name);
    return;
  }
  prev->next = temp->next;  // Bypass the deleted node
  free(temp);
  printf("Member '%s' deleted from the list.\n", name);
}

// Function to display all members in the list
void displayMembers(struct Node* head) {
  struct Node* temp = head;
  if (temp == NULL) {
    printf("The list is empty.\n");
    return;
  }
  printf("List of members:\n");
  while (temp != NULL) {
    printf("%s\n", temp->name);
    temp = temp->next;  // Traverse and print each member
  }
}

int main() {
  struct Node* head = NULL;

  // Add members to the list
  addMember(&head, "John");
  addMember(&head, "Beth");
  addMember(&head, "Rip");

  // Display members in the list
  displayMembers(head);

  // Delete a member from the list
  deleteMember(&head, "Beth");

  // Display updated list
  displayMembers(head);

  return 0;
}
