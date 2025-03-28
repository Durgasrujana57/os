#include <stdio.h>

int main() {
    int i, j, k, f, pf = 0, count = 0, rs[25], m[10], n;

    printf("\n Enter the length of reference string: ");
    scanf("%d", &n);

    printf("\n Enter the reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &rs[i]);

    printf("\n Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        m[i] = -1;  // Initialize frames to -1 (empty)

    printf("\n The Page Replacement Process is: \n");

    for (i = 0; i < n; i++) {
        for (k = 0; k < f; k++) {
            if (m[k] == rs[i]) // Page Hit: Found in memory
                break;
        }

        if (k == f) { // Page Fault: Not found in memory
            m[count] = rs[i]; // Replace the oldest page (FIFO)
            count = (count + 1) % f; // Move pointer for next replacement
            pf++; // Increment page fault counter
        }

        // Print memory frames
        for (j = 0; j < f; j++)
            printf("\t%d", (m[j] == -1) ? -1 : m[j]);

        if (k == f)
            printf("\tPF No. %d", pf);

        printf("\n");
    }

    printf("\n Total Page Faults using FIFO: %d\n", pf);

    return 0;
}
