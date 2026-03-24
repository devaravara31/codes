#include <stdio.h>
#include <unistd.h>

int main() {
    int N, choice;
    int empty, full, mutex;
    
    printf("Enter total number of tables: ");
    scanf("%d", &N);

    empty = N;
    full = 0;
    mutex = 1;

    while(1) {
        // Display restaurant state
        printf("\nRESTAURANT (Semaphore Simulation)\n");
        printf("Tables (N) = %d | Free(empty) = %d | Occupied (full) = %d | mutex = %d\n", 
               N, empty, full, mutex);

        printf("TABLES: ");
        for(int i = 0; i < full; i++) printf("[X]");
        for(int i = 0; i < empty; i++) printf("[]");
        printf("\n");

        // Display state
        if(full == 0)
            printf("STATE: BUFFER EMPTY -> Arrival (Producer) ALLOWED | Exit (Consumer) DENIED\n");
        else if(empty == 0)
            printf("STATE: BUFFER FULL -> Arrival (Producer) DENIED | Exit (Consumer) ALLOWED\n");
        else
            printf("STATE: PARTIALLY FILLED -> Arrival (Producer) ALLOWED | Exit (Consumer) ALLOWED\n");

        // Menu
        printf("\n1) Customer ARRIVES (Producer: occupy a table)\n");
        printf("2) Customer LEAVES (Consumer: free a table)\n");
        printf("3) Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: // Customer arrives
                printf("\n-- Producer steps ..\n");
                if(mutex == 1 && empty > 0) {
                    printf("wait(mutex): mutex %d -> 0\n", mutex);
                    mutex = 0;

                    printf("wait(empty): empty %d -> %d\n", empty, empty-1);
                    empty--;

                    // Critical Section
                    printf("CRITICAL SECTION: customer occupies a table\n");

                    full++;
                    printf("signal(full): full %d -> %d\n", full-1, full);

                    mutex = 1;
                    printf("signal(mutex): mutex 0 -> 1\n");

                    printf("[EXIT] One customer arrived. Table occupied.\n");
                } else if(empty == 0) {
                    printf("[BLOCKED] No empty table to occupy. BUFFER FULL (empty=0).\n");
                }
                break;

            case 2: // Customer leaves
                printf("\n-- Consumer steps ..\n");
                if(mutex == 1 && full > 0) {
                    printf("wait(mutex): mutex %d -> 0\n", mutex);
                    mutex = 0;

                    printf("wait(full): full %d -> %d\n", full, full-1);
                    full--;

                    // Critical Section
                    printf("CRITICAL SECTION: customer leaves, freeing a table\n");

                    empty++;
                    printf("signal(empty): empty %d -> %d\n", empty-1, empty);

                    mutex = 1;
                    printf("signal(mutex): mutex 0 -> 1\n");

                    printf("[EXIT] One customer left. Table freed.\n");
                } else if(full == 0) {
                    printf("[BLOCKED] No occupied table to free. BUFFER EMPTY (full=0).\n");
                }
                break;

            case 3:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}