#include <stdio.h>
#include <ctype.h>
#include <math.h>

int main() {
    FILE *file;
    int count[52] = {0};
    int ch;
    int totalLetters = 0;

    file = fopen("C:/Users/SATWIK/OneDrive/Desktop/DataCompression/Assignment1/Q1.txt", "r");

    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    // Read file character by character
    while ((ch = fgetc(file)) != EOF) {

        if (isalpha(ch)) {

            if (ch >= 'A' && ch <= 'Z') {
                count[ch - 'A']++;
                totalLetters++;
            }
            else if (ch >= 'a' && ch <= 'z') {
                count[ch - 'a' + 26]++;
                totalLetters++;
            }
        }
    }

    fclose(file);

    printf("\nLetter\tOccurrence\tProbability\tBits Required\n");
    printf("----------------------------------------------------------\n");

    // Uppercase letters
    for (int i = 0; i < 26; i++) {

        if (count[i] > 0) {

            double probability = (double)count[i] / totalLetters;

            double bits = 1.0 / (log(probability) / log(2.0));

            printf("%c\t%d\t\t%.6f\t%.4f\n",
                   'A' + i,
                   count[i],
                   probability,
                   bits);
        }
    }

    // Lowercase letters
    for (int i = 0; i < 26; i++) {

        if (count[i + 26] > 0) {

            double probability = (double)count[i + 26] / totalLetters;

            double bits = 1.0 / (log(probability) / log(2.0));

            printf("%c\t%d\t\t%.6f\t%.4f\n",
                   'a' + i,
                   count[i + 26],
                   probability,
                   bits);
        }
    }

    printf("----------------------------------------------------------\n");
    printf("Total Letters = %d\n", totalLetters);

    return 0;
}