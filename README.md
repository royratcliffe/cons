# Cons---a C99 library for simple Lisp-like singly-linked lists

Inspired by Lisp, "Cons" is a lightweight C99 library that provides a clean, efficient implementation of singly-linked lists. Designed for simplicity and performance, it offers essential operations for managing dynamic collections of data in C programs without the overhead of other dependencies.

## Features

-   Singly-Linked Lists

    -   Core data structure for efficient list management

-   Hierarchical Nodes

    -   Support for nested lists, allowing for complex data structures

-   Simple API

    -   Intuitive Lisp-like functions for list operations like `cons`, `cons_car`, and `cons_cdr`

-   Dynamic Collections

    -   Functions for constructing and modifying lists from caller-managed nodes; allocation and deallocation remain the caller's responsibility

-   Documentation

    -   Comprehensive API documentation generated with Doxygen

## Usage

To use the Cons library, include the header file and link against the compiled library in your C project. The API provides functions for constructing and manipulating lists, as well as traversing and modifying hierarchical node structures.

```c
#include "cons.h"

int main(void) {
    struct cons cell1 = CONS((void *)1, CONS_NIL);
    struct cons cell2 = CONS((void *)2, CONS_NIL);
    struct cons *head = CONS_NIL;

    cons(&head, &cell1);
    cons(&head, &cell2);

    return 0;
}
```

What does this code do? It constructs two cons cells, `cell1` and `cell2`, with values `1` and `2` respectively. It then constructs a list by prepending these cells to the `head` pointer, resulting in a list that contains both cells.
