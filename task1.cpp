#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>  
#include <cctype>     
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};
Node* buildTreeHelper(stack<char> &st){
    if(st.empty() || st.top()==')' || st.top()==',' ) return nullptr;
    if(isalpha(st.top())){
        Node* root = new Node(st.top());
        st.pop();
        if(!st.empty() &&  st.top()=='('){
            st.pop();
            root->left = buildTreeHelper(st);
            if(!st.empty() && st.top()==',') st.pop();
            root->right = buildTreeHelper(st);
            if(!st.empty() && st.top()==')') st.pop();
        }
        return root;
    }
    return nullptr;
}
Node* buildTree(const string& str) {
    stack<char> st;
    for (int i = static_cast<int>(str.size()) - 1; i >= 0; i--) {
        st.push(str[i]);
    }
    return buildTreeHelper(st);
}

void preorder(Node* root) {
    if(root==nullptr) return;
    cout<<root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    stack<Node*> st;
    Node* current = root;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout << current->data << " ";

        current = current->right;
    }
}
void postorder(Node* root) {
    stack<Node*> st;
    Node* current = root;
    Node* lastVisited = nullptr;

    while (current != nullptr || !st.empty()) {
        while (current != nullptr) {
            st.push(current);
            current = current->left;
        }

        Node* node = st.top();

        if (node->right != nullptr && lastVisited != node->right) {
            current = node->right;
        } else {
            cout << node->data << " ";
            st.pop();
            lastVisited = node;
        }
    }
}

bool validateSubtree(const string& str, int& index) {
    if (index >= str.size() ||
        !isalpha(static_cast<unsigned char>(str[index]))) {
        return false;
    }

    index++; 

    if (index < str.size() && str[index] == '(') {
        index++; 
        if (index < str.size() && str[index] != ',') {
            if (!validateSubtree(str, index))
                return false;
        }

        if (index >= str.size() || str[index] != ',')
            return false;

        index++; 
        if (index < str.size() && str[index] != ')') {
            if (!validateSubtree(str, index))
                return false;
        }

        if (index >= str.size() || str[index] != ')')
            return false;

        index++; 
    }

    return true;
}

bool isValidTreeString(const string& str) {
    if (str.empty()) return false;

    int index = 0;

    return validateSubtree(str, index) &&
           index == str.size();
}

int height(Node* root) {
    if(root== nullptr) return -1;
    return 1+max(height(root->left),height(root->right));
}
void printDepths(Node* root, int depth) {
    if (root == nullptr) return;

    cout << root->data << ": " << depth << "\n";

    printDepths(root->left, depth + 1);
    printDepths(root->right, depth + 1);
}

BSTNode* insertBST(BSTNode* root, int value) {
    if (root == nullptr) {
        return new BSTNode(value);
    }

    if (value > root->data) {
        root->right = insertBST(root->right, value);
    } else if (value < root->data) {
        root->left = insertBST(root->left, value);
    }

    return root;
}
BSTNode* buildBST(const vector<int>& values) {
    BSTNode* root = nullptr;

    for (int value : values) {
        root = insertBST(root, value);
    }

    return root;
}

void inorderBST(BSTNode* root) {
    if (root == nullptr) return;

    inorderBST(root->left);
    cout << root->data << " ";
    inorderBST(root->right);
}

void deleteTree(Node* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void deleteBST(BSTNode* root) {
    if (root == nullptr) return;

    deleteBST(root->left);
    deleteBST(root->right);
    delete root;
}

int main() {
    string str = "a(b(d,e),c(,f(g,)))";

    cout << "Tree string: " << str << "\n";

    // Task 1
    if (!isValidTreeString(str)) {
        cout << "Invalid tree string.\n";
        return 0;
    }

    Node* root = buildTree(str);

    // Task 2
    cout << "\nPreorder: ";
    preorder(root);
    cout << "\n";

    // Task 3
    cout << "Inorder: ";
    inorder(root);
    cout << "\n";

    // Task 4
    cout << "Postorder: ";
    postorder(root);
    cout << "\n";

    // Task 5
    cout << "\nValid tree string: "
         << (isValidTreeString(str) ? "Yes" : "No")
         << "\n";

    // Task 6
    cout << "\nTree height: " << height(root) << "\n";

    cout << "Node depths:\n";
    printDepths(root, 0);

    // Task 7
    vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    BSTNode* bstRoot = buildBST(values);

    cout << "\nBST inorder: ";
    inorderBST(bstRoot);
    cout << "\n";

    deleteTree(root);
    deleteBST(bstRoot);

    return 0;
}