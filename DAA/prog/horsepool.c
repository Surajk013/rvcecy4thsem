#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 256

// Function to create the bad character heuristic table
void badCharHeuristic(char *pattern, int m, int badChar[]) {
    // Initialize all occurrences to -1
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        badChar[i] = -1;
    }

    // Fill the actual value of the last occurrence of each character
    for (int i = 0; i < m; i++) {
        badChar[(unsigned char)pattern[i]] = i;
    }
}

// Horsepool's algorithm to search for pattern in the text
void horsepoolSearch(char *text, char *pattern) {
    int m = strlen(pattern);
    int n = strlen(text);
    int badChar[ALPHABET_SIZE];

    // Create bad character heuristic table
    badCharHeuristic(pattern, m, badChar);

    int s = 0; // s is the shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        // Compare the pattern with the text from right to left
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        // If the pattern is found
        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - badChar[(unsigned char)text[s + m]] : 1;
        } else {
            s += (j - badChar[(unsigned char)text[s + j]] > 1) ? j - badChar[(unsigned char)text[s + j]] : 1;
        }
    }
}

int main() {
    char text[1000], pattern[1000];

    // Input text and pattern
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  // Remove trailing newline character

    printf("Enter the pattern: ");
    fgets(pattern, sizeof(pattern), stdin);
    pattern[strcspn(pattern, "\n")] = '\0';  // Remove trailing newline character

    horsepoolSearch(text, pattern);

    return 0;
}

