#include <stdio.h>

void main()
{
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int destinationVertex;
    int destinationVertexDistance;
    printf("Enter the destination vertex: ");
    scanf("%d", &destinationVertex);

    int vertexDistances[n][n];
    int calculationArray[n][n];

    int scannedVertices[n];
    int scannedVerticesIndex = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Enter the distance from %d to other vertices\n", i);
        for (int j = 0; j < n; j++)
        {
            printf("%d --> %d: ", i, j);
            scanf("%d", &vertexDistances[i][j]);
        }
    }

    printf("Vertex Distances:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0)
                calculationArray[i][j] = vertexDistances[i][j];
            printf("%d\t", vertexDistances[i][j]);
        }
        printf("\n");
    }

    int calculationArrayIndex = 1;
    int nextShortestVertex = 0;

    for (int i = 0; i < n; i++)
    {
        nextShortestVertex = 0;

        for (int j = 1; j < n; j++)
        {
            int alreadyScanned = 0;
            for (int k = 0; k < scannedVerticesIndex; k++)
            {
                if (j == scannedVertices[k])
                {
                    alreadyScanned = 1;
                    break;
                }
            }

            if (alreadyScanned == 0)
                if (calculationArray[i][nextShortestVertex] == 0 || (calculationArray[i][j] > 0 && calculationArray[i][j] < calculationArray[i][nextShortestVertex]))
                {
                    nextShortestVertex = j;
                }
        }

        scannedVertices[scannedVerticesIndex++] = nextShortestVertex;

        for (int k = 1; k < n; k++)
        {
            int du = calculationArray[calculationArrayIndex - 1][nextShortestVertex];
            int ccv = vertexDistances[nextShortestVertex][k];
            int dv = calculationArray[calculationArrayIndex - 1][k];

            if (ccv > 0 && du > 0 && (du + ccv < dv || dv == 0))
            {
                dv = du + ccv;
                calculationArray[calculationArrayIndex][k] = dv;
            }
            else
                calculationArray[calculationArrayIndex][k] = dv;
        }

        calculationArrayIndex++;
    }

    printf("\n\nVertex \t Distance from Source\n");

    for (int j = 1; j < n; j++)
    {
        if (j + 1 == destinationVertex)
            destinationVertexDistance = calculationArray[n - 1][j];
        printf("%d\t\t %d\t \n", j + 1, calculationArray[n - 1][j]);
    }

    printf("\nDistance to Destination: %d\n", destinationVertexDistance);
}
