#include <iostream>
#include <string>

using namespace std;

struct TaskNode {
    int taskID;
    string description;
    int priority;
    TaskNode* next;
    TaskNode(int id, string desc, int prio) : taskID(id), description(desc), priority(prio), next(NULL) {}
};

class TaskManager {
private:
    TaskNode* head;
public:
    TaskManager() : head(NULL) {}

    // To add a new task
    void addTask(int id, string desc, int prio) {
        TaskNode* newTask = new TaskNode(id, desc, prio);
        
        if (!head || head->priority < prio) {
            newTask->next = head;
            head = newTask;
            return;
        }
		TaskNode* current = head;
        while (current->next && current->next->priority >= prio) {
            current = current->next;
        }
        newTask->next = current->next;
        current->next = newTask;
    }

    // to display all tasks
    void displayTasks() {
        if (!head) {
            cout << "No tasks available." << endl;
            return;
        }

        TaskNode* current = head;
        cout << "Tasks List:" << endl;
        while (current) {
            cout << "ID: " << current->taskID << ", Description: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }
    
    // To remove highest priority task
    void removeHighestPriorityTask() {
        if (!head) {
            cout << "No tasks to remove." << endl;
            return;
        }
        
        TaskNode* temp = head;
        head = head->next;
        delete temp;
        cout << "Removed highest priority task." << endl;
    }

    // To remove a task by ID
    void removeTaskByID(int id) {
        if (!head) {
            cout << "No tasks to remove." << endl;
            return;
        }
        // task to remove head
        if (head->taskID == id) {
            TaskNode* temp = head;
            head = head->next;
            delete temp;
            cout << "Removed task with ID: " << id << endl;
            return;
        }
        // to find the task with the specified ID
        TaskNode* current = head;
        while (current->next && current->next->taskID != id) {
            current = current->next;
        }
        // If the task was found
        if (current->next) {
            TaskNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            cout << "Removed task with ID: " << id << endl;
        } else {
            cout << "Task with ID: " << id << " not found." << endl;
        }
    }

    // free memory allocated for the tasks
    ~TaskManager() {
        while (head) {
            removeHighestPriorityTask();
        }
    }
};

void displayMenu() {
    TaskManager taskManager;
    int choice, id, priority;
    string description;

    do {
        cout << "\nTask Management System" << endl;
        cout << "1. Add a new Task" << endl;
        cout << "2. View all Tasks" << endl;
        cout << "3. Remove Highest Priority Task" << endl;
        cout << "4. Remove Task by ID" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cout << "Enter Task Description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter Priority Level: ";
                cin >> priority;
                taskManager.addTask(id, description, priority);
                break;
            case 2:
                taskManager.displayTasks();
                break;
            case 3:
                taskManager.removeHighestPriorityTask();
                break;
            case 4:
                cout << "Enter Task ID to remove: ";
                cin >> id;
                taskManager.removeTaskByID(id);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    displayMenu();
    return 0;
}
