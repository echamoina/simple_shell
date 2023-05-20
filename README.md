# Simple_Shell
The 1st group project

## Main objective
Write a basic shell that prints a prompt, waits for user to enter
a command and prints what they enetered on the next line.

## Two process to-do

    1. Printing the prompt
    2. Reading and printing what the end user types out.

## Exercises

### 0. printenv with environ

Write a program that prints the environment using the global variable environ.

### 1. env vs environ
Write a program that prints the address of env (the third parameter of the main function) and environ (the global variable). Are they they same? Does this make sense?

### 2. getenv()
Write a function that gets an environment variable. (without using getenv)

    Prototype: char *_getenv(const char *name);
man 3 getenv

### 3. PATH
Write a function that prints each directory contained in the the environment variable PATH, one directory per line. 

### 4. PATH
Write a function that builds a linked list of the PATH directories.

## 5. setenv
Write a function that changes or adds an environment variable (without using setenv).

    Prototype: int _setenv(const char *name, const char *value, int overwrite);

man 3 setenv

### 6. unsetenv
Write a function that deletes the variable name from the environment (without using unsetenv).

    Prototype: int _unsetenv(const char *name);

man 3 unsetenv
