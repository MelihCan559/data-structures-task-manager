#include <iostream>
#include <string>
using namespace std;

struct Node {
    string task;
    Node* next;
};

Node* head = nullptr;
Node* tail = nullptr;
Node* deletedStack = nullptr;

void addTask(string taskName) {
    Node* newNode = new Node;
    newNode->task = taskName;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    cout << "Task added: " << taskName << endl;
}

void showTasks() {
    if (head == nullptr) {
        cout << "No tasks available." << endl;
        return;
    }

    Node* current = head;
    int count = 1;

    cout << "\nTask List:\n";
    while (current != nullptr) {
        cout << count << ". " << current->task << endl;
        current = current->next;
        count++;
    }
}

void processFirstTask() {
    if (head == nullptr) {
        cout << "No task to process." << endl;
        return;
    }

    Node* temp = head;
    cout << "Processing task: " << temp->task << endl;

    head = head->next;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete temp;
}

void deleteLastTask() {
    if (head == nullptr) {
        cout << "No task to delete." << endl;
        return;
    }

    if (head == tail) {
        Node* temp = head;

        Node* deletedNode = new Node;
        deletedNode->task = temp->task;
        deletedNode->next = deletedStack;
        deletedStack = deletedNode;

        cout << "Deleted task: " << temp->task << endl;

        head = nullptr;
        tail = nullptr;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != tail) {
        current = current->next;
    }

    Node* temp = tail;

    Node* deletedNode = new Node;
    deletedNode->task = temp->task;
    deletedNode->next = deletedStack;
    deletedStack = deletedNode;

    cout << "Deleted task: " << temp->task << endl;

    tail = current;
    tail->next = nullptr;
    delete temp;
}

void undoDelete() {
    if (deletedStack == nullptr) {
        cout << "No deleted task to restore." << endl;
        return;
    }

    Node* temp = deletedStack;
    string restoredTask = temp->task;
    deletedStack = deletedStack->next;

    addTask(restoredTask);

    cout << "Restored task: " << restoredTask << endl;

    delete temp;
}

int main() {
    int choice;
    string taskName;

    do {
        cout << "\n--- Task Manager ---\n";
        cout << "1. Add Task\n";
        cout << "2. Show Tasks\n";
        cout << "3. Process First Task\n";
        cout << "4. Delete Last Task\n";
        cout << "5. Undo Delete\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter task name: ";
            getline(cin, taskName);
            addTask(taskName);
            break;
        case 2:
            showTasks();
            break;
        case 3:
            processFirstTask();
            break;
        case 4:
            deleteLastTask();
            break;
        case 5:
            undoDelete();
            break;
        case 6:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }

    } while (choice != 6);

    return 0;
}