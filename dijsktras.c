#include <stdio.h>

void main()
{
    int n = 6;
    // printf("Enter the number of vertices: ");
    // scanf("%d", &n);
    int vertexDistances[6][6] = {
        {0, 50, 45, 10, 0, 0},
        {0, 0, 10, 15, 0, 0},
        {0, 0, 0, 0, 30, 0},
        {0, 0, 0, 0, 15, 0},
        {0, 20, 35, 0, 0, 0},
        {0, 0, 0, 0, 3, 0}};

    int calculationArray[n][n];
    
    // for (int i = 0; i < n; i++)
    // {
    //     printf("Enter the distance from %d to other vertices\n", i);
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%d --> %d: ", i, j);
    //         scanf("%d", &vertexDistances[i][j]);
    //     }
    // }

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

    for (int i = 0; i < 3; i++)
    {
        nextShortestVertex = 0;
        for (int j = 1; j < n; j++)
        {
            if (calculationArray[i][nextShortestVertex] == 0 || (calculationArray[i][j] > 0 && calculationArray[i][j] < calculationArray[i][nextShortestVertex]))
                nextShortestVertex = j;
        }

        printf("\nShortest Vertex %d\n", nextShortestVertex);

        for (int k = 1; k < n; k++)
        {
            int du = calculationArray[calculationArrayIndex - 1][nextShortestVertex];
            int ccv = vertexDistances[nextShortestVertex][k];
            int dv = calculationArray[calculationArrayIndex - 1][k];

            printf("du: %d, ccv: %d, dv: %d\n", du, ccv, dv);

            if (ccv == 0)
                calculationArray[calculationArrayIndex][k] = dv;
            else if (du + ccv < dv || dv == 0)
            {
                dv = du + ccv;
                calculationArray[calculationArrayIndex][k] = dv;
            }
        }

        calculationArrayIndex++;
    }

    printf("\n\nVertex Distances Final\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", calculationArray[i][j]);
        }
        printf("\n");
    }
}