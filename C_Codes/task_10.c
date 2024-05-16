// Task No. 10: Multiway Search Trees

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Define the order (maximum number of keys) for the B-tree
#define ORDER 3

// Structure to represent a course
typedef struct Course {
  int code;
  char title[50];
} Course;

// Structure to represent a B-tree node
typedef struct BTreeNode {
  Course courses[ORDER - 1];  // Array of courses in the node
  struct BTreeNode* children[ORDER];  // Array of child nodes
  int num_keys;                   // Number of keys (courses) in the node
  bool isLeaf;                   // Flag indicating whether the node is a leaf (no children)
} BTreeNode;

// Function to create a new B-tree node
BTreeNode* createNode(bool leaf) {
  BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
  if (newNode == NULL) {
    printf("Memory allocation failed!\n");
    exit(EXIT_FAILURE);
  }
  newNode->num_keys = 0;
  newNode->isLeaf = leaf;
  return newNode;
}

// Function prototypes for B-tree operations (implemented below)
void insert(BTreeNode** root, Course course);
void insertNonFull(BTreeNode* node, Course course);
void splitChild(BTreeNode* parent, int i, BTreeNode* child);
bool search(BTreeNode* root, int code);
void freeBTree(BTreeNode* root);

void freeBTree(BTreeNode* root) {
    if (root) {
        if (!root->isLeaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                freeBTree(root->children[i]);
            }
        }
        free(root);
    }
}


// Function to search for a course in the B-tree
bool search(BTreeNode* root, int code) {
  int i = 0;
  // Traverse the tree until the appropriate leaf is found
  while (i < root->num_keys && code > root->courses[i].code) {
    i++;
  }
  // Check if the course code is found in the current node
  if (i < root->num_keys && code == root->courses[i].code) {
    return true;
  }
  // If not found in a leaf node, continue searching in the appropriate child
  if (root->isLeaf) {
    return false;
  }
  return search(root->children[i], code);
}

// Function to insert a course into the B-tree
void insert(BTreeNode** root, Course course) {
  // If the root is full, split it and then insert the course
  if ((*root)->num_keys == ORDER - 1) {
    BTreeNode* newRoot = createNode(false);
    newRoot->children[0] = *root;
    splitChild(newRoot, 0, *root);
    int i = 0;
    // Decide which child to insert into based on the course code
    if (newRoot->courses[0].code < course.code) {
      i++;
    }
    insertNonFull(newRoot->children[i], course);
    *root = newRoot;
  } else {
    // If there's space in the root, insert directly
    insertNonFull(*root, course);
  }
}

// Function to insert a course into a non-full B-tree node
void insertNonFull(BTreeNode* node, Course course) {
  int i = node->num_keys - 1;
  // Shift existing courses if needed to make space for the new one
  if (node->isLeaf) {
    while (i >= 0 && course.code < node->courses[i].code) {
      node->courses[i + 1] = node->courses[i];
      i--;
    }
    node->courses[i + 1] = course;
    node->num_keys++;
  } else {
    // Find the appropriate child to insert into
    while (i >= 0 && course.code < node->courses[i].code) {
      i--;
    }
    i++;
    // If the child is full, split it before insertion
    if (node->children[i]->num_keys == ORDER - 1) {
      splitChild(node, i, node->children[i]);
      // Decide which child to insert into after splitting
    if (course.code > node->courses[i].code) {
      i++;
    }
  }
    insertNonFull(node->children[i], course);
  }
}

// Function to split a child node of a B-tree node
void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
  BTreeNode* newNode = createNode(child->isLeaf);
  // Move half of the child's elements to the new node

  newNode->num_keys = ORDER / 2 - 1;
  for (int j = 0; j < ORDER / 2 - 1; j++) {
    newNode->courses[j] = child->courses[j + ORDER / 2];
  }
  // If the child is not a leaf, move pointers to child nodes as well
  if (!child->isLeaf) {
    for (int j = 0; j < ORDER / 2; j++) {
      newNode->children[j] = child->children[j + ORDER / 2];
    }
  }
  child->num_keys = ORDER / 2 - 1;

  // Adjust parent pointers and courses to accommodate the split child
  for (int j = parent->num_keys; j >= i + 1; j--) {
    parent->children[j + 1] = parent->children[j];
  }
  parent->children[i + 1] = newNode;
  for (int j = parent->num_keys - 1; j >= i; j--) {
    parent->courses[j + 1] = parent->courses[j];
  }
  parent->courses[i] = child->courses[ORDER / 2 - 1];
  parent->num_keys++;
}

// Function to free memory allocated for B-tree nodes during deletion (not shown here)
void freeBTree(BTreeNode* root);

// Function to test the B-tree with different course structures
void testBTree() {
  BTreeNode* root = createNode(true);

  // Insert some courses
  Course c1 = {101, "Web Systems"};
  insert(&root, c1);
  Course c2 = {202, "Databases"};
  insert(&root, c2);
  Course c3 = {303, "IT Projects"};
  insert(&root, c3);
  Course c4 = {404, "Algorithms and Complexity"};
  insert(&root, c4);
  Course c5 = {505, "Cyber-space Security"};
  insert(&root, c5);

  // Search for courses
  int searchCode = 303;
  if (search(root, searchCode)) {
    printf("Course with code %d found.\n", searchCode);
  } else {
    printf("Course with code %d not found.\n", searchCode);
  }

  int searchCode2 = 578;
  if (search(root, searchCode2)) {
    printf("Course with code %d found.\n", searchCode2);
  } else {
    printf("Course with code %d not found.\n", searchCode2);
  }

  // Free memory allocated for the B-tree (not shown here)
  freeBTree(root);
}

int main() {
  // Test the B-tree
  testBTree();
  return 0;
}
