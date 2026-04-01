#include <stdio.h>
#include <stdbool.h>

#define N 7
#define COLORS 3

char *states[] = {"WA","NT","Q","SA","NSW","V","T"};
char *colorNames[] = {"", "Red", "Green", "Blue"};  // index 1-based

int graph[N][N] = {
    {0,1,0,1,0,0,0}, // WA
    {1,0,1,1,0,0,0}, // NT
    {0,1,0,1,1,0,0}, // Q
    {1,1,1,0,1,1,0}, // SA
    {0,0,1,1,0,1,0}, // NSW
    {0,0,0,1,1,0,0}, // V
    {0,0,0,0,0,0,0}  // T
};

int color[N] = {0}; // initialize safely

// Check if color can be assigned
bool isSafe(int node, int c) {
    for (int i = 0; i < N; i++) {
        if (graph[node][i] && color[i] == c)
            return false;
    }
    return true;
}

// Backtracking solver
bool solve(int node) {
    // Edge case: all nodes colored
    if (node == N)
        return true;

    // Edge case: invalid node index
    if (node < 0 || node >= N)
        return false;

    for (int c = 1; c <= COLORS; c++) {
        if (isSafe(node, c)) {
            color[node] = c;

            if (solve(node + 1))
                return true;

            // backtrack
            color[node] = 0;
        }
    }

    // Edge case: no color possible
    return false;
}

int main() {

    // Edge case: empty graph
    if (N == 0) {
        printf("No states to color.\n");
        return 0;
    }

    if (solve(0)) {
        printf("Australia Map Coloring Solution:\n");
        for (int i = 0; i < N; i++) {
            printf("%s -> %s\n", states[i], colorNames[color[i]]);
        }
    } else {
        printf("No solution exists with %d colors.\n", COLORS);
    }

    return 0;
}
