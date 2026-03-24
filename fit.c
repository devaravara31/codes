#include <stdio.h>

int main() {

    int blockSize[20], processSize[20];
    int m, n, i, j, choice;
    int allocation[20];

    printf("Enter number of memory blocks: ");
    scanf("%d",&m);

    printf("Enter sizes of blocks:\n");
    for(i=0;i<m;i++)
        scanf("%d",&blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter sizes of processes:\n");
    for(i=0;i<n;i++)
        scanf("%d",&processSize[i]);

    printf("\n1.First Fit\n2.Best Fit\n3.Worst Fit\n4.Next Fit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    for(i=0;i<n;i++)
        allocation[i] = -1;

    if(choice == 1)   // FIRST FIT
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                if(blockSize[j] >= processSize[i])
                {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    break;
                }
            }
        }
    }

    else if(choice == 2)  // BEST FIT
    {
        for(i=0;i<n;i++)
        {
            int best = -1;

            for(j=0;j<m;j++)
            {
                if(blockSize[j] >= processSize[i])
                {
                    if(best == -1 || blockSize[j] < blockSize[best])
                        best = j;
                }
            }

            if(best != -1)
            {
                allocation[i] = best;
                blockSize[best] -= processSize[i];
            }
        }
    }

    else if(choice == 3)  // WORST FIT
    {
        for(i=0;i<n;i++)
        {
            int worst = -1;

            for(j=0;j<m;j++)
            {
                if(blockSize[j] >= processSize[i])
                {
                    if(worst == -1 || blockSize[j] > blockSize[worst])
                        worst = j;
                }
            }

            if(worst != -1)
            {
                allocation[i] = worst;
                blockSize[worst] -= processSize[i];
            }
        }
    }

    else if(choice == 4)  // NEXT FIT
    {
        int last = 0;

        for(i=0;i<n;i++)
        {
            int count = 0;
            j = last;

            while(count < m)
            {
                if(blockSize[j] >= processSize[i])
                {
                    allocation[i] = j;
                    blockSize[j] -= processSize[i];
                    last = j;
                    break;
                }

                j = (j + 1) % m;
                count++;
            }
        }
    }

    printf("\nProcess No\tProcess Size\tBlock No\n");

    for(i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t", i+1, processSize[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i]+1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}