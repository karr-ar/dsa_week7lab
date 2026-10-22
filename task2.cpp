#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    int studentID;
    string name;
    float GPA;
    Student* left;
    Student* right;

    Student(int id, string studentName, float gpa) {
        studentID = id;
        name = studentName;
        GPA = gpa;
        left = nullptr;
        right = nullptr;
    }
};

Student* insert(Student* root, int id, string name, float gpa) {
    if (root == nullptr)
        return new Student(id, name, gpa);

    if (id < root->studentID)
        root->left = insert(root->left, id, name, gpa);
    else if (id > root->studentID)
        root->right = insert(root->right, id, name, gpa);
    else
        cout << "Student ID " << id << " already exists.\n";

    return root;
}

Student* search(Student* root, int id) {
    if (root == nullptr || root->studentID == id)
        return root;

    if (id < root->studentID)
        return search(root->left, id);

    return search(root->right, id);
}

void displayStudent(Student* student) {
    if (student == nullptr) return;

    cout << student->studentID << " | "
         << student->name << " | GPA: "
         << student->GPA << "\n";
}

void inorder(Student* root) {
    if (root == nullptr) return;

    inorder(root->left);
    displayStudent(root);
    inorder(root->right);
}

Student* deleteStudent(Student* root, int id) {
    if (root == nullptr) return nullptr;

    if (id < root->studentID) {
        root->left = deleteStudent(root->left, id);
    } else if (id > root->studentID) {
        root->right = deleteStudent(root->right, id);
    } else {
        if (root->left == nullptr) {
            Student* child = root->right;
            delete root;
            return child;
        }

        if (root->right == nullptr) {
            Student* child = root->left;
            delete root;
            return child;
        }

        Student* successor = root->right;
        while (successor->left != nullptr)
            successor = successor->left;

        root->studentID = successor->studentID;
        root->name = successor->name;
        root->GPA = successor->GPA;

        root->right = deleteStudent(root->right,
                                    successor->studentID);
    }

    return root;
}

int countStudents(Student* root) {
    if (root == nullptr) return 0;

    return 1 + countStudents(root->left)
             + countStudents(root->right);
}

void findGPAExtremes(Student* root,
                     Student*& lowest,
                     Student*& highest) {
    if (root == nullptr) return;

    if (lowest == nullptr || root->GPA < lowest->GPA)
        lowest = root;

    if (highest == nullptr || root->GPA > highest->GPA)
        highest = root;

    findGPAExtremes(root->left, lowest, highest);
    findGPAExtremes(root->right, lowest, highest);
}

void displayWithGPA(Student* root, float gpa) {
    if (root == nullptr) return;

    displayWithGPA(root->left, gpa);

    if (root->GPA == gpa)
        displayStudent(root);

    displayWithGPA(root->right, gpa);
}

int displayAboveGPA(Student* root, float threshold) {
    if (root == nullptr) return 0;

    int count = displayAboveGPA(root->left, threshold);

    if (root->GPA > threshold) {
        displayStudent(root);
        count++;
    }

    count += displayAboveGPA(root->right, threshold);
    return count;
}

void deleteTree(Student* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << fixed << setprecision(2);

    Student* root = nullptr;

    root = insert(root, 50, "Ali", 3.50);
    root = insert(root, 30, "Sara", 3.90);
    root = insert(root, 70, "Ahmed", 2.80);
    root = insert(root, 20, "Hina", 3.20);
    root = insert(root, 40, "Usman", 2.50);
    root = insert(root, 60, "Zain", 3.70);
    root = insert(root, 80, "Ayesha", 3.40);

    cout << "STUDENT RECORD MANAGEMENT SYSTEM\n";

    cout << "\nStudents sorted by ID:\n";
    inorder(root);

    cout << "\nTotal students: " << countStudents(root) << "\n";

    cout << "\nSearching for student ID 40:\n";
    Student* found = search(root, 40);

    if (found != nullptr)
        displayStudent(found);
    else
        cout << "Student not found.\n";

    cout << "\nSearching for student ID 99:\n";
    found = search(root, 99);

    if (found != nullptr)
        displayStudent(found);
    else
        cout << "Student not found.\n";

    Student* lowest = nullptr;
    Student* highest = nullptr;
    findGPAExtremes(root, lowest, highest);

    if (highest != nullptr) {
        cout << "\nStudent(s) with highest GPA:\n";
        displayWithGPA(root, highest->GPA);

        cout << "\nStudent(s) with lowest GPA:\n";
        displayWithGPA(root, lowest->GPA);
    }

    float threshold;
    cout << "\nEnter GPA threshold: ";

    if (!(cin >> threshold)) {
        cout << "Invalid input.\n";
        deleteTree(root);
        return 0;
    }

    cout << "\nStudents with GPA above " << threshold << ":\n";
    if (displayAboveGPA(root, threshold) == 0)
        cout << "No matching students.\n";

    // Demonstrate all three deletion cases.
    cout << "\nDeleting ID 20 (leaf node):\n";
    root = deleteStudent(root, 20);
    inorder(root);

    cout << "\nDeleting ID 30 (one child):\n";
    root = deleteStudent(root, 30);
    inorder(root);

    cout << "\nDeleting ID 50 (two children):\n";
    root = deleteStudent(root, 50);
    inorder(root);

    cout << "\nRemaining students: " << countStudents(root) << "\n";

    deleteTree(root);
    return 0;
}