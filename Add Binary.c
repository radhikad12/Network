#include <stdlib.h>
#include <string.h>

char* addBinary(char* a, char* b) {

    int i = strlen(a) - 1;
    int j = strlen(b) - 1;

    int maxLen = (strlen(a) > strlen(b)) ? strlen(a) : strlen(b);

    char *result = (char *)malloc(maxLen + 2);

    int k = 0;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) {

        int sum = carry;

        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }

        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }

        result[k++] = (sum % 2) + '0';
        carry = sum / 2;
    }

    result[k] = '\0';

    int left = 0;
    int right = k - 1;

    while (left < right) {
        char temp = result[left];
        result[left] = result[right];
        result[right] = temp;
        left++;
        right--;
    }

    return result;
}
