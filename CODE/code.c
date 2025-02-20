#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_NODES 10
#define INFINITY 999

void dijkstra(int numNodes, int cost[MAX_NODES][MAX_NODES], char source, int dist[MAX_NODES], int prev[MAX_NODES]);
void getPath(int destination, char source, int dist[MAX_NODES], int prev[MAX_NODES]);

int main() {
    int i, j, numNodes, cost[MAX_NODES][MAX_NODES], dist[MAX_NODES], prev[MAX_NODES];
    char source;
    char input[10];
    printf("---------------------------------------------------------------------------------------\n");
    printf("Shortest PathFinding algorithm\n");
    printf("---------------------------------------------------------------------------------------\n");
    while (true) {
        printf("Enter the number of nodes (1 to 10) or enter '-1' to exit: ");
        if (scanf("%s", input) != 1) {
            printf("Invalid input! Please enter a valid number or '-1' to exit.\n");
            while (getchar() != '\n');
        } else {
            if (atoi(input) == -1) {
                printf("Exiting the program...\n");
                exit(0);
            } else if (sscanf(input, "%d", &numNodes) != 1) {
                printf("Invalid number of nodes! Please enter a valid number or '-1' to exit.\n");
                printf("\n");
            } else if (numNodes < 1 || numNodes > MAX_NODES) {
                printf("Invalid number of nodes! Please enter a number between 1 and %d or '-1' to exit.\n", MAX_NODES);
                printf("\n");
            } else {
                break;
            }
        }
    }
    printf("---------------------------------------------------------------------------------------\n");
    printf("NOTE: When you don't know the distance between the nodes, please enter '0'.\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("Read the cost matrix:\n");
    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            if (i == j) {
                cost[i][j] = 0;
                continue;
            }
            while (true) {
                printf("Enter the cost from Node %c to Node %c: ", i + 'A', j + 'A');
                if (scanf("%d", &cost[i][j]) != 1) {
                    printf("Invalid input! Please enter a valid number.\n");
                } else {
                    break;
                }
            }

            if (cost[i][j] == 0) {
                cost[i][j] = INFINITY;
            }
        }
    }

   while (true) {
    printf("---------------------------------------------------------------------------------------\n");
    printf("Read the source vertex (i.e Single) (or enter 'Q' to exit) : ");
    if (scanf(" %c", &source) != 1) {
        printf("Invalid input! Please enter a valid character.\n");
        while (getchar() != '\n');
    } else {
        source = toupper(source);
        if (source == 'Q') {
            printf("Exiting the program...\n");
            exit(0);
        } else if (source < 'A' || source > 'A' + numNodes - 1) {
            printf("Invalid source vertex! Please enter a valid character between 'A' and '%c'.\n", 'A' + numNodes - 1);
        } else {
            break;
        }
    }
}


    dijkstra(numNodes, cost, source, dist, prev);
    printf("---------------------------------------------------------------------------------------\n");
    printf("Shortest path from Node %c is:\n", source);
    for (i = 0; i < numNodes; i++) {
        if (source != i + 'A') {
            printf("Node %c -> Node %c = %d\n", source, i + 'A', dist[i]);
            printf("Path: ");
            getPath(i, source, dist, prev);
            printf("Node %c\n", i + 'A');
        }
    }

    return 0;
}

void dijkstra(int numNodes, int cost[MAX_NODES][MAX_NODES], char source, int dist[MAX_NODES], int prev[MAX_NODES]) {
    int i, v, count = 0, min;
    int visited[MAX_NODES];

    for (i = 0; i < numNodes; i++) {
        visited[i] = 0;
        dist[i] = cost[source - 'A'][i];
        prev[i] = source - 'A';
    }

    visited[source - 'A'] = 1;
    dist[source - 'A'] = 0;

    while (count < numNodes) {
        min = INFINITY;
        v = -1;

        for (i = 0; i < numNodes; i++) {
            if (visited[i] == 0 && dist[i] < min) {
                min = dist[i];
                v = i;
            }
        }

        if (v == -1)
            break;

        visited[v] = 1;
        count++;

        for (i = 0; i < numNodes; i++) {
            if (visited[i] == 0 && dist[v] + cost[v][i] < dist[i]) {
                dist[i] = dist[v] + cost[v][i];
                prev[i] = v;
            }
        }
    }
}

void getPath(int destination, char source, int dist[MAX_NODES], int prev[MAX_NODES]) {
    if (destination != source - 'A') {
        getPath(prev[destination], source, dist, prev);
        printf("Node %c -> ", prev[destination] + 'A');
    }
}
