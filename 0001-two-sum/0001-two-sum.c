#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

#define SIZE 10007

int hash(int key) {
    return abs(key) % SIZE;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Node* table[SIZE] = {NULL};

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];

        // Search for complement
        int h = hash(complement);
        Node* curr = table[h];

        while (curr) {
            if (curr->key == complement) {
                int* result = (int*)malloc(2 * sizeof(int));
                result[0] = curr->value;
                result[1] = i;
                *returnSize = 2;
                return result;
            }
            curr = curr->next;
        }

        // Insert current number
        h = hash(nums[i]);

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = nums[i];
        newNode->value = i;
        newNode->next = table[h];
        table[h] = newNode;
    }

    *returnSize = 0;
    return NULL;
}