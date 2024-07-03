#include <stdio.h>
#include <stdlib.h>
void dijsktra(int source, int shortestIndex, int currentDistance, int size, int graph[size][size], int visited[size], int vistedIndex, int destination, int destinationDistance)
{
    if (vistedIndex == size)
    {
        printf("\nDistance to Destination: %d\n", destinationDistance);
        return;
    }
    int isRowFullZero = 1;
    for (int i = 1; i <= size - 1; i++)
    {
        if (graph[source][i] != 0 && (graph[source][i] <= graph[source][shortestIndex] ||
                                      graph[source][shortestIndex] == 0))
        {
            isRowFullZero = 0;
            int alreadyVisited = 0;
            for (int j = 0; j < vistedIndex; j++)
            {
                if (visited[j] == i)
                    alreadyVisited = 1;
            }
            if (alreadyVisited == 0)
                shortestIndex = i;
        }
    }
    if (isRowFullZero == 1)
    {
        int oldSource = visited[vistedIndex - 1];
        currentDistance -= graph[oldSource][source];
        shortestIndex = size - 1;
    }
    int tempCurrentDistance = currentDistance + graph[source][shortestIndex];
    if (tempCurrentDistance != currentDistance)
    {
        if (tempCurrentDistance > graph[0][shortestIndex] && graph[0][shortestIndex] !=
                                                                 0)
        {
            currentDistance = graph[0][shortestIndex];
        }
        else
            currentDistance += graph[source][shortestIndex];
        printf("%d \t\t %d\n", (shortestIndex + 1), currentDistance);
    }
    else if (shortestIndex != 0)
    {
        printf("Dey\n");
        int shortestValue = graph[0][shortestIndex];
        for (int j = size - 1; j > 0; j--)
        {
            if (shortestValue == 0 || (shortestValue > graph[j][shortestIndex] &&
                                       graph[j][shortestIndex] != 0))
            {
                shortestValue = graph[j][shortestIndex];
            }
        }
        currentDistance += shortestValue;
        printf("%d \t\t %d\n", (shortestIndex + 1), currentDistance);
    }
    if (shortestIndex + 1 == destination)
        destinationDistance = currentDistance;
    visited[vistedIndex] = source;
    vistedIndex++;
    dijsktra(shortestIndex, graph[shortestIndex][0], currentDistance, size, graph, visited,
             vistedIndex, destination, destinationDistance);
}
void main()
{
    int n = 6;
    printf("\nEnter the Number of Vertices: ");
    scanf("%d", &n);
    int graph[n][n];
    for (int i = 0; i < n; i++)
    {
        printf("\nVertex %d: Enter the Distances to Other Vertices(0 for no edge)\n", (i +
                                                                                       1));
        for (int j = 0; j < n; j++)
        {
            printf("%d --> %d: ", (i + 1), (j + 1));
            scanf("%d", &graph[i][j]);
        }
    }
    int destination = 1;
    int destinationDistance = 0;
    printf("\nEnter the destination vertex: ");
    scanf("%d", &destination);
    int visited[n];
    visited[0] = 0;
    int vistedIndex = 1;
    printf("\n\nVertex \t Distance from Source\n");
    dijsktra(0, graph[0][0], 0, n, graph, visited, vistedIndex, destination,
             destinationDistance);
}