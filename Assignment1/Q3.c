#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 100

char S[MAX][LEN];
int size = 0;

// Check whether string already exists
int exists(char set[][LEN], int n, char str[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(set[i], str) == 0)
            return 1;
    }
    return 0;
}

// Add string if it does not already exist
void add(char set[][LEN], int *n, char str[]) {
    if (strlen(str) > 0 && !exists(set, *n, str)) {
        strcpy(set[*n], str);
        (*n)++;
    }
}

// Generate next Sardinas-Patterson set
int generateNext(char current[][LEN], int currentSize,
                 char codes[][LEN], int n,
                 char next[][LEN]) {

    int nextSize = 0;

    for (int i = 0; i < currentSize; i++) {

        for (int j = 0; j < n; j++) {

            int len1 = strlen(current[i]);
            int len2 = strlen(codes[j]);

            // current[i] = codes[j] + suffix
            if (len1 > len2 &&
                strncmp(current[i], codes[j], len2) == 0) {

                char suffix[LEN];

                strcpy(suffix, current[i] + len2);

                add(next, &nextSize, suffix);
            }

            // codes[j] = current[i] + suffix
            else if (len2 > len1 &&
                     strncmp(codes[j], current[i], len1) == 0) {

                char suffix[LEN];

                strcpy(suffix, codes[j] + len1);

                add(next, &nextSize, suffix);
            }

            // Equal strings => empty string
            else if (len1 == len2 &&
                     strcmp(current[i], codes[j]) == 0) {

                return -1;
            }
        }
    }

    return nextSize;
}

int main() {

    int n;
    char codes[MAX][LEN];

    printf("Enter number of codes: ");
    scanf("%d", &n);

    printf("Enter the codes:\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", codes[i]);
    }

    // First Sardinas-Patterson set S1
    char current[MAX][LEN];
    int currentSize = 0;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (i == j)
                continue;

            int len1 = strlen(codes[i]);
            int len2 = strlen(codes[j]);

            // code[i] = code[j] + suffix
            if (len1 > len2 &&
                strncmp(codes[i], codes[j], len2) == 0) {

                char suffix[LEN];

                strcpy(suffix, codes[i] + len2);

                add(current, &currentSize, suffix);
            }

            // code[j] = code[i] + suffix
            else if (len2 > len1 &&
                     strncmp(codes[j], codes[i], len1) == 0) {

                char suffix[LEN];

                strcpy(suffix, codes[j] + len1);

                add(current, &currentSize, suffix);
            }
        }
    }

    if (currentSize == 0) {
        printf("\nThe given code is UNIQUELY DECODABLE.\n");
        return 0;
    }

    printf("\nSardinas-Patterson Sets:\n");

    int iteration = 1;

    while (1) {

        printf("S%d = { ", iteration);

        for (int i = 0; i < currentSize; i++) {
            printf("%s ", current[i]);
        }

        printf("}\n");

        char next[MAX][LEN];

        int nextSize = generateNext(
            current,
            currentSize,
            codes,
            n,
            next
        );

        // Empty string found
        if (nextSize == -1) {
            printf("\nThe given code is NOT UNIQUELY DECODABLE.\n");
            return 0;
        }

        // No new suffixes
        if (nextSize == 0) {
            printf("\nThe given code is UNIQUELY DECODABLE.\n");
            return 0;
        }

        // Same set appeared again
        int same = 1;

        if (nextSize != currentSize) {
            same = 0;
        } else {
            for (int i = 0; i < currentSize; i++) {
                if (!exists(next, nextSize, current[i])) {
                    same = 0;
                    break;
                }
            }
        }

        if (same) {
            printf("\nThe given code is UNIQUELY DECODABLE.\n");
            return 0;
        }

        // Copy next set into current
        currentSize = nextSize;

        for (int i = 0; i < nextSize; i++) {
            strcpy(current[i], next[i]);
        }

        iteration++;
    }

    return 0;
}