#include <stdlib.h>
#include <stdbool.h>

typedef struct Edge {
    int to;
    int cost; 
    struct Edge* next;
} Edge;

int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    Edge** head = (Edge**)calloc(n, sizeof(Edge*));
    
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
        // Original direction u -> v (moving away from 0 costs 1)
        Edge* e1 = (Edge*)malloc(sizeof(Edge));
        e1->to = v;
        e1->cost = 1;
        e1->next = head[u];
        head[u] = e1;
        
        // Reverse direction v -> u (moving towards 0 costs 0)
        Edge* e2 = (Edge*)malloc(sizeof(Edge));
        e2->to = u;
        e2->cost = 0;
        e2->next = head[v];
        head[v] = e2;
    }
    
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    
    queue[rear++] = 0;
    visited[0] = true;
    int changeCount = 0;
    
    while (front < rear) {
        int curr = queue[front++];
        Edge* e = head[curr];
        while (e != NULL) {
            if (!visited[e->to]) {
                visited[e->to] = true;
                changeCount += e->cost;
                queue[rear++] = e->to;
            }
            e = e->next;
        }
    }
    
    for (int i = 0; i < n; i++) {
        Edge* curr = head[i];
        while (curr != NULL) {
            Edge* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(head);
    free(visited);
    free(queue);
    
    return changeCount;
}
