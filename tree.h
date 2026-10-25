// tree.h
// TREE: shows how question papers travel.
// Printing Press (root) -> State -> District -> Exam Centre -> Packet (leaf)
// Each node has a parent pointer (to go UP) and children (to go DOWN).

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include "linkedlist.h"
#include "stack.h"
using namespace std;

struct TreeNode {
    string name;              // e.g. "Pune" or "PKT-103"
    string type;              // e.g. "District", "Packet"
    TreeNode* parent;         // node above it
    TreeNode* children[10];   // nodes below it
    int childCount;
    CustodyLog log;           // linked list of events at this node
};

// Create a new node
TreeNode* createNode(string name, string type) {
    TreeNode* node = new TreeNode;
    node->name = name;
    node->type = type;
    node->parent = NULL;
    node->childCount = 0;
    return node;
}

// Connect child under parent
void addChild(TreeNode* parent, TreeNode* child) {
    parent->children[parent->childCount] = child;
    parent->childCount++;
    child->parent = parent;
}

// Print the whole tree with indentation (recursion)
void printTree(TreeNode* node, int level) {
    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << "|-- " << node->name << " (" << node->type << ")" << endl;

    for (int i = 0; i < node->childCount; i++) {
        printTree(node->children[i], level + 1);
    }
}

// Search a node by name (recursion)
TreeNode* findNode(TreeNode* node, string name) {
    if (node == NULL) return NULL;
    if (node->name == name) return node;

    for (int i = 0; i < node->childCount; i++) {
        TreeNode* found = findNode(node->children[i], name);
        if (found != NULL) return found;
    }
    return NULL;
}

// MAIN FEATURE: trace a leaked packet back to the press
void traceLeak(TreeNode* root, string packetCode) {
    TreeNode* packet = findNode(root, packetCode);

    if (packet == NULL) {
        cout << "Packet " << packetCode << " not found!" << endl;
        return;
    }

    // Step 1: go UP from packet to root, pushing each node
    Stack s;
    TreeNode* current = packet;
    while (current != NULL) {
        s.push(current);
        current = current->parent;
    }

    // Step 2: pop each node -> prints from press down to packet
    cout << "\n===== CHAIN OF CUSTODY FOR " << packetCode << " =====" << endl;
    int step = 1;
    while (!s.isEmpty()) {
        TreeNode* node = s.pop();
        cout << "\nStep " << step << ": " << node->name
             << " (" << node->type << ")" << endl;
        node->log.printLog();     // print linked list log of this node
        step++;
    }
    cout << "\nEveryone listed above handled this packet before the leak." << endl;
}

#endif
