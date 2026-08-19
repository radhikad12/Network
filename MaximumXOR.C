#include <stdbool.h>

typedef struct {
    int* keys;
    int size;
} HashSet;

void insert(HashSet* set, int key) {
    int idx = abs(key) % set->size;
    while (set->keys[idx] != -1) {
        if (set->keys[idx] == key) return;
        idx = (idx + 1) % set->size;
    }
    set->keys[idx] = key;
}

bool contains(HashSet* set, int key) {
    int idx = abs(key) % set->size;
    while (set->keys[idx] != -1) {
        if (set->keys[idx] == key) return true;
        idx = (idx + 1) % set->size;
    }
    return false;
}

int findMaximumXOR(int* nums, int numsSize) {
    int max_result = 0;
    int mask = 0;
    int hash_size = numsSize * 2;
    
    int* hash_keys = (int*)malloc(hash_size * sizeof(int));
    HashSet set = {hash_keys, hash_size};

    for (int i = 30; i >= 0; i--) {
        mask |= (1 << i);
        
        for (int j = 0; j < hash_size; j++) {
            hash_keys[j] = -1;
        }

        for (int j = 0; j < numsSize; j++) {
            insert(&set, nums[j] & mask);
        }

        int target = max_result | (1 << i);
        for (int j = 0; j < numsSize; j++) {
            int prefix = nums[j] & mask;
            if (contains(&set, prefix ^ target)) {
                max_result = target;
                break;
            }
        }
    }

    free(hash_keys);
    return max_result;
}
