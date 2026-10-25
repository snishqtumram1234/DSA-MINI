// stack.h
// STACK: used to trace a leaked packet BACK to the printing press.
// We go from packet -> centre -> district -> state -> press and PUSH each one.
// Then we POP them, which prints them in the correct order: press first.
// (Last In, First Out)

#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

struct TreeNode;   // tells the compiler TreeNode exists (defined in tree.h)

class Stack {
private:
    TreeNode* arr[100];   // simple array to hold items
    int top;              // index of top item (-1 means empty)

public:
    Stack() {
        top = -1;
    }

    void push(TreeNode* node) {
        if (top == 99) {
            cout << "Stack is full!" << endl;
            return;
        }
        top++;
        arr[top] = node;
    }

    TreeNode* pop() {
        if (top == -1) {
            return NULL;   // stack is empty
        }
        TreeNode* node = arr[top];
        top--;
        return node;
    }

    bool isEmpty() {
        return top == -1;
    }
};

#endif
