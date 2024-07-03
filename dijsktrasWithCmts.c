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

    /*
    vertexDistances is used to store the distance from one vertex to another,
    where the row indicates the current vertex the column indicates another vertex.
    and each cell has the value of the distance between them(0 for no edge)
    */
    int vertexDistances[n][n];

    /*
    for calulating the distances we need another similar matrix also for storing
    the relaxed distance as per Abdul Bari Sir's video(https://www.youtube.com/watch?v=XB4MIexjvY0).
    */
    int calculationArray[n][n];

    /*
    An vertex which has been once scanned don't need to be scanned again, for keeping
    track of that we use this 1d array which pushes each of the shortest vertex.
    */
    int scannedVertices[n];
    int scannedVerticesIndex = 0;

    // Taking user inputs.
    for (int i = 0; i < n; i++)
    {
        printf("Enter the distance from %d to other vertices\n", i);
        for (int j = 0; j < n; j++)
        {
            printf("%d --> %d: ", i, j);
            scanf("%d", &vertexDistances[i][j]);
        }
    }

    // Printing the user input as well as initalizing the first row of the calculationArray.
    printf("Vertex Distances:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // we are initalizing the first row only so i == 0 condition check.
            if (i == 0)
                calculationArray[i][j] = vertexDistances[i][j];
            printf("%d\t", vertexDistances[i][j]);
        }
        printf("\n");
    }

    // A variable to keep track of the calculationArrayIndex.
    int calculationArrayIndex = 1;

    /*
    for each row iteration we will find the shortest edge amongst
    the current row values and that vertex will be travelled next.
    nextShortestVertex is used to store that vertex number.
    */
    int nextShortestVertex = 0;

    for (int i = 0; i < n; i++)
    {
        // reinializing the nextShortestVertex to 0, for each row its recalculated.
        nextShortestVertex = 0;

        // by default this prmg sets source as 1st vertext(aka 0 as per program), thus j starts with 1.
        for (int j = 1; j < n; j++)
        {
            // checking whether that vertex has been already scanned, if so updating the flag.
            int alreadyScanned = 0;
            for (int k = 0; k < scannedVerticesIndex; k++)
            {
                if (j == scannedVertices[k])
                {
                    alreadyScanned = 1;
                    break;
                }
            }

            // else storing the vertex number to our variable, provided it satisfyies the conditions.
            if (alreadyScanned == 0)
                if (calculationArray[i][nextShortestVertex] == 0 || (calculationArray[i][j] > 0 && calculationArray[i][j] < calculationArray[i][nextShortestVertex]))
                {
                    nextShortestVertex = j;
                }
        }

        // pushing the unscanned vertex to the scannedVerticesArray for later use.
        scannedVertices[scannedVerticesIndex++] = nextShortestVertex;

        // calculating the distance via new shortest edge and replacing old distance if less than.

        /*
        CORE FORMULA

        if(d[u] + c(c,v) < d[v])
            d[v] = d[u] + c(c,v)
        */

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

    // printing the shortest path from the source vertex.
    // j starts from 1 as source is 0.
    printf("\n\nVertex \t Distance from Source\n");

    for (int j = 1; j < n; j++)
    {
        if(j+1 == destinationVertex)
            destinationVertexDistance =  calculationArray[n - 1][j];
        printf("%d\t\t %d\t \n", j + 1, calculationArray[n - 1][j]);
    }

    printf("\nDistance to Destination: %d\n", destinationVertexDistance);
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