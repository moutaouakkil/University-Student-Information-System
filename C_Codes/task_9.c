// Task No. 9: Efficient Binary Search Trees

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a balanced binary search tree node
struct Node {
  int rollNumber;
  struct Node* left;
  struct Node* right;
  int height;
};

// Function to get the maximum value between two integers
int max(int a, int b) {
  return (a > b) ? a : b;
}

// Function to get the height of a node (if NULL, height is 0)
int getHeight(struct Node* node) {
  return node ? node->height : 0;
}

// Function to create a new node
struct Node* createNode(int rollNumber) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->rollNumber = rollNumber;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 1;
  return newNode;
}

// Function to perform a left rotation on the tree
struct Node* rotateLeft(struct Node* root) {
  struct Node* newRoot = root->right;
  struct Node* temp = newRoot->left;
  newRoot->left = root;
  root->right = temp;

  // Update heights after rotation
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
  return newRoot;
}

// Function to perform a right rotation on the tree
struct Node* rotateRight(struct Node* root) {
  struct Node* newRoot = root->left;
  struct Node* temp = newRoot->right;
  newRoot->right = root;
  root->left = temp;

  // Update heights after rotation
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
  return newRoot;
}

// Function to get the balance factor of a node
int getBalanceFactor(struct Node* node) {
  if (node == NULL) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a student record into the balanced binary search tree
struct Node* insertStudent(struct Node* root, int rollNumber) {
  if (root == NULL) {
    return createNode(rollNumber);
  }

  if (rollNumber < root->rollNumber) {
    root->left = insertStudent(root->left, rollNumber);
  } else if (rollNumber > root->rollNumber) {
    root->right = insertStudent(root->right, rollNumber);
  } else {
    // Duplicate roll number (do nothing)
    return root;
  }

  // Update height after insertion
  root->height = 1 + max(getHeight(root->left), getHeight(root->right));

  // Balance factor check for rotations
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1 && rollNumber < root->left->rollNumber) {
    return rotateRight(root);
  } else if (balanceFactor < -1 && rollNumber > root->right->rollNumber) {
    return rotateLeft(root);
  } else if (balanceFactor > 1 && rollNumber > root->left->rollNumber) {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  } else if (balanceFactor < -1 && rollNumber < root->right->rollNumber) {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}

// Function to search for a student record in the balanced binary search tree
struct Node* searchStudent(struct Node* root, int rollNumber) {
  if (root == NULL || root->rollNumber == rollNumber) {
    return root;
  }

  if (rollNumber < root->rollNumber) {
    return searchStudent(root->left, rollNumber);
  } else {
    return searchStudent(root->right, rollNumber);
  }
}

// In-order traversal for printing the tree elements
void inorderTraversal(struct Node* root) {
  if (root != NULL) {
    inorderTraversal(root->left);
    printf("%d ", root->rollNumber);
    inorderTraversal(root->right);
  }
}

// Step 3: Thorough Testing
int main() {
  struct Node* root = NULL;

  // Insert student records
  root = insertStudent(root, 10);
  root = insertStudent(root, 20);
  root = insertStudent(root, 30);
  root = insertStudent(root, 40);
  root = insertStudent(root, 50);
  root = insertStudent(root, 25);

  // Search for a student record
  struct Node* foundStudent = searchStudent(root, 30);
  if (foundStudent != NULL) {
    printf("Student with roll number %d found.\n", foundStudent->rollNumber);
  } else {
    printf("Student not found.\n");
  }

  // Print the balanced binary search tree
  printf("Balanced Binary Search Tree: ");
  inorderTraversal(root);
  printf("\n");

  return 0;
}
