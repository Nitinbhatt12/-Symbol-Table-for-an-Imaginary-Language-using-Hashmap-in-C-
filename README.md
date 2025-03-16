# Symbol Table for an Imaginary Language using Hashmap in C

This project implements a **symbol table** for an imaginary programming language using a **hashmap** in C. The symbol table is responsible for managing variables and their values across different scopes, supporting features like variable shadowing and dynamic typing.

## Features

- **Symbol Table**: Manages variables and their values using a hashmap.
- **Dynamic Typing**: Supports variables of type `int`, `float`, and `string`.
- **Nested Scopes**: Allows creating and managing nested scopes, with variable shadowing.
- **Collision Handling**: Uses chaining (linked lists) to handle hash collisions.
- **File Input**: Reads commands from a file (`program.txt`) to perform assignments and print operations.
- **Type Detection**: Automatically detects the type of the value being assigned (integer, float, or string).

## What is a Symbol Table?

A **symbol table** is a data structure used by compilers and interpreters to store information about variables, functions, and other symbols in a program. It typically supports:
- **Variable storage**: Storing variable names and their values.
- **Scope management**: Handling nested scopes and variable shadowing.
- **Type information**: Storing and retrieving the type of variables.

In this project, the symbol table is implemented using a **hashmap**, which provides efficient lookup, insertion, and deletion of variables.

## Project Structure

- **`hashmap.h`**: Header file containing the definitions for the hashmap, node structure, and function prototypes.
- **`hashmap.c`**: Implementation of the hashmap functions, including insertion, display, and scope management.
- **`wtof.c`**: Main program that reads commands from `program.txt` and interacts with the symbol table.
- **`id.c`**: Helper program to demonstrate type detection and value printing (not directly used in the symbol table but provided for reference).
- **`program.txt`**: Input file containing commands like `begin`, `end`, `assign`, and `print`.

## How It Works

1. **Hash Function**: Uses a modified DJB2 hash function to map variable names to indices in the hash table.
2. **Insertion**: Inserts a variable and its value into the symbol table. The value can be an integer, float, or string.
3. **Scope Management**:
   - `begin`: Creates a new nested scope.
   - `end`: Ends the current scope and reverts to the parent scope.
4. **Type Detection**: Automatically detects the type of the value being assigned (integer, float, or string) and stores it accordingly.
5. **Lookup and Display**: Retrieves and prints the value associated with a variable, respecting the scope hierarchy.

## Example Input (`program.txt`)

```plaintext
begin
assign a 1
assign b 2.5
begin
assign a "hello"
print a
print b
end
print a
end
