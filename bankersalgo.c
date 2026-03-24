#include <stdio.h>
#include <stdlib.h>

int main() {
    int N, R;
    printf("Enter the number of processes: ");
    scanf("%d", &N);
    printf("Enter the number of resources: ");
    scanf("%d", &R);

    int max[N][R], alloc[N][R], need[N][R];
    int total[R], avail[R], work[R];
    int finish[N], safeSeq[N];

    // Input allocations and maximum needs
    for (int i = 0; i < N; i++) {
        printf("PROCESS %d\n", i + 1);
        for (int j = 0; j < R; j++) {
            printf("Allocated for R%d: ", j + 1);
            scanf("%d", &alloc[i][j]);
            printf("Max Resource for R%d: ", j + 1);
            scanf("%d", &max[i][j]);
        }
    }

    // Input total resources
    for (int i = 0; i < R; i++) {
        printf("Total Resource R%d: ", i + 1);
        scanf("%d", &total[i]);
    }

    // Calculate need matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Calculate available resources
    for (int i = 0; i < R; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++)
            sum += alloc[j][i];
        avail[i] = total[i] - sum;
        work[i] = avail[i];
    }

    // Initialize finish flags
    for (int i = 0; i < N; i++)
        finish[i] = 0;

    int count = 0;
    while (count < N) {
        int found = 0;
        for (int i = 0; i < N; i++) {
            if (finish[i] == 0) {
                int possible = 1;
                for (int j = 0; j < R; j++)
                    if (need[i][j] > work[j])
                        possible = 0;

                if (possible) {
                    for (int j = 0; j < R; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break;
    }

    if (count == N) {
        printf("\nSystem is in SAFE state.\nSafe Sequence: ");
        for (int i = 0; i < N; i++) {
            printf("P%d", safeSeq[i] + 1);
            if (i != N - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in SAFE state (Deadlock).\n");
    }

    return 0;
}