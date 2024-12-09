#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>  // Ensure this is included

using namespace std;

// Binary Tree Node
// Binary Tree Node
class BinaryTree {
public:
    int value;
    BinaryTree* left;
    BinaryTree* right;

    BinaryTree(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }

    // Insert value into the binary tree (make it virtual)
    virtual void insert(int val) {
        if (val < value) {
            if (left == nullptr) {
                left = new BinaryTree(val);
            } else {
                left->insert(val);
            }
        } else {
            if (right == nullptr) {
                right = new BinaryTree(val);
            } else {
                right->insert(val);
            }
        }
    }

    // Inorder traversal of the tree
    void inorder() {
        if (left) left->inorder();
        cout << value << " ";
        if (right) right->inorder();
    }

    // Virtual search function for BinaryTree (it does nothing by default)
    virtual bool search(int val) {
        return false;  // Default implementation returns false
    }
};


// Binary Search Tree class (overrides insert and search methods)
class BinarySearchTree : public BinaryTree {
public:
    BinarySearchTree(int val) : BinaryTree(val) {}

    // Insert value into the binary search tree
    void insert(int val) override {
        if (val < value) {
            if (left == nullptr) {
                left = new BinarySearchTree(val);
            } else {
                left->insert(val);
            }
        } else {
            if (right == nullptr) {
                right = new BinarySearchTree(val);
            } else {
                right->insert(val);
            }
        }
    }

    // Search for a value in the binary search tree
    bool search(int val) override {
        // If the value is equal to the current node, return true
        if (val == value) return true;

        // If the value is smaller and left subtree exists, search in the left subtree
        if (val < value && left != nullptr) return left->search(val);

        // If the value is larger and right subtree exists, search in the right subtree
        if (val > value && right != nullptr) return right->search(val);

        // If no match found, return false
        return false;
    }

    // Delete a node in the binary search tree
    BinaryTree* deleteNode(BinaryTree* root, int key) {
        if (root == nullptr) return root; // Base case: tree is empty

        // Traverse the tree to find the node to delete
        if (key < root->value) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->value) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node to delete found

            // Case 1: Node with only one child or no child
            if (root->left == nullptr) {
                BinaryTree* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                BinaryTree* temp = root->left;
                delete root;
                return temp;
            }

            // Case 2: Node with two children
            // Find the inorder successor (smallest value in the right subtree)
            BinaryTree* temp = minValueNode(root->right);

            // Copy the inorder successor's value to this node
            root->value = temp->value;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->value);
        }

        return root;
    }

private:
    // Helper function to find the minimum value node in the tree
    BinaryTree* minValueNode(BinaryTree* node) {
        BinaryTree* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
};


// Min Heap class
class MinHeap {
public:
    vector<int> heap;

    // Heapify function to create a Min Heap
    void heapify(vector<int>& arr) {
        heap = arr;
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

    // Heapify down to maintain the Min Heap property
    void heapifyDown(int i) {
        int n = heap.size();
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] < heap[smallest]) {
            smallest = left;
        }

        if (right < n && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    // Get the heap
    void printHeap() {
        for (int num : heap) {
            cout << num << " ";
        }
        cout << endl;
    }
};

// Max Heap class
class MaxHeap {
public:
    vector<int> heap;

    // Heapify function to create a Max Heap
    void heapify(vector<int>& arr) {
        heap = arr;
        int n = heap.size();
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

    // Heapify down to maintain the Max Heap property
    void heapifyDown(int i) {
        int n = heap.size();
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < n && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapifyDown(largest);
        }
    }

    // Get the heap
    void printHeap() {
        for (int num : heap) {
            cout << num << " ";
        }
        cout << endl;
    }
};

// Function to convert string to lowercase for case-insensitive comparison
string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);  // Ensure this works
    return lowerStr;
}

// Function to search for a topic and display related explanation
void dictionarySearch(const string& searchTerm) {  // Accept searchTerm as argument
    string lowerTerm = toLowerCase(searchTerm);

    if (lowerTerm == "binary tree") {
        cout <<endl<< "Binary Tree: A binary tree is a tree data structure where each node has at most two children, referred to as the left child and the right child.\n";
        cout <<endl<< "Enter values for Binary Tree (space-separated, end with -1): ";
        int val;
        cin >> val;
        BinaryTree bt(val);

        while (cin >> val && val != -1) {
            bt.insert(val);
        }
        cin.ignore();  // Clear newline after entering values

        cout << "Inorder Traversal: ";
        bt.inorder();
        cout << endl;

    } else if (lowerTerm == "binary search tree") {
        cout <<endl<< "Binary Search Tree: A binary search tree is a binary tree where the left child node contains a value smaller than its parent, "
             << "and the right child contains a value greater.\n";
        cout <<endl<< "Enter values for Binary Search Tree (space-separated, end with -1): ";
        int val;
        cin >> val;
        BinarySearchTree bst(val);

        while (cin >> val && val != -1) {
            bst.insert(val);
        }
        cin.ignore();  // Clear newline after entering values

        cout << "Inorder Traversal: ";
        bst.inorder();
        cout <<endl<< "\nEnter a value to search for: ";
        cin >> val;
         cin.ignore();
        cout << "Search for " << val << ": [STATUS] " << (bst.search(val) ? "Found" : "Not Found") << endl;

        cout <<endl<< "Enter a value to delete: ";
        cin >> val;
        cin.ignore();
        bst.deleteNode(&bst, val);
        cout << "Inorder Traversal after deletion: ";
        bst.inorder();
        cout << endl;

    } else if (lowerTerm == "heapify") {
        cout <<endl<< "Heapify: Heapify is the process of converting an array into a heap data structure, maintaining the heap property (either min-heap or max-heap).\n";
        cout <<endl<< "Enter values for array (space-separated, end with -1): ";
        vector<int> arr;
        int val;
        while (cin >> val && val != -1) {
            arr.push_back(val);
        }
        cin.ignore();  // Clear newline after entering values

        cout <<endl<< "Choose heap type: \n1. Min Heap\n2. Max Heap\n\nEnter 1 or 2: ";
        int choice;
        cin >> choice;
        cin.ignore();  // Clear newline after heap type input

        if (choice == 1) {
            MinHeap minHeap;
            minHeap.heapify(arr);
            cout << "The values you inputted: ";
            for (int num : arr) {
            cout << num << " ";
            }
            cout << endl;
            cout << "Min Heap: ";
            minHeap.printHeap();
        } else if (choice == 2) {
            MaxHeap maxHeap;
            maxHeap.heapify(arr);
            cout << "The values you inputted: ";
            for (int num : arr) {
            cout << num << " ";
            }
            cout << endl;

            cout << "Max Heap: ";
            maxHeap.printHeap();
        } else {
            cout << "Invalid choice.\n";
        }

    } else if (lowerTerm == "min heap") {
        cout <<endl<< "Min Heap: A min-heap is a binary tree where the parent node is less than or equal to its children, and the smallest element is at the root.\n";
        cout <<endl<< "Enter values for Min Heap (space-separated, end with -1): ";
        vector<int> arr;
        int val;
        while (cin >> val && val != -1) {
            arr.push_back(val);
        }
        cin.ignore();  // Clear newline after entering values

        MinHeap minHeap;
        minHeap.heapify(arr);
        cout << "The values you inputted: ";
        for (int num : arr) {
        cout << num << " ";
        }
        cout <<endl<< "Min Heap: ";
        minHeap.printHeap();

    } else if (lowerTerm == "max heap") {
        cout <<endl<< "Max Heap: A max-heap is a binary tree where the parent node is greater than or equal to its children, and the largest element is at the root.\n";
        cout <<endl<< "Enter values for Max Heap (space-separated, end with -1): ";
        vector<int> arr;
        int val;
        while (cin >> val && val != -1) {
            arr.push_back(val);
        }
        cin.ignore();  // Clear newline after entering values

        MaxHeap maxHeap;
        maxHeap.heapify(arr);
        cout << "The values you inputted: ";
        for (int num : arr) {
        cout << num << " ";
        }
        cout << endl;
        cout << "Max Heap: ";
        maxHeap.printHeap();

    } else {
        cout << "Topic not found.\n";
    }
}

int main() {
cout<<endl;
cout << "     ************************************************\n";
cout << "     *    WELCOME TO OUR MINI DIGITAL DICTIONARY    *\n";
cout << "     ************************************************\n";
cout <<endl;

cout << "     ************************************************\n";
cout << "     *   You can search for the following topics:   *\n";
cout << "     ************************************************\n";
cout << "     *                                              *\n";
cout << "     *                 Binary Tree                  *\n";
cout << "     *                                              *\n";
cout << "     *              Binary Search Tree              *\n";
cout << "     *                                              *\n";
cout << "     *                   Heapify                    *\n";
cout << "     *                                              *\n";
cout << "     *                  Min  Heap                   *\n";
cout << "     *                                              *\n";
cout << "     *                  Max  Heap                   *\n";
cout << "     *                                              *\n";
cout << "     ************************************************\n";

    // Infinite loop to allow multiple searches
    while (true) {
        string searchTerm;
        cout << "\n\nEnter a topic to learn about (or type 'exit' to quit): ";
        getline(cin, searchTerm);  // Get user input for topic

        if (toLowerCase(searchTerm) == "exit") {
            break;  // Exit the loop if user types 'exit'
        }

        dictionarySearch(searchTerm);  // Call dictionarySearch to display information
    }

    return 0;
}
