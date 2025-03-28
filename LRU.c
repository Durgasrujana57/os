#include <stdio.h>

int main() {
    int i, j, min, rs[25], frames[10], count[10], flag[25], n, f, page_faults = 0, time_counter = 1;

    // Step 1: Take input for reference string length
    printf("Enter the length of the reference string: ");
    scanf("%d", &n);

    // Step 2: Input the reference string
    printf("Enter the reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &rs[i]);
        flag[i] = 0; // Initialize flag to indicate no page is loaded yet
    }

    // Step 3: Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &f);

    // Step 4: Initialize the frames and count arrays
    for (i = 0; i < f; i++) {
        count[i] = 0; // This will store the last used time
        frames[i] = -1; // -1 means the frame is empty
    }

    printf("\nPage Replacement Process:\n");

    // Step 5: Process each page request in the reference string
    for (i = 0; i < n; i++) {
        int page_found = 0; // Flag to check if page is already in memory

        // Step 6: Check if page is already in memory (Page Hit)
        for (j = 0; j < f; j++) {
            if (frames[j] == rs[i]) { // If page is found in memory
                flag[i] = 1; 
                count[j] = time_counter++; // Update last used time
                page_found = 1; // Page found in memory
                break; // No need to check further
            }
        }

        // Step 7: If the page is NOT found in memory (Page Fault)
        if (!page_found) {
            if (i < f) { // Case 1: If there are empty frames, use them first
                frames[i] = rs[i]; 
                count[i] = time_counter++; // Set last used time
            } 
            else { // Case 2: All frames are occupied -> Apply LRU replacement
                min = 0;
                for (j = 1; j < f; j++) { // Find the LRU page (least used)
                    if (count[min] > count[j]) {
                        min = j;
                    }
                }

                // Replace the LRU page with the new page
                frames[min] = rs[i];
                count[min] = time_counter++;
            }

            page_faults++; // Increase page fault count
        }

        // Step 8: Print current memory frames
        for (j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d\t", frames[j]); // Print frame content
            else
                printf("-\t"); // Print empty frame as '-'
        }

        // Print page fault info
        if (!page_found)
            printf("Page Fault No. %d", page_faults);
        
        printf("\n");
    }

    // Step 9: Print total number of page faults
    printf("\nTotal number of page faults using LRU: %d\n", page_faults);
    return 0;
}
