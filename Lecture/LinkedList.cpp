#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// A simple linked-list Node:
struct Node {
    std::string data;
    Node* next;
    Node(const std::string &d, Node* n = nullptr)
        : data(d), next(n) {}
};

// 1. Print list from head to tail: Iterative
void printListIterative(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data;
        if (curr->next != nullptr) {
            std::cout << "->";
        }
        curr = curr->next; 
    }
    std::cout << std::endl;
}

// 1. Print list from head to tail: Recursive
void printListRecursive(Node* head) {
    if (head == nullptr) {
        std::cout << std::endl;
        return;
    }
    std::cout << head->data;
    if (head->next != nullptr) {
        std::cout << "->";
    }
    printListRecursive(head->next);
}

// 2. Copy list elements to a vector: Iterative
std::vector<std::string> copyToVectorIterative(Node* head) {
    std::vector<std::string> result;
    Node* curr = head;
    while (curr != nullptr) {
        result.push_back(curr->data);
        curr = curr->next;
    }
    return result;
}

// 2. Copy list elements to a vector: Recursive
void copyHelper(Node* head, std::vector<std::string> &vec) {
    if (head == nullptr) return;
    vec.push_back(head->data);
    copyHelper(head->next, vec);
}
std::vector<std::string> copyToVectorRecursive(Node* head) {
    std::vector<std::string> result;
    copyHelper(head, result);
    return result;
}

// 3. Get element at index i (0 = head): Iterative
std::string getElementIterative(Node* head, int i) {
    Node* curr = head;
    int index = 0;
    while (curr != nullptr && index < i) {
        curr = curr->next;
        index++;
    }
    if (curr == nullptr) {
        throw std::out_of_range("Index too large for list");
    }
    return curr->data;
}

// 3. Get element at index i (0 = head): Recursive
std::string getElementRecursive(Node* head, int i) {
    if (head == nullptr) {
        throw std::out_of_range("Index too large for list");
    }
    if (i == 0) {
        return head->data;
    }
    return getElementRecursive(head->next, i - 1);
}

// 4. Check if the list has element "ATL": Iterative
bool hasElementATLIterative(Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        if (curr->data == "ATL") {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// 4. Check if the list has element "ATL": Recursive
bool hasElementATLRecursive(Node* head) {
    if (head == nullptr) return false;
    if (head->data == "ATL") return true;
    return hasElementATLRecursive(head->next);
}

int main() {
    // Build a simple list: LAX -> MSP -> ATL -> BOS
    Node* head = new Node("LAX");
    head->next = new Node("MSP");
    head->next->next = new Node("ATL");
    head->next->next->next = new Node("BOS");

    // 1. Print the list
    std::cout << "Iterative print: ";
    printListIterative(head);

    std::cout << "Recursive print: ";
    printListRecursive(head);

    // 2. Copy to vector
    std::vector<std::string> vecIter = copyToVectorIterative(head);
    std::cout << "Iterative copy to vector: ";
    for (const auto &item : vecIter) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::vector<std::string> vecRec = copyToVectorRecursive(head);
    std::cout << "Recursive copy to vector: ";
    for (const auto &item : vecRec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // 3. Get element at index i
    try {
        std::cout << "Element at index 0 (iterative): "
                  << getElementIterative(head, 0) << std::endl;
        std::cout << "Element at index 2 (iterative): "
                  << getElementIterative(head, 2) << std::endl;
        std::cout << "Element at index 0 (recursive): "
                  << getElementRecursive(head, 0) << std::endl;
        std::cout << "Element at index 2 (recursive): "
                  << getElementRecursive(head, 2) << std::endl;
    } catch (std::out_of_range &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 4. Check if list has "ATL"
    std::cout << std::boolalpha;
    std::cout << "Iterative hasElementATL? "
              << hasElementATLIterative(head) << std::endl;
    std::cout << "Recursive hasElementATL? "
              << hasElementATLRecursive(head) << std::endl;

    // Clean up memory
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
