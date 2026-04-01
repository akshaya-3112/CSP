#include <stdio.h>
#include <stdbool.h>

#define N 33
#define COLORS 4

char *districts[N] = {
    "Adilabad","Nirmal","Mancherial","Komaram Bheem",
    "Nizamabad","Kamareddy","Karimnagar","Peddapalli",
    "Jagtial","Rajanna Sircilla","Warangal","Hanamkonda",
    "Mahabubabad","Mulugu","Bhadradri Kothagudem","Khammam",
    "Suryapet","Nalgonda","Yadadri Bhuvanagiri","Medchal",
    "Hyderabad","Rangareddy","Vikarabad","Sangareddy",
    "Medak","Siddipet","Jangaon","Narayanpet",
    "Mahabubnagar","Wanaparthy","Nagarkurnool",
    "Jogulamba Gadwal","Jayashankar"
};

char *colorNames[] = {"", "Red", "Green", "Blue", "Yellow"};

int graph[N][N] = {0};
int color[N] = {0};

// Add bidirectional edge
void addEdge(int a, int b) {
    if (a >= 0 && a < N && b >= 0 && b < N) {
        graph[a][b] = 1;
        graph[b][a] = 1;
    }
}

// Check constraint
bool isSafe(int node, int c) {
    for (int i = 0; i < N; i++) {
        if (graph[node][i] && color[i] == c)
            return false;
    }
    return true;
}

// Backtracking CSP
bool solve(int node) {
    if (node == N)
        return true;

    for (int c = 1; c <= COLORS; c++) {
        if (isSafe(node, c)) {
            color[node] = c;

            if (solve(node + 1))
                return true;

            color[node] = 0; // backtrack
        }
    }
    return false;
}

int main() {

    if (N == 0) {
        printf("No districts.\n");
        return 0;
    }

    // --- IMPORTANT: REALISTIC ADJACENCY ---

    // North Telangana
    addEdge(0,1); addEdge(0,3);
    addEdge(1,4); addEdge(1,8);
    addEdge(2,7); addEdge(2,32);
    addEdge(3,2);

    // Nizamabad region
    addEdge(4,5); addEdge(4,8);
    addEdge(5,24); addEdge(5,8);

    // Karimnagar cluster
    addEdge(6,7); addEdge(6,9); addEdge(6,25);
    addEdge(7,8);
    addEdge(8,9);

    // Warangal cluster
    addEdge(10,11); addEdge(10,13); addEdge(10,26);
    addEdge(11,12);
    addEdge(12,14);
    addEdge(13,14);

    // East Telangana
    addEdge(14,15);
    addEdge(15,16);

    // South-East
    addEdge(16,17);
    addEdge(17,18);

    // Central Telangana
    addEdge(18,19);
    addEdge(19,20);
    addEdge(20,21);

    // Hyderabad region
    addEdge(21,22);
    addEdge(22,23);
    addEdge(23,24);

    // Medak cluster
    addEdge(24,25);
    addEdge(25,26);

    // South Telangana
    addEdge(21,28);
    addEdge(28,29);
    addEdge(29,30);
    addEdge(30,31);
    addEdge(31,27);

    // Solve
    if (solve(0)) {
        printf("\nTelangana Map Coloring (Valid CSP Solution):\n\n");
        for (int i = 0; i < N; i++) {
            printf("%-25s -> %s\n", districts[i], colorNames[color[i]]);
        }
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
