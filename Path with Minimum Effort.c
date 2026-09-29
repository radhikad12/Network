#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int r, c, effort;
} Cell;

void minHeapify(Cell* heap, int size, int idx, int** pos, int cols) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left].effort < heap[smallest].effort) smallest = left;
    if (right < size && heap[right].effort < heap[smallest].effort) smallest = right;

    if (smallest != idx) {
        pos[heap[idx].r][heap[idx].c] = smallest;
        pos[heap[smallest].r][heap[smallest].c] = idx;
        Cell temp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = temp;
        minHeapify(heap, size, smallest, pos, cols);
    }
}

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int rows = heightsSize;
    int cols = heightsColSize[0];

    int** effort = (int**)malloc(rows * sizeof(int*));
    int** pos = (int**)malloc(rows * sizeof(int*));
    Cell* heap = (Cell*)malloc(rows * cols * sizeof(Cell));

    int count = 0;
    for (int i = 0; i < rows; i++) {
        effort[i] = (int*)malloc(cols * sizeof(int));
        pos[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            effort[i][j] = INT_MAX;
            pos[i][j] = count;
            heap[count] = (Cell){i, j, INT_MAX};
            count++;
        }
    }

    effort[0][0] = 0;
    heap[pos[0][0]].effort = 0;

    int idx = pos[0][0];
    while (idx > 0 && heap[idx].effort < heap[(idx - 1) / 2].effort) {
        pos[heap[idx].r][heap[idx].c] = (idx - 1) / 2;
        pos[heap[(idx - 1) / 2].r][heap[(idx - 1) / 2].c] = idx;
        Cell temp = heap[idx];
        heap[idx] = heap[(idx - 1) / 2];
        heap[(idx - 1) / 2] = temp;
        idx = (idx - 1) / 2;
    }

    int heapSize = rows * cols;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (heapSize > 0) {
        Cell root = heap[0];
        int r = root.r;
        int c = root.c;

        if (r == rows - 1 && c == cols - 1) {
            break;
        }

        pos[r][c] = -1;
        heapSize--;

        if (heapSize > 0) {
            heap[0] = heap[heapSize];
            pos[heap[0].r][heap[0].c] = 0;
            minHeapify(heap, heapSize, 0, pos, cols);
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && pos[nr][nc] != -1) {
                int currentEffort = abs(heights[r][c] - heights[nr][nc]);
                int maxEffort = currentEffort > effort[r][c] ? currentEffort : effort[r][c];

                if (maxEffort < effort[nr][nc]) {
                    effort[nr][nc] = maxEffort;
                    heap[pos[nr][nc]].effort = maxEffort;

                    int cIdx = pos[nr][nc];
                    while (cIdx > 0 && heap[cIdx].effort < heap[(cIdx - 1) / 2].effort) {
                        pos[heap[cIdx].r][heap[cIdx].c] = (cIdx - 1) / 2;
                        pos[heap[(cIdx - 1) / 2].r][heap[(cIdx - 1) / 2].c] = cIdx;
                        Cell temp = heap[cIdx];
                        heap[cIdx] = heap[(cIdx - 1) / 2];
                        heap[(cIdx - 1) / 2] = temp;
                        cIdx = (cIdx - 1) / 2;
                    }
                }
            }
        }
    }

    int result = effort[rows - 1][cols - 1];

    for (int i = 0; i < rows; i++) {
        free(effort[i]);
        free(pos[i]);
    }
    free(effort);
    free(pos);
    free(heap);

    return result;
}
