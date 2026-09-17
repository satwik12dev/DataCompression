#include <stdio.h>
#include <string.h>

#define MAX 100

struct Symbol {
    char ch;
    int frequency;
    char code[MAX];
};

struct Symbol symbols[MAX];
int n = 0;

// Sort symbols according to frequency
void sortSymbols() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (symbols[i].frequency < symbols[j].frequency) {
                struct Symbol temp = symbols[i];
                symbols[i] = symbols[j];
                symbols[j] = temp;
            }
        }
    }
}

// Generate Shannon-Fano codes
void shannonFano(int start, int end) {

    if (start >= end)
        return;

    int total = 0;

    for (int i = start; i <= end; i++)
        total += symbols[i].frequency;

    int sum = 0;
    int split = start;

    int minDiff = total;

    for (int i = start; i < end; i++) {
        sum += symbols[i].frequency;

        int diff = total - 2 * sum;

        if (diff < 0)
            diff = -diff;

        if (diff < minDiff) {
            minDiff = diff;
            split = i;
        }
    }

    // Assign 0 to first group
    for (int i = start; i <= split; i++)
        strcat(symbols[i].code, "0");

    // Assign 1 to second group
    for (int i = split + 1; i <= end; i++)
        strcat(symbols[i].code, "1");

    shannonFano(start, split);
    shannonFano(split + 1, end);
}

int main() {

    char str[MAX];

    printf("Enter a string: ");
    scanf("%s", str);

    // Calculate frequency
    for (int i = 0; str[i] != '\0'; i++) {

        int found = 0;

        for (int j = 0; j < n; j++) {
            if (symbols[j].ch == str[i]) {
                symbols[j].frequency++;
                found = 1;
                break;
            }
        }

        if (!found) {
            symbols[n].ch = str[i];
            symbols[n].frequency = 1;
            symbols[n].code[0] = '\0';
            n++;
        }
    }

    // Sort by frequency
    sortSymbols();

    // Generate Shannon-Fano codes
    shannonFano(0, n - 1);

    printf("\nCharacter\tFrequency\tCode\n");
    printf("--------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%c\t\t%d\t\t%s\n",
               symbols[i].ch,
               symbols[i].frequency,
               symbols[i].code);
    }

    // Display compressed string
    printf("\nCompressed string: ");

    for (int i = 0; str[i] != '\0'; i++) {

        for (int j = 0; j < n; j++) {

            if (symbols[j].ch == str[i]) {
                printf("%s", symbols[j].code);
                break;
            }
        }
    }

    printf("\n");

    return 0;
}