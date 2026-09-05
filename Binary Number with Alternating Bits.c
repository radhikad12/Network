#include <stdbool.h>

bool hasAlternatingBits(int n) {

    int lastBit = n % 2;
    n = n / 2;

    while (n > 0) {

        int currentBit = n % 2;

        if (currentBit == lastBit) {
            return false;
        }

        lastBit = currentBit;
        n = n / 2;
    }

    return true;
}
