#include <stdio.h>

int findComplement(int num) {
    unsigned int temp = num;
    unsigned int mask = 0;
    
    while (temp > 0) {
        mask = (mask << 1) | 1;
        temp >>= 1;
    }
    
    return num ^ mask;
}
