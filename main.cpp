// main.cpp
// Exam Paper Leak Tracing System
// Compile:  g++ main.cpp -o leak
// Run:      ./leak        (on Windows: leak.exe)

#include <iostream>
#include <string>
#include "tree.h"
using namespace std;

int main() {
    // ---------- BUILD THE TREE ----------
    TreeNode* press = createNode("Govt Printing Press", "Press");

    TreeNode* state = createNode("Maharashtra Board", "State");
    addChild(press, state);

    TreeNode* pune   = createNode("Pune", "District");
    TreeNode* mumbai = createNode("Mumbai", "District");
    addChild(state, pune);
    addChild(state, mumbai);

    TreeNode* c1 = createNode("Fergusson College", "Exam Centre");
    TreeNode* c2 = createNode("COEP", "Exam Centre");
    TreeNode* c3 = createNode("St. Xavier's", "Exam Centre");
    addChild(pune, c1);
    addChild(pune, c2);
    addChild(mumbai, c3);

    TreeNode* p1 = createNode("PKT-101", "Packet");
    TreeNode* p2 = createNode("PKT-102", "Packet");
    TreeNode* p3 = createNode("PKT-103", "Packet");
    TreeNode* p4 = createNode("PKT-104", "Packet");
    addChild(c1, p1);
    addChild(c2, p2);
    addChild(c2, p3);
    addChild(c3, p4);

    // ---------- ADD LOGS (LINKED LIST) ----------
    press->log.addEntry("01 Mar 10:00", "Papers printed, sealed by Mr. Sharma");
    state->log.addEntry("02 Mar 09:00", "Received at board strong room");
    pune->log.addEntry("03 Mar 11:00", "Received by District Officer Mr. Patil");
    c2->log.addEntry("05 Mar 07:30", "Received by Centre Head Mrs. Joshi");
    c2->log.addEntry("05 Mar 07:45", "Stored in centre locker");

    p3->log.addEntry("05 Mar 08:40", "Seal checked by Supervisor Rahul");
    p3->log.addEntry("05 Mar 08:50", "Seal found TORN - not reported!");
    p3->log.addEntry("05 Mar 09:00", "Packet opened in Room 12");

    p2->log.addEntry("05 Mar 08:45", "Seal checked by Supervisor Anita - OK");
    p2->log.addEntry("05 Mar 09:00", "Packet opened in Room 11");

    // ---------- MENU ----------
    int choice;
    string code;

    while (true) {
        cout << "\n========== EXAM PAPER LEAK TRACER ==========" << endl;
        cout << "1. Show distribution tree" << endl;
        cout << "2. Trace a leaked packet" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- Distribution Tree ---" << endl;
            printTree(press, 0);
        }
        else if (choice == 2) {
            cout << "Enter packet code found on leaked photo (e.g. PKT-103): ";
            cin >> code;
            traceLeak(press, code);
        }
        else if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
