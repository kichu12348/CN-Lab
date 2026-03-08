#include <stdio.h>
#define INF 999
#define MAX 20

void main()
{
    int cost[MAX][MAX];
    int n;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (use 999 for no direct path):\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
        }
    }

    for (int k = 0; k < n; k++) // intermediate node k
    {
        for (int i = 0; i < n; i++) // source node i
        {
            for (int j = 0; j < n; j++) // destination node j
            {
                if (cost[i][k] + cost[k][j] < cost[i][j]) // check if path through k is shorter than direct path from i to j
                {
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
            }
        }
    }

    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (cost[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", cost[i][j]);
        }
        printf("\n");
    }
}

/*
how it works
1. We define a cost matrix that represents the cost of traveling from one node to another.
    In this example, we have 5 nodes, and the cost of traveling from node i to node j is
    given by cost[i][j]. A value of 999 indicates that there is no direct path between the nodes.
2. We initialize a cost array (cost) to store the shortest cost from the source node (node 0) to all other nodes. Initially, we set cost[i] to cost[0][i], which represents the direct cost from the source node to each node.
3. We also maintain a visited array to keep track of which nodes have been visited during the algorithm.
4. We start the algorithm by marking the source node (node 0) as visited.
5. We then enter a loop that runs until all nodes have been visited. In each iteration,
    we find the unvisited node with the smallest cost (min_index) and mark it as visited.

*/