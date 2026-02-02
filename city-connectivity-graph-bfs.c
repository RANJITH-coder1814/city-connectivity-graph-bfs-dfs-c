#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

int numCities, adj[MAX][MAX], visited[MAX];
char cities[MAX][30];

void initGraph() {
    printf("Number of cities (max %d): ", MAX);
    scanf("%d", &numCities);

    if (numCities <= 0 || numCities > MAX) {
        printf("Invalid!\n");
        numCities = 0;
        return;
    }

    for (int i = 0; i < numCities; i++)
        for (int j = 0; j < numCities; j++)
            adj[i][j] = 0;

    printf("\nEnter city names:\n");
    for (int i = 0; i < numCities; i++) {
        printf("City %d: ", i);
        scanf("%s", cities[i]);
    }

    printf("\nEnter connections (1=connected, 0=not):\n");
    for (int i = 0; i < numCities; i++)
        for (int j = 0; j < numCities; j++)
            if (i != j) {
                printf("%s to %s: ", cities[i], cities[j]);
                scanf("%d", &adj[i][j]);
            }

    printf("Graph created successfully!\n");
}

void displayGraph() {
    if (numCities == 0) {
        printf("No graph created!\n");
        return;
    }

    printf("\nCities:\n");
    for (int i = 0; i < numCities; i++)
        printf("%d. %s\n", i, cities[i]);

    printf("\nAdjacency Matrix:\n   ");
    for (int j = 0; j < numCities; j++)
        printf("%2d ", j);
    printf("\n");

    for (int i = 0; i < numCities; i++) {
        printf("%2d:", i);
        for (int j = 0; j < numCities; j++)
            printf("%2d ", adj[i][j]);
        printf("\n");
    }
}

void dfsUtil(int city) {
    visited[city] = 1;
    printf("%s ", cities[city]);

    for (int i = 0; i < numCities; i++)
        if (adj[city][i] && !visited[i])
            dfsUtil(i);
}

void dfs(int start) {
    for (int i = 0; i < numCities; i++)
        visited[i] = 0;

    printf("\nDFS from %s: ", cities[start]);
    dfsUtil(start);

    int count = 0;
    printf("\n\nReachability:\n");

    for (int i = 0; i < numCities; i++) {
        printf("%s %s\n", visited[i] ? "✓" : "✗", cities[i]);
        if (visited[i]) count++;
    }

    printf("Reachable: %d/%d\n", count, numCities);
}

void bfs(int start) {
    int queue[MAX], front = 0, rear = 0;

    for (int i = 0; i < numCities; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nBFS from %s: ", cities[start]);

    while (front < rear) {
        int current = queue[front++];
        printf("%s ", cities[current]);

        for (int i = 0; i < numCities; i++)
            if (adj[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
    }

    int count = 0;
    printf("\n\nReachability:\n");

    for (int i = 0; i < numCities; i++) {
        printf("%s %s\n", visited[i] ? "✓" : "✗", cities[i]);
        if (visited[i]) count++;
    }

    printf("Reachable: %d/%d\n", count, numCities);
}

void analyze() {
    if (numCities == 0) {
        printf("No graph available!\n");
        return;
    }

    int start, method;

    printf("\nSelect city:\n");
    for (int i = 0; i < numCities; i++)
        printf("%d. %s  ", i, cities[i]);

    printf("\nStart city: ");
    scanf("%d", &start);

    if (start < 0 || start >= numCities) {
        printf("Invalid city index!\n");
        return;
    }

    printf("1. DFS  2. BFS : ");
    scanf("%d", &method);

    if (method == 2)
        bfs(start);
    else
        dfs(start);
}

int main() {
    int choice;

    printf("=== CITY CONNECTIVITY SYSTEM ===\n");

    while (1) {
        printf("\n1. Create Graph\n2. Display Graph\n3. Analyze Connectivity\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: initGraph(); break;
            case 2: displayGraph(); break;
            case 3: analyze(); break;
            case 4:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
