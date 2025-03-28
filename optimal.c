#include <stdio.h>

int main() {
    int rs[25], frames[10], n, f, i, j, k, pageFaults = 0, flag, farthest, index, found;
    
    // Get reference string length
    printf("Enter the length of reference string: ");
    scanf("%d", &n);

    // Get reference string values
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
    }

    // Get number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++) {
        frames[i] = -1; // Empty frame
    }

    printf("\nThe Page Replacement Process is:\n");

    // Processing each page in reference string
    for (i = 0; i < n; i++) {
        flag = 0;

        // Check if page is already in a frame (Page Hit)
        for (j = 0; j < f; j++) {
            if (frames[j] == rs[i]) {
                flag = 1; // Page is already in frame
                break;
            }
        }

        // If page is not found (Page Fault)
        if (flag == 0) {
            // If there is space in frames, insert directly
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    frames[j] = rs[i];
                    pageFaults++;
                    flag = 1;
                    break;
                }
            }
        }

        // If frames are full, find the optimal page to replace
        if (flag == 0) {
            farthest = -1, index = -1;

            // Find the page that will not be used for the longest time
            for (j = 0; j < f; j++) {
                found = 0;
                
                // Check how far this page will be used again
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == rs[k]) {
                        found = 1;
                        if (k > farthest) {
                            farthest = k;
                            index = j;
                        }
                        break;
                    }
                }

                // If a page is never used again, replace it immediately
                if (found == 0) {
                    index = j;
                    break;
                }
            }

            // Replace the optimal page
            frames[index] = rs[i];
            pageFaults++;
        }

        // Print current frame state
        for (j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("\t%d", frames[j]);
            else
                printf("\t-");
        }
        printf("\n");
    }

    // Print total page faults
    printf("\nTotal Page Faults using Optimal: %d\n", pageFaults);

    return 0;
}

// Output
// Enter the length of reference string: 5
// Enter the reference string: 1 2 3 4 1
// Enter the number of frames: 3

// The Page Replacement Process is:
// 	1	-	-
// 	1	2	-
// 	1	2	3
// 	1	4	3
// 	1	4	3

// Total Page Faults using Optimal: 4