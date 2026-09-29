#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    int node;
    int dist;
} HeapNode;

void minHeapify(HeapNode* heap, int size, int idx, int* pos) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left].dist < heap[smallest].dist) smallest = left;
    if (right < size && heap[right].dist < heap[smallest].dist) smallest = right;

    if (smallest != idx) {
        pos[heap[idx].node] = smallest;
        pos[heap[smallest].node] = idx;
        HeapNode temp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, size, smallest, pos);
    }
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {
    Edge** head = (Edge**)calloc(n + 1, sizeof(Edge*));
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        Edge* e = (Edge*)malloc(sizeof(Edge));
        e->to = v;
        e->weight = w;
        e->next = head[u];
        head[u] = e;
    }

    int* dist = (int*)malloc((n + 1) * sizeof(int));
    int* pos = (int*)malloc((n + 1) * sizeof(int));
    HeapNode* heap = (HeapNode*)malloc(n * sizeof(HeapNode));

    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        pos[i] = i - 1;
        heap[i - 1].node = i;
        heap[i - 1].dist = INT_MAX;
    }

    dist[k] = 0;
    heap[pos[k]].dist = 0;

    // Shift up the source node in the heap
    int idx = pos[k];
    while (idx > 0 && heap[idx].dist < heap[(idx - 1) / 2].dist) {
        pos[heap[idx].node] = (idx - 1) / 2;
        pos[heap[(idx - 1) / 2].node] = idx;
        HeapNode temp = heap[idx];
        heap[idx] = heap[(idx - 1) / 2];
        heap[(idx - 1) / 2] = temp;
        idx = (idx - 1) / 2;
    }

    int heapSize = n;
    while (heapSize > 0) {
        HeapNode root = heap[0];
        int u = root.node;

        pos[u] = -1;
        heapSize--;
        if (heapSize > 0) {
            heap[0] = heap[heapSize];
            pos[heap[0].node] = 0;
            minHeapify(heap, heapSize, 0, pos);
        }

        if (dist[u] == INT_MAX) break;

        Edge* e = head[u];
        while (e != NULL) {
            int v = e->to;
            if (pos[v] != -1 && dist[u] + e->weight < dist[v]) {
                dist[v] = dist[u] + e->weight;
                heap[pos[v]].dist = dist[v];
                
                int cIdx = pos[v];
                while (cIdx > 0 && heap[cIdx].dist < heap[(cIdx - 1) / 2].dist) {
                    pos[heap[cIdx].node] = (cIdx - 1) / 2;
                    pos[heap[(cIdx - 1) / 2].node] = cIdx;
                    HeapNode temp = heap[cIdx];
                    heap[cIdx] = heap[(cIdx - 1) / 2];
                    heap[(cIdx - 1) / 2] = temp;
                    cIdx = (cIdx - 1) / 2;
                }
            }
            e = e->next;
        }
    }

    int maxDelay = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            maxDelay = -1;
            break;
        }
        if (dist[i] > maxDelay) {
            maxDelay = dist[i];
        }
    }

    for (int i = 1; i <= n; i++) {
        Edge* curr = head[i];
        while (curr != NULL) {
            Edge* tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(head);
    free(dist);
    free(pos);
    free(heap);

    return maxDelay;
}
