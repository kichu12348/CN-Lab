// link state routing
#include <stdio.h>
#define INF 999
#define MAX 20

void main()
{
    int cost[MAX][MAX];
    int dist[MAX];
    int visited[MAX];
    int prev[MAX];
    int n, source;

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

    printf("Enter the source node: ");
    scanf("%d", &source);

    for (int i = 0; i < n; i++)
    {
        dist[i] = cost[source][i];
        prev[i] = source;
        visited[i] = 0;
    }

    visited[source] = 1;

    for (int i = 0; i < n - 1; i++)
    {
        int min_dist = 999;
        int min_idx = -1;
        // FIND the node with the smallest distance from the source node that has not been visited yet
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < min_dist)
            {
                min_dist = dist[j];
                min_idx = j;
            }
        }

        visited[min_idx] = 1; // Mark the node with the smallest distance as visited

        // Update the distances to the neighboring nodes of the newly visited node
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && dist[min_idx] + cost[min_idx][j] < dist[j])
            {
                dist[j] = dist[min_idx] + cost[min_idx][j];
                prev[j] = min_idx;
            }
        }
    }

    int temp;
    for (int i = 0; i < n; i++)
    {
        printf("\n%d -> %d path taken: %d", source, i, i);
        temp = i;
        while (temp != source)
        {
            printf(" <- %d", prev[temp]);
            temp = prev[temp]; // 0 -> 1 path taken: 1 <- 0
        }
        printf("\nShortest distance from %d to %d: %d\n", source, i, dist[i]);
    }
}

/*
how it works
1. We define a cost matrix that represents the cost of traveling from one node to another.
 In this example, we have 5 nodes, and the cost of traveling from node i to node j is
 given by cost[i][j]. A value of 999 indicates that there is no direct path between the nodes.

2. We initialize a distance array (dist) to store the shortest distance
from the source node (node 0) to all other nodes. Initially, we set dist[i] to cost[0][i],
which represents the direct cost from the source node to each node.

3. We also maintain a visited array to keep track of which nodes have been visited during the algorithm.

4. We start the algorithm by marking the source node (node 0) as visited.

5. We then enter a loop that runs until all nodes have been visited. In each iteration,
we find the unvisited node with the smallest distance (min_index) and mark it as visited.

6. After marking the node as visited, we update the distances to its neighboring nodes.
If the distance to a neighboring node through the newly visited node is smaller than the previously known distance,
we update the distance in the dist array.

7. Finally, after all nodes have been visited, we print the shortest distances from the source node to all other nodes.
*/