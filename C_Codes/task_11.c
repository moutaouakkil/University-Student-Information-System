// Task No. 11: Digital Search Structures

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

// Structure to represent a trie node
struct TrieNode {
  struct TrieNode* children[ALPHABET_SIZE];  // Array of child nodes (one for each letter)
  bool isEndOfWord;                           // Flag indicating the end of a word
};

// Function to create a new Trie node
struct TrieNode* createNode() {
  struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
  newNode->isEndOfWord = false;
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    newNode->children[i] = NULL;
  }
  return newNode;
}

// Function to insert a student name into the trie
void insertName(struct TrieNode* root, char* name) {
  struct TrieNode* node = root;
  for (int i = 0; name[i] != '\0'; i++) {
    int index = name[i] - 'a'; // Convert character to index (a = 0, b = 1, ...)
    if (node->children[index] == NULL) {
      node->children[index] = createNode();
    }
    node = node->children[index];
  }
  node->isEndOfWord = true; // Mark the end of the inserted word
}

// Function to search for a student name in the trie
bool searchName(struct TrieNode* root, char* name) {
  struct TrieNode* node = root;
  for (int i = 0; name[i] != '\0'; i++) {
    int index = name[i] - 'a';
    if (node->children[index] == NULL) {
      return false; // Character not found in the trie path
    }
    node = node->children[index];
  }
  return node->isEndOfWord; // Check if the current node marks the end of a word
}

// Function to recursively delete a student name from the trie (helper for deleteName)
bool deleteRecursive(struct TrieNode* root, char* name, int level, int length) {
  if (root == NULL) {
    return false; // Reached a null node, deletion failed
  }
  if (level == length) {  // Reached the end of the name
    if (root->isEndOfWord) {
      root->isEndOfWord = false; // Unmark the end of word
    } else {
      return false; // Word not found in the trie
    }
  } else {
    int index = name[level] - 'a';
    if (!deleteRecursive(root->children[index], name, level + 1, length)) {
      return false; // Deletion failed in a child node
    }
  }

  bool hasChildren = false;
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    if (root->children[i] != NULL) {
      hasChildren = true;
      break;
    }
  }
  if (!hasChildren) {  // No children, safe to delete the node
    free(root);
  }
  return true;
}

// Function to delete a student name from the trie
void deleteName(struct TrieNode* root, char* name) {
  deleteRecursive(root, name, 0, strlen(name));
}

int main() {
  struct TrieNode* root = createNode();

  // Insert student names
  insertName(root, "john");
  insertName(root, "beth");
  insertName(root, "rip");
  insertName(root, "lloyd");

  // Search for student names
  printf("Searching for 'john': %s\n", searchName(root, "john") ? "Found" : "Not found");
  printf("Searching for 'beth': %s\n", searchName(root, "beth") ? "Found" : "Not found");
  printf("Searching for 'kayce': %s\n", searchName(root, "kayce") ? "Found" : "Not found");

    // Delete a student name
    deleteName(root, "beth");
    printf("Searching for 'beth' after deletion: %s\n", searchName(root, "beth") ? "Found" : "Not found");

    return 0;
}
