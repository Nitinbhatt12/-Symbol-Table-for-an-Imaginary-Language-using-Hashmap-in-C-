#ifndef HASHMAP_H
#define HASHMAP_H

#define SIZE 200

// Define a union to store different types of data
union Data {
    int i;
    float f;
    char str[100];
};

// Define an enum for different types
enum DataType {
    INT,
    FLOAT,
    STRING
};

typedef struct hashmap_node {
    char key[100];
    union Data value;  // Use union for value
    enum DataType type;  // Add type information
    struct hashmap_node* next;
} Node;

typedef struct hashmap {
    Node* table[SIZE];
    struct hashmap* parent;  // Pointer to the parent scope
} Hashtable;

int hashfunction(char* s);
void insert(Hashtable* ht, char* key, union Data value, enum DataType type);
void display(Hashtable* ht, char* key);
void end(Hashtable* ht);
Hashtable* make(Hashtable* parent);

#endif // HASHMAP_H