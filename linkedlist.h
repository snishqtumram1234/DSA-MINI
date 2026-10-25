// linkedlist.h
// LINKED LIST: stores the custody log of a packet / centre.
// Every time something happens (received, seal checked, opened),
// we add a new entry at the END of the list. Order = time order.

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

// One entry in the log
struct LogNode {
    string time;     // e.g. "08:30 AM"
    string event;    // e.g. "Received by Supervisor Rahul"
    LogNode* next;   // pointer to next entry
};

class CustodyLog {
private:
    LogNode* head;   // first entry
    LogNode* tail;   // last entry (so adding at end is fast)

public:
    CustodyLog() {
        head = NULL;
        tail = NULL;
    }

    // Add a new entry at the end of the list
    void addEntry(string time, string event) {
        LogNode* newNode = new LogNode;
        newNode->time = time;
        newNode->event = event;
        newNode->next = NULL;

        if (head == NULL) {          // list is empty
            head = newNode;
            tail = newNode;
        } else {                     // attach after last node
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Print all entries from first to last
    void printLog() {
        if (head == NULL) {
            cout << "        (no log entries)" << endl;
            return;
        }
        LogNode* temp = head;
        while (temp != NULL) {
            cout << "        [" << temp->time << "] " << temp->event << endl;
            temp = temp->next;
        }
    }
};

#endif
