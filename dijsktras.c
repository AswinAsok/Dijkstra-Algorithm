#include <stdio.h>

void main()
{
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
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
        printf("%d\t\t %d\t \n", j + 1, calculationArray[n - 1][j]);
    }
}

/*
Test Case 1:
Enter the number of vertices: 6

Vertex Distances:
0	2	4	0	0	0
0	0	1	7	0	0
0	0	0	0	3	0
0	0	0	0	0	1
0	0	0	2	0	3
0	0	0	0	0	0


Vertex 	 Distance from Source
2		 2
3		 3
4		 8
5		 6
6		 9

Test Case 2:
Enter the number of vertices: 6

Vertex Distances:
0       50      45      10      0       0
0       0       10      15      0       0
0       0       0       0       30      0
0       0       0       0       15      0
0       20      35      0       0       0
0       0       0       0       3       0

Vertex   Distance from Source
2                45
3                45
4                10
5                25
6                0

Test Case 3:
https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/

Enter the number of vertices: 9
Vertex Distances:
0       4       0       0       0       0       0       8       0
4       0       8       0       0       0       0       11      0
0       8       0       7       0       4       0       0       2
0       0       7       0       9       14      0       0       0
0       0       0       9       0       10      0       0       0
0       0       4       14      10      0       2       0       0
0       0       0       0       0       2       0       1       6
8       11      0       0       0       0       1       0       7
0       0       2       0       0       0       6       7       0


Vertex   Distance from Source
2                4
3                12
4                19
5                21
6                11
7                9
8                8
9                14
*/