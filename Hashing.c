#include <stdio.h>
#include <stdlib.h>

// Structure to store order details
struct Order {
    int orderNumber;
    int time;
    int duration;
};

// Structure for hash table node
struct HashNode {
    struct Order order;
    struct HashNode* next;
};

// Function to perform bubble sort based on order number
void sortOrders(struct Order orders[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (orders[j].orderNumber > orders[j + 1].orderNumber) {
                // Swap the orders
                struct Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
}

// Function to print orders
void printOrders(struct Order orders[], int n) {
    printf("\nOrder in which students will receive their orders:\n");
    for (int i = 0; i < n; i++) {
        printf("Order %d\n", orders[i].orderNumber);
    }
}

int main() {
    int n;

    // Input number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Order orders[n];

    // Input order details
    for (int i = 0; i < n; i++) {
        orders[i].orderNumber = i + 1;
        printf("Enter the order time and processing time for student %d: ", i + 1);
        scanf("%d %d", &orders[i].time, &orders[i].duration);
    }   

    // Create a hash table
    const int HASH_SIZE = 10;  // Prime number for better distribution
    struct HashNode* hashTable[HASH_SIZE] = {NULL};
    // Insert orders into the hash table based on completion time
    for (int i = 0; i < n; i++) {
        int completionTime = orders[i].time + orders[i].duration;

        // Hash function to determine the index in the hash table
        int index = completionTime % HASH_SIZE;

        // Create a new node for the order
        struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
        newNode->order = orders[i];
        newNode->next = NULL;

        // Insert the new node into the hash table
        if (hashTable[index] == NULL) {
            hashTable[index] = newNode;
        } else {
            // If there is a collision, append the new node to the linked list
            struct HashNode* current = hashTable[index];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Traverse the hash table and collect the orders in sorted order
    int count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        struct HashNode* current = hashTable[i];
        while (current != NULL) {
            orders[count++] = current->order;
            current = current->next;
        }
    }

    // Sort the orders based on order number if completion times are the same
    sortOrders(orders, n);

    // Print the order in which students will receive their orders
    printOrders(orders, n);

    // Free allocated memory
    for (int i = 0; i < HASH_SIZE; i++) {
        struct HashNode* current = hashTable[i];
        while (current != NULL) {
            struct HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return 0;
}