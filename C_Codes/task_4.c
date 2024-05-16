// Task No. 4: Trees

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Binary Tree Node Structure
struct Node {
  char courseName[50];  // Name of the course
  struct Node* left;    // Pointer to the left child node
  struct Node* right;   // Pointer to the right child node
};

// Function to create a new node
struct Node* createNode(char courseName[]) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  strcpy(newNode->courseName, courseName);  // Copy course name
  newNode->left = NULL;                     // Initialize left child to NULL
  newNode->right = NULL;                    // Initialize right child to NULL
  return newNode;
}

// Function to insert a course into the binary tree
struct Node* insertCourse(struct Node* root, char courseName[]) {
  if (root == NULL) {
    return createNode(courseName);  // Create a new node if tree is empty
  }
  if (strcmp(courseName, root->courseName) < 0) {
    root->left = insertCourse(root->left, courseName);  // Insert left if smaller
  } else if (strcmp(courseName, root->courseName) > 0) {
    root->right = insertCourse(root->right, courseName); // Insert right if larger
  }
  // No duplicates allowed, so return the unchanged root for existing courses
  return root;
}

// Function to create a binary tree of courses (sample)
struct Node* createCourseTree() {
  struct Node* root = NULL;
  root = insertCourse(root, "Web Systems");
  root = insertCourse(root, "Databases");
  root = insertCourse(root, "IT Projects");
  root = insertCourse(root, "Algorithms and Complexity");
  root = insertCourse(root, "Cyber-space Security");
  return root;
}

// In-order traversal (prints courses in sorted order)
void inorderTraversal(struct Node* root) {
  if (root != NULL) {
    inorderTraversal(root->left);
    printf("%s\n", root->courseName);
    inorderTraversal(root->right);
  }
}

// Pre-order traversal (visits root first, then children)
void preorderTraversal(struct Node* root) {
  if (root != NULL) {
    printf("%s\n", root->courseName);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
  }
}

// Post-order traversal (visits leaves first, then parents)
void postorderTraversal(struct Node* root) {
  if (root != NULL) {
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%s\n", root->courseName);
  }
}

int main() {
  struct Node* root = createCourseTree();

  printf("In-order traversal:\n");
  inorderTraversal(root);

  printf("\nPre-order traversal:\n");
  preorderTraversal(root);

  printf("\nPost-order traversal:\n");
  postorderTraversal(root);

  return 0;
}
