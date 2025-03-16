#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

// Improved hash function
int hashfunction(char* s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % SIZE;
}

// Insert a key-value pair into the hash table
void insert(Hashtable* ht, char* key, union Data value, enum DataType type) {
    int index = hashfunction(key);
    Node* newnode = (Node*)malloc(sizeof(Node));
    strcpy(newnode->key, key);
    newnode->value = value;
    newnode->type = type;
    newnode->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newnode;
    } else {
        // Handle collisions by adding to the linked list
        newnode->next = ht->table[index];
        ht->table[index] = newnode;
    }
}

// Display the value associated with a key
void display(Hashtable* ht, char* key) {
    Hashtable* current = ht;
    while (current != NULL) {
        int index = hashfunction(key);
        Node* temp = current->table[index];
        while (temp != NULL) {
            if (strcmp(temp->key, key) == 0) {
                switch (temp->type) {
                    case INT:
                        printf("%s = %d\n", key, temp->value.i);
                        return;
                    case FLOAT:
                        printf("%s = %.2f\n", key, temp->value.f);
                        return;
                    case STRING:
                        printf("%s = %s\n", key, temp->value.str);
                        return;
                    default:
                        printf("Unknown type for key '%s'\n", key);
                        return;
                }
            }
            temp = temp->next;
        }
        current = current->parent;  // Move to the parent scope
    }
    printf("Key '%s' not found\n", key);
}

// Free the hash table and its nodes
void end(Hashtable* ht) {
    for (int i = 0; i < SIZE; i++) {
        Node* temp = ht->table[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
        ht->table[i] = NULL;
    }
    free(ht);
    printf("End of Scope\n");
}

// Create and initialize a new hash table
Hashtable* make(Hashtable* parent) {
    Hashtable* ht = (Hashtable*)malloc(sizeof(Hashtable));
    for (int i = 0; i < SIZE; i++) {
        ht->table[i] = NULL;
    }
    ht->parent = parent;  // Link to the parent scope
    return ht;
}