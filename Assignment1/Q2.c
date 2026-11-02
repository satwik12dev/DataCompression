#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100];

    printf("Enter first string: ");
    scanf("%s", str1);

    printf("Enter second string: ");
    scanf("%s", str2);

    if (strncmp(str1, str2, strlen(str1)) == 0) {
        printf("First string is a prefix of second string.\n");
    }
    else if (strncmp(str2, str1, strlen(str2)) == 0) {
        printf("Second string is a prefix of first string.\n");
    }
    else {
        printf("Neither string is a prefix of the other.\n");
    }

    return 0;
}