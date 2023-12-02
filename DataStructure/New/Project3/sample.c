#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// #define V 5 // 假设顶点的数量

// 定义邻接表节点
typedef struct AdjListNode {
  int dest;
  int weight;
  struct AdjListNode *next;
} AdjListNode;

// 定义邻接表
typedef struct AdjList {
  AdjListNode *head;
} AdjList;

// 定义图
typedef struct Graph {
  int V;
  AdjList *array;
} Graph;

// 定义堆节点
typedef struct MinHeapNode {
  int v;
  int dist;
} MinHeapNode;

// 定义最小堆
typedef struct MinHeap {
  int size;
  int capacity;
  int *pos;
  MinHeapNode **array;
} MinHeap;

// 函数原型
MinHeapNode *newMinHeapNode(int v, int dist);
MinHeap *createMinHeap(int capacity);
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b);
void minHeapify(MinHeap *minHeap, int idx);
int isEmpty(MinHeap *minHeap);
MinHeapNode *extractMin(MinHeap *minHeap);
void decreaseKey(MinHeap *minHeap, int v, int dist);
int isInMinHeap(MinHeap *minHeap, int v);
Graph *createGraph(int V);
void addEdge(Graph *graph, int src, int dest, int weight);
void dijkstra(Graph *graph, int src);

// 实现函数
// 创建一个新的堆节点
MinHeapNode *newMinHeapNode(int v, int dist) {
  MinHeapNode *minHeapNode = (MinHeapNode *)malloc(sizeof(MinHeapNode));
  minHeapNode->v = v;
  minHeapNode->dist = dist;
  return minHeapNode;
}

// 创建一个最小堆
MinHeap *createMinHeap(int capacity) {
  MinHeap *minHeap = (MinHeap *)malloc(sizeof(MinHeap));
  minHeap->pos = (int *)malloc(capacity * sizeof(int));
  minHeap->size = 0;
  minHeap->capacity = capacity;
  minHeap->array = (MinHeapNode **)malloc(capacity * sizeof(MinHeapNode *));
  return minHeap;
}

// 交换两个堆节点
void swapMinHeapNode(MinHeapNode **a, MinHeapNode **b) {
  MinHeapNode *t = *a;
  *a = *b;
  *b = t;
}

// 堆化函数
void minHeapify(MinHeap *minHeap, int idx) {
  int smallest, left, right;
  smallest = idx;
  left = 2 * idx + 1;
  right = 2 * idx + 2;

  if (left < minHeap->size &&
      minHeap->array[left]->dist < minHeap->array[smallest]->dist)
    smallest = left;

  if (right < minHeap->size &&
      minHeap->array[right]->dist < minHeap->array[smallest]->dist)
    smallest = right;

  if (smallest != idx) {
    // 交换节点并继续堆化
    MinHeapNode *smallestNode = minHeap->array[smallest];
    MinHeapNode *idxNode = minHeap->array[idx];

    // 交换位置
    minHeap->pos[smallestNode->v] = idx;
    minHeap->pos[idxNode->v] = smallest;

    swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

    minHeapify(minHeap, smallest);
  }
}

// 检查堆是否为空
int isEmpty(MinHeap *minHeap) { return minHeap->size == 0; }

// 从堆中提取最小节点
MinHeapNode *extractMin(MinHeap *minHeap) {
  if (isEmpty(minHeap))
    return NULL;

  // 存储根节点
  MinHeapNode *root = minHeap->array[0];

  // 替换根节点为最后一个节点
  MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
  minHeap->array[0] = lastNode;

  // 更新位置
  minHeap->pos[root->v] = minHeap->size - 1;
  minHeap->pos[lastNode->v] = 0;

  // 减少堆大小并堆化根节点
  --minHeap->size;
  minHeapify(minHeap, 0);

  return root;
}

// 函数用于减小v的距离值
void decreaseKey(MinHeap *minHeap, int v, int dist) {
  // 获取v在堆数组中的索引
  int i = minHeap->pos[v];

  // 获取节点并更新其距离值
  minHeap->array[i]->dist = dist;

  // 向上移动，直到满足堆属性
  while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
    // 交换节点和更新位置
    minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
    minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
    swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

    // 移动到父节点
    i = (i - 1) / 2;
  }
}

// 检查v是否在堆中
int isInMinHeap(MinHeap *minHeap, int v) {
  if (minHeap->pos[v] < minHeap->size)
    return 1;
  return 0;
}

// 创建一个新的邻接表节点
AdjListNode *newAdjListNode(int dest, int weight) {
  AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
  newNode->dest = dest;
  newNode->weight = weight;
  newNode->next = NULL;
  return newNode;
}

// 创建一个图
Graph *createGraph(int V) {
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->V = V;

  // 创建一个数组，包含邻接表
  graph->array = (AdjList *)malloc(V * sizeof(AdjList));

  // 初始化每个邻接表为空链表
  for (int i = 0; i < V; ++i)
    graph->array[i].head = NULL;

  return graph;
}

// 添加边到图
void addEdge(Graph *graph, int src, int dest, int weight) {
  // 添加边从src到dest
  AdjListNode *newNode = newAdjListNode(dest, weight);
  newNode->next = graph->array[src].head;
  graph->array[src].head = newNode;

  // 由于图是无向的，添加边从dest到src
  newNode = newAdjListNode(src, weight);
  newNode->next = graph->array[dest].head;
  graph->array[dest].head = newNode;
}

// Dijkstra算法实现
void dijkstra(Graph *graph, int src) {
  int V = graph->V; // 获取顶点数
  int dist[V];      // 距离数组

  // 创建一个最小堆
  MinHeap *minHeap = createMinHeap(V);

  // 初始化最小堆
  for (int v = 0; v < V; ++v) {
    dist[v] = INT_MAX;
    minHeap->array[v] = newMinHeapNode(v, dist[v]);
    minHeap->pos[v] = v;
  }

  // 将源顶点的距离值设为0，并更新它在最小堆中
  minHeap->array[src] = newMinHeapNode(src, dist[src]);
  minHeap->pos[src] = src;
  dist[src] = 0;
  decreaseKey(minHeap, src, dist[src]);

  // 初始化最小堆的大小为等于V
  minHeap->size = V;

  // 当最小堆非空时
  while (!isEmpty(minHeap)) {
    // 提取最小距离顶点
    MinHeapNode *minHeapNode = extractMin(minHeap);
    int u = minHeapNode->v; // 存储顶点编号

    // 遍历所有邻接顶点
    AdjListNode *pCrawl = graph->array[u].head;
    while (pCrawl != NULL) {
      int v = pCrawl->dest;

      // 如果最短路径可以更新
      if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX &&
          pCrawl->weight + dist[u] < dist[v]) {
        dist[v] = dist[u] + pCrawl->weight;

        // 更新距离值在最小堆中
        decreaseKey(minHeap, v, dist[v]);
      }
      pCrawl = pCrawl->next;
    }
  }

  // 打印最短路径数组
  printf("Vertex   Distance from Source\n");
  for (int i = 0; i < V; ++i)
    printf("%d \t\t %d\n", i, dist[i]);
}

// 主函数测试
int main() {
  // 创建图
  Graph *graph = createGraph(5);
  addEdge(graph, 0, 1, 4);
  addEdge(graph, 0, 7, 8);
  addEdge(graph, 1, 2, 8);
  addEdge(graph, 1, 7, 11);
  addEdge(graph, 2, 3, 7);
  addEdge(graph, 2, 8, 2);
  addEdge(graph, 2, 5, 4);
  addEdge(graph, 3, 4, 9);
  addEdge(graph, 3, 5, 14);
  addEdge(graph, 4, 5, 10);
  addEdge(graph, 5, 6, 2);
  addEdge(graph, 6, 7, 1);
  addEdge(graph, 6, 8, 6);
  addEdge(graph, 7, 8, 7);

  dijkstra(graph, 0);

  return 0;
}
