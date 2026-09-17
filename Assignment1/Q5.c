#include <stdio.h>
#include <string.h>

#define MAX 1000

void compress(char str[], char compressed[]) {
    int i = 0, k = 0;

    while (str[i] != '\0') {
        char ch = str[i];
        int count = 0;

        while (str[i] == ch) {
            count++;
            i++;
        }

        compressed[k++] = ch;

        // Store count
        k += sprintf(&compressed[k], "%d", count);
    }

    compressed[k] = '\0';
}

void decompress(char compressed[], char decompressed[]) {
    int i = 0, k = 0;

    while (compressed[i] != '\0') {
        char ch = compressed[i++];

        int count = 0;

        while (compressed[i] >= '0' && compressed[i] <= '9') {
            count = count * 10 + (compressed[i] - '0');
            i++;
        }

        for (int j = 0; j < count; j++) {
            decompressed[k++] = ch;
        }
    }

    decompressed[k] = '\0';
}

int main() {

    char str[MAX];
    char compressed[MAX];
    char decompressed[MAX];

    printf("Enter a string: ");
    scanf("%s", str);

    compress(str, compressed);

    printf("\nCompressed string: %s\n", compressed);

    decompress(compressed, decompressed);

    printf("Decompressed string: %s\n", decompressed);

    return 0;
}