#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1003
#define MAX_EDGES 100005

// Structure to represent an edge in the graph
typedef struct {
  int vertex; // Destination vertex of the edge
  int weight; // Weight of the edge
} Edge;

Edge graph[MAX_VERTICES]
          [MAX_VERTICES];    // Graph represented as an adjacency matrix
int distances[MAX_VERTICES]; // Array to store shortest distance from source
bool shortestPathSet[MAX_VERTICES]; // Boolean array to track vertices included
                                    // in shortest path
int edgeCount[MAX_VERTICES];        // Count of edges for each vertex

// Function to perform Dijkstra's algorithm for a given source vertex
void dijkstra(int source, int vertices) {
  for (int i = 1; i <= vertices; i++) {
    distances[i] = INT_MAX; // Initialize distances to maximum value
    shortestPathSet[i] =
        false; // Mark all vertices as not included in shortest path yet
  }

  distances[source] = 0; // Distance of source vertex from itself is always 0

  // Find shortest path for all vertices
  for (int count = 0; count < vertices - 1; count++) {
    int minDistance = INT_MAX, minIndex;

    // Pick the minimum distance vertex from the set of vertices not yet
    // processed
    for (int v = 1; v <= vertices; v++) {
      if (!shortestPathSet[v] && distances[v] <= minDistance) {
        minDistance = distances[v], minIndex = v;
      }
    }

    // Mark the picked vertex as processed
    shortestPathSet[minIndex] = true;

    // Update distance value of the adjacent vertices of the picked vertex
    for (int i = 0; i < edgeCount[minIndex]; i++) {
      Edge e = graph[minIndex][i];
      if (!shortestPathSet[e.vertex] && distances[minIndex] != INT_MAX &&
          distances[minIndex] + e.weight < distances[e.vertex]) {
        distances[e.vertex] = distances[minIndex] + e.weight;
      }
    }
  }
}

// Function to check if a given sequence is a Dijkstra sequence
bool isDijkstraSequence(int vertices, int sequence[]) {
  for (int i = 1; i <= vertices; i++) {
    if (distances[sequence[i - 1]] != INT_MAX) {
      for (int j = i; j < vertices; j++) {
        if (distances[sequence[j]] < distances[sequence[i - 1]]) {
          return false; // If any vertex has a shorter distance, sequence is not
                        // valid
        }
      }
    } else {
      return false; // If any vertex is unreachable, sequence is not valid
    }
  }
  return true; // If all checks pass, sequence is valid
}

int main() {
  int vertices, edges;
  scanf("%d %d", &vertices, &edges);

  // Reading edges and constructing the graph
  for (int i = 0; i < edges; i++) {
    int src, dest, weight;
    scanf("%d %d %d", &src, &dest, &weight);
    graph[src][edgeCount[src]].vertex = dest;
    graph[src][edgeCount[src]++].weight = weight;
    // Assuming undirected graph
    graph[dest][edgeCount[dest]].vertex = src;
    graph[dest][edgeCount[dest]++].weight = weight;
  }

  int queries;
  scanf("%d", &queries);

  // Processing each query
  while (queries--) {
    int sequence[MAX_VERTICES];
    for (int i = 0; i < vertices; i++) {
      scanf("%d", &sequence[i]);
    }
    dijkstra(sequence[0], vertices);
    printf("%s\n", isDijkstraSequence(vertices, sequence) ? "Yes" : "No");
  }

  return 0;
}
