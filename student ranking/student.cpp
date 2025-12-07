#include <iostream>
#include <string>
using namespace std;

struct Node {
    int roll;
    string name;
    double marks;
    Node* next;

    Node(int r, const string& n, double m) {
        roll = r;
        name = n;
        marks = m;
        next = NULL;
    }
};

class StudentList {
public:
    Node* head;

    StudentList() {
        head = NULL;
    }

    bool existsRoll(int roll) {
        Node* t = head;
        while (t) {
            if (t->roll == roll) return true;
            t = t->next;
        }
        return false;
    }

    void addStudent(int roll, const string& name, double marks) {
        if (existsRoll(roll)) {
            cout << "Roll number already exists.\n";
            return;
        }
        Node* n = new Node(roll, name, marks);

        if (!head) {
            head = n;
            cout << "Student added.\n";
            return;
        }

        Node* t = head;
        while (t->next) t = t->next;
        t->next = n;

        cout << "Student added.\n";
    }

    void viewStudents() {
        if (!head) {
            cout << "No students available.\n";
            return;
        }

        cout << "\n--- Student List (Insertion Order) ---\n";
        Node* t = head;
        while (t) {
            cout << "Roll: " << t->roll << " | Name: " << t->name 
                 << " | Marks: " << t->marks << '\n';
            t = t->next;
        }
    }

    int countStudents() {
        int c = 0;
        Node* t = head;
        while (t) {
            c++;
            t = t->next;
        }
        return c;
    }

    Node* searchByRoll(int roll) {
        Node* t = head;
        while (t) {
            if (t->roll == roll) return t;
            t = t->next;
        }
        return NULL;
    }

    int positionOfRoll(int roll) {
        Node* t = head;
        int pos = 1;
        while (t) {
            if (t->roll == roll) return pos;
            t = t->next;
            pos++;
        }
        return -1;
    }

    void deleteByRoll(int roll) {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        if (head->roll == roll) {
            Node* d = head;
            head = head->next;
            delete d;
            cout << "Student deleted.\n";
            return;
        }

        Node* t = head;
        while (t->next && t->next->roll != roll)
            t = t->next;

        if (!t->next) {
            cout << "Roll not found.\n";
            return;
        }

        Node* d = t->next;
        t->next = d->next;
        delete d;

        cout << "Student deleted.\n";
    }

    void clearAll() {
        Node* t;
        while (head) {
            t = head;
            head = head->next;
            delete t;
        }
        cout << "All records cleared.\n";
    }

    Node* mergeDesc(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;

        Node* result;

        if (a->marks >= b->marks) {
            result = a;
            result->next = mergeDesc(a->next, b);
        } else {
            result = b;
            result->next = mergeDesc(a, b->next);
        }
        return result;
    }

    void splitList(Node* source, Node** frontRef, Node** backRef) {
        Node* slow = source;
        Node* fast = source->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }

    void mergeSort(Node** headRef) {
        Node* h = *headRef;
        if (!h || !h->next) return;

        Node* a;
        Node* b;

        splitList(h, &a, &b);
        mergeSort(&a);
        mergeSort(&b);

        *headRef = mergeDesc(a, b);
    }

    void displayRankList() {
        if (!head) {
            cout << "No students available.\n";
            return;
        }

        mergeSort(&head);

        cout << "\n--- Rank List (1 = Top) ---\n";
        Node* t = head;
        int rank = 1;
        while (t) {
            cout << rank << ". Roll: " << t->roll 
                 << " | Name: " << t->name 
                 << " | Marks: " << t->marks << '\n';
            t = t->next;
            rank++;
        }
    }

    void displayTopper() {
        if (!head) {
            cout << "No students available.\n";
            return;
        }

        Node* t = head;
        Node* top = head;

        while (t) {
            if (t->marks > top->marks) top = t;
            t = t->next;
        }

        cout << "Topper -> Roll: " << top->roll 
             << " | Name: " << top->name 
             << " | Marks: " << top->marks << '\n';
    }
};

int main() {
    StudentList sl;
    int choice;

    while (true) {
        cout << "\n--- STUDENT RANKING SYSTEM ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Display Rank List\n";
        cout << "4. Display Topper\n";
        cout << "5. Search by Roll\n";
        cout << "6. Delete by Roll\n";
        cout << "7. Count Students\n";
        cout << "8. Clear All Records\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int r;
            double m;
            string name;

            cout << "Enter roll: ";
            cin >> r;
            cin.ignore();

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter marks: ";
            cin >> m;

            sl.addStudent(r, name, m);
        }

        else if (choice == 2) sl.viewStudents();
        else if (choice == 3) sl.displayRankList();
        else if (choice == 4) sl.displayTopper();

        else if (choice == 5) {
            int r;
            cout << "Enter roll: ";
            cin >> r;
            Node* f = sl.searchByRoll(r);

            if (f) {
                cout << "Found -> Roll: " << f->roll 
                     << " | Name: " << f->name 
                     << " | Marks: " << f->marks << '\n';
            } else cout << "Not found.\n";
        }

        else if (choice == 6) {
            int r;
            cout << "Enter roll to delete: ";
            cin >> r;
            sl.deleteByRoll(r);
        }

        else if (choice == 7) {
            cout << "Total students: " << sl.countStudents() << '\n';
        }

        else if (choice == 8) sl.clearAll();

        else if (choice == 9) {
            cout << "Exiting...\n";
            break;
        }

        else cout << "Invalid choice.\n";
    }

    return 0;
}