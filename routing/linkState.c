// link state routing
#include <stdio.h>

void main()
{
    int cost[5][5] = {
        {0, 2, 5, 1, 999},
        {2, 0, 3, 2, 999},
        {5, 3, 0, 3, 1},
        {1, 2, 3, 0, 1},
        {999, 999, 1, 1, 0}};

    int dist[5];
    int visited[5] = {0};

    for (int i = 0; i < 5; i++)
    {
        dist[i] = cost[0][i];
    }
    visited[0] = 1;

    for (int i = 0; i < 4; i++)
    {
        int min = 999, min_index;
        for (int j = 0; j < 5; j++)
        {
            if (!visited[j] && dist[j] < min)
            {
                min = dist[j];
                min_index = j;
            }
        }
        visited[min_index] = 1;
        for (int j = 0; j < 5; j++)
        {
            if (!visited[j] && dist[min_index] + cost[min_index][j] < dist[j])
            {
                dist[j] = dist[min_index] + cost[min_index][j];
            }
        }
    }
    printf("Shortest distances from node 0:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Node %d: %d\n", i, dist[i]);
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