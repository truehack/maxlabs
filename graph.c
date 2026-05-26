#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100
#define INF   1000000000

typedef struct {
    int n;
    int adj[MAX_V][MAX_V];
} Graph;

void init_graph(Graph *g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
}

void read_edges(Graph *g) {
    int m;
    printf("Enter number of edges: ");
    if (scanf("%d", &m) != 1 || m < 0) {
        printf("Invalid input. Exiting.\n");
        exit(1);
    }

    printf("Enter edges in format: u v weight\n");
    for (int i = 0; i < m; i++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            printf("Invalid edge format. Try again.\n");
            while (getchar() != '\n');
            i--;
            continue;
        }
        
        if (u >= 0 && u < g->n && v >= 0 && v < g->n) {
            g->adj[u][v] = w;
        } else {
            printf("Warning: vertex index out of bounds (got %d, %d, max %d). Try again.\n", u, v, g->n-1);
            i--;
        }
    }
}

void floyd_warshall(Graph *g, int dist[MAX_V][MAX_V]) {
    int n = g->n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = g->adj[i][j];

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

void print_matrix(const char *title, int mat[MAX_V][MAX_V], int n) {
    printf("\n%s\n", title);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == INF) printf("INF\t");
            else printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Lab: Floyd-Warshall Algorithm\n");
    printf("Representation: Adjacency Matrix\n");
    printf("Task: All-pairs shortest paths\n\n");

    printf("Enter number of vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_V) {
        printf("Invalid vertex count. Must be 1-%d.\n", MAX_V);
        return 1;
    }

    Graph g;
    init_graph(&g, n);
    read_edges(&g);

    print_matrix("Initial Adjacency Matrix:", g.adj, n);

    
    int dist[MAX_V][MAX_V];
    floyd_warshall(&g, dist);

    
    print_matrix("Shortest Path Matrix (Floyd-Warshall):", dist, n);

    printf("\nDone.\n");
    return 0;
}