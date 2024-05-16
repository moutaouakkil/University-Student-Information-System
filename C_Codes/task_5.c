// Task No. 5: Graphs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DEPARTMENTS 10

// Graph Node Structure
struct Node {
  char departmentName[50];  // Name of the department
  int numConnections;       // Number of connected departments
  int connections[MAX_DEPARTMENTS];  // Indices of connected departments
};

// Graph Structure
struct Graph {
  int numDepartments;
  struct Node departments[MAX_DEPARTMENTS];
};

// Function to find the index of a department in the graph
int findDepartmentIndex(struct Graph* graph, char departmentName[]) {
  for (int i = 0; i < graph->numDepartments; i++) {
    if (strcmp(graph->departments[i].departmentName, departmentName) == 0) {
      return i;
    }
  }
  return -1;
}

// Function to create a new graph
struct Graph* createGraph() {
  struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
  graph->numDepartments = 0;
  return graph;
}

// Function to add a department to the graph
void addDepartment(struct Graph* graph, char departmentName[]) {
  if (graph->numDepartments < MAX_DEPARTMENTS) {
    strcpy(graph->departments[graph->numDepartments].departmentName, departmentName);
    graph->departments[graph->numDepartments].numConnections = 0;
    graph->numDepartments++;
    printf("Department '%s' added to the graph.\n", departmentName);
  } else {
    printf("Error: Maximum number of departments reached.\n");
  }
}

// Function to add an edge between two departments
void addEdge(struct Graph* graph, char dept1[], char dept2[]) {
  int index1 = findDepartmentIndex(graph, dept1);
  int index2 = findDepartmentIndex(graph, dept2);
  if (index1 == -1 || index2 == -1) {
    printf("Error: One or both departments not found in the graph.\n");
    return;
  }
  graph->departments[index1].connections[graph->departments[index1].numConnections++] = index2;
  graph->departments[index2].connections[graph->departments[index2].numConnections++] = index1;
  printf("Edge added between '%s' and '%s'.\n", dept1, dept2);
}

// Function to display the relationships between departments
void displayRelationships(struct Graph* graph) {
  for (int i = 0; i < graph->numDepartments; i++) {
    printf("Department '%s' is connected to:\n", graph->departments[i].departmentName);
    for (int j = 0; j < graph->departments[i].numConnections; j++) {
      int connectedDepartmentIndex = graph->departments[i].connections[j];
      printf("- %s\n", graph->departments[connectedDepartmentIndex].departmentName);
    }
    printf("\n");
  }
}

// Depth-First Search (DFS) traversal
void dfs(struct Graph* graph, int startIndex, int visited[]) {
  visited[startIndex] = 1;
  printf("%s ", graph->departments[startIndex].departmentName);
  for (int i = 0; i < graph->departments[startIndex].numConnections; i++) {
    int connectedDepartmentIndex = graph->departments[startIndex].connections[i];
    if (!visited[connectedDepartmentIndex]) {
      dfs(graph, connectedDepartmentIndex, visited);
    }
  }
}

// Breadth-First Search (BFS) traversal
void bfs(struct Graph* graph, int startIndex) {
  int visited[MAX_DEPARTMENTS] = {0};  // Array to store visited departments (initialized to 0)
  int queue[MAX_DEPARTMENTS];          // Queue to manage departments to be visited
  int front = 0, rear = 0;              // Queue front and rear indices

  visited[startIndex] = 1;              // Mark starting department as visited
  queue[rear++] = startIndex;           // Add starting department to the queue

  while (front != rear) {               // Loop until queue is empty
    int currentIndex = queue[front++];  // Get the department at the queue front and remove it
    printf("%s ", graph->departments[currentIndex].departmentName);  // Print current department

    for (int i = 0; i < graph->departments[currentIndex].numConnections; i++) {
      int connectedDepartmentIndex = graph->departments[currentIndex].connections[i];
      if (!visited[connectedDepartmentIndex]) {  // Check if connected department is not visited
        visited[connectedDepartmentIndex] = 1;  // Mark connected department as visited
        queue[rear++] = connectedDepartmentIndex;  // Add connected department to the queue
      }
    }
  }
}

// Main function
int main() {
  struct Graph* graph = createGraph();

  // Add departments to the graph
  addDepartment(graph, "Law");
  addDepartment(graph, "History");
  addDepartment(graph, "Engineering");
  addDepartment(graph, "Business Administration");
  addDepartment(graph, "Accounting");

  // Add edges between departments
  addEdge(graph, "Law", "History");
  addEdge(graph, "Law", "Engineering");
  addEdge(graph, "History", "Engineering");
  addEdge(graph, "Engineering", "Business Administration");
  addEdge(graph, "Business Administration", "Accounting");

  // Display relationships between departments
  printf("\nDepartment Relationships:\n");
  displayRelationships(graph);

  // Perform DFS and BFS traversals
  printf("\nDepth-First Search (DFS) starting from Law:\n");
  int visited[MAX_DEPARTMENTS] = {0};
  dfs(graph, findDepartmentIndex(graph, "Law"), visited);
  printf("\n\nBreadth-First Search (BFS) starting from Law:\n");
  bfs(graph, findDepartmentIndex(graph, "Law"));

  return 0;
}
