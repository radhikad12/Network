#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int routeId;
    struct Node* next;
} Node;

typedef struct {
    int stop;
    int depth;
} QueueNode;

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    if (source == target) {
        return 0;
    }

    int maxStop = 0;
    for (int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            if (routes[i][j] > maxStop) {
                maxStop = routes[i][j];
            }
        }
    }

    if (source > maxStop || target > maxStop) {
        return -1;
    }

    Node** stopToRoutes = (Node**)calloc(maxStop + 1, sizeof(Node*));
    for (int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            int stop = routes[i][j];
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->routeId = i;
            newNode->next = stopToRoutes[stop];
            stopToRoutes[stop] = newNode;
        }
    }

    bool* visitedStops = (bool*)calloc(maxStop + 1, sizeof(bool));
    bool* visitedRoutes = (bool*)calloc(routesSize, sizeof(bool));

    QueueNode* queue = (QueueNode*)malloc((maxStop + 1) * sizeof(QueueNode));
    int head = 0, tail = 0;

    queue[tail++] = (QueueNode){source, 0};
    visitedStops[source] = true;

    int minBuses = -1;

    while (head < tail) {
        QueueNode current = queue[head++];
        int currStop = current.stop;
        int currDepth = current.depth;

        if (currStop == target) {
            minBuses = currDepth;
            break;
        }

        Node* currNode = stopToRoutes[currStop];
        while (currNode != NULL) {
            int rId = currNode->routeId;

            if (!visitedRoutes[rId]) {
                visitedRoutes[rId] = true;

                for (int j = 0; j < routesColSize[rId]; j++) {
                    int nextStop = routes[rId][j];
                    if (!visitedStops[nextStop]) {
                        visitedStops[nextStop] = true;
                        queue[tail++] = (QueueNode){nextStop, currDepth + 1};
                    }
                }
            }
            currNode = currNode->next;
        }
    }

    for (int i = 0; i <= maxStop; i++) {
        Node* curr = stopToRoutes[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(stopToRoutes);
    free(visitedStops);
    free(visitedRoutes);
    free(queue);

    return minBuses;
}
