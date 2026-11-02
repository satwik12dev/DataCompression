#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 100

int exists(char set[][LEN], int n, char str[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(set[i], str) == 0)
            return 1;
    }
    return 0;
}

void add(char set[][LEN], int *n, char str[]) {
    if (strlen(str) > 0 && !exists(set, *n, str)) {
        strcpy(set[*n], str);
        (*n)++;
    }
}

int main() {

    int n;
    char str[MAX][LEN];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    printf("Enter the strings:\n");

    for (int i = 0; i < n; i++) {
        scanf("%s", str[i]);
    }

    char current[MAX][LEN];
    int currentSize = 0;

    // Generate S1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i == j)
                continue;

            int len1 = strlen(str[i]);
            int len2 = strlen(str[j]);

            if (len1 > len2 &&
                strncmp(str[i], str[j], len2) == 0) {

                add(current, &currentSize, str[i] + len2);
            }

            else if (len2 > len1 &&
                     strncmp(str[j], str[i], len1) == 0) {

                add(current, &currentSize, str[j] + len1);
            }
        }
    }

    // S1 is empty
    if (currentSize == 0) {
        printf("\nThe strings are UNIQUELY DECODABLE.\n");
        return 0;
    }

    while (1) {

        char next[MAX][LEN];
        int nextSize = 0;

        for (int i = 0; i < currentSize; i++) {
            for (int j = 0; j < n; j++) {

                int len1 = strlen(current[i]);
                int len2 = strlen(str[j]);

                if (len1 > len2 &&
                    strncmp(current[i], str[j], len2) == 0) {

                    add(next, &nextSize, current[i] + len2);
                }

                else if (len2 > len1 &&
                         strncmp(str[j], current[i], len1) == 0) {

                    add(next, &nextSize, str[j] + len1);
                }

                else if (len1 == len2 &&
                         strcmp(current[i], str[j]) == 0) {

                    printf("\nThe strings are NOT UNIQUELY DECODABLE.\n");
                    return 0;
                }
            }
        }

        if (nextSize == 0) {
            printf("\nThe strings are UNIQUELY DECODABLE.\n");
            return 0;
        }

        // Check if same set occurs again
        int same = (nextSize == currentSize);

        if (same) {
            for (int i = 0; i < currentSize; i++) {
                if (!exists(next, nextSize, current[i])) {
                    same = 0;
                    break;
                }
            }
        }

        if (same) {
            printf("\nThe strings are UNIQUELY DECODABLE.\n");
            return 0;
        }

        currentSize = nextSize;

        for (int i = 0; i < nextSize; i++) {
            strcpy(current[i], next[i]);
        }
    }
}