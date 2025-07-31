#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Node {
public:
    string elem;
    Node* left;
    Node* right;
    Node(const string & e, Node* l = nullptr, Node* r = nullptr) : elem(e), left(l), right(r) {} // define node consists of element, left element and right element
};

class LinkedBinaryTree {
public:
    LinkedBinaryTree() : score(0), root(nullptr) {} //Constructor of LinkedBinaryTree
    LinkedBinaryTree(const LinkedBinaryTree & other) { //deep copy of class
        root = copy(other.root);
        score = other.score;
    }
    LinkedBinaryTree & operator=(const LinkedBinaryTree & other) { // overload operator = 
        if (this != &other) {
            clear(root);
            root = copy(other.root);
            score = other.score;
        }
        return *this;
    }
    ~LinkedBinaryTree() {
        clear(root);
    }

    void printExpression() const {
        printExpression(root);
    }

    double evaluateExpression(double a, double b) const {
        return evaluateExpression(root, a, b);
    }

    double getScore() const {
        return score;
    }

    void setScore(double s) {
        score = s;
    }

    bool operator<(const LinkedBinaryTree & other) const {
        return score < other.score;
    }

    Node* getRoot() const {
        return root; 
    }
    
    void setRoot(Node* r) {
        root = r; 
    }

private:
    Node* root;   
    double score; 
    void printExpression(Node* t) const; //these functions are auxiliary function 
    double evaluateExpression(Node* t, double a, double b) const;
    Node* copy(Node* t);
    void clear(Node* t);
};

void LinkedBinaryTree::printExpression(Node* t) const {
    if (t != nullptr) { 
        if (t->left == nullptr && t->right == nullptr) {
            cout << t->elem;
        } else {
            if (t->elem == "abs") {
                cout << "abs(";
                printExpression(t->left); // abs only have left branch
                cout << ")";
            } else {
                cout << "(";
                printExpression(t->left); //recursion to left
                cout << t->elem;
                printExpression(t->right);// recursion to right 
                cout << ")";
            }
        }
    }
}

double LinkedBinaryTree::evaluateExpression(Node* t, double a, double b) const {
    if (t != nullptr) {
        if (t->left == nullptr && t->right == nullptr) {
            if (t->elem == "a") 
                return a;
            if (t->elem == "b")
                return b;
            return stod(t->elem); // change elem to double 
        } else {
            if (t->elem == "abs") {
                return fabs(evaluateExpression(t->left, a, b));
            }
            double leftval = evaluateExpression(t->left, a, b);  
            double rightval = evaluateExpression(t->right, a, b);
            if (t->elem == "+"){
                return leftval + rightval;
            }
            if (t->elem == "-"){
                return leftval - rightval;
            }
            if (t->elem == "*"){
                return leftval * rightval;
            }
            if (t->elem == "/"){
                return leftval / rightval; 
            }
            if (t->elem == ">"){
                if (leftval > rightval){
                    return 1;
                }
                else{
                    return -1;
                }
            }
        }
    }
    return 0;
}

Node* LinkedBinaryTree::copy(Node* t) {
    if (t == nullptr){
        return nullptr;
    }
    else{
        return new Node(t->elem, copy(t->left), copy(t->right));
    }
}

void LinkedBinaryTree::clear(Node* t) { // clear each leaves and root

    if (t != nullptr) {
        clear(t->left);
        clear(t->right);
        delete t;
    }
}

LinkedBinaryTree createExpressionTree(const string & postfix) {
    stack<Node*> st;
    istringstream iss(postfix); 
    string token;
    while (iss >> token) { // let token go to next position in the postfix one by one
        if (token != "+" && token != "-" && token != "*" && token != "/" && token != "abs" && token != ">") { // if double or constant 
            st.push(new Node(token)); //push double or constant into stack
        } else { 
            Node* newNode = new Node(token,nullptr,nullptr);// make a newnnode with this token and left and right branches to be NULL
            if (token == "abs") {  
                if (st.empty()) {
                    cerr << "Error: insufficient operands for operator " << token << endl;
                    continue;
                }
                newNode->left = st.top();//abs() left is in bracket 
                st.pop();
            } else { 
                if (st.size() < 2) {
                    cerr << "Error: insufficient operands for operator " << token << endl;
                    continue;
                }
                newNode->right = st.top(); // the right branch is the top in the stack
                st.pop();// pop the right 
                newNode->left = st.top();// the left branch is the top in stack now because right is pop
                st.pop();// pop the left
            }
            st.push(newNode);// push in the stack
        }
    }
    LinkedBinaryTree tree;
    if (!st.empty()) {
        tree.setRoot(st.top());
        st.pop();
    }
    return tree;
}

int main() {

    vector<LinkedBinaryTree> trees;
    ifstream exp_file("expressions.txt");
    if (!exp_file) {
        cerr << "Error opening expressions.txt" << endl;
        return 1;
    }
    string line;
    while (getline(exp_file, line)) {
        if (!line.empty()) {
            trees.push_back(createExpressionTree(line));
        }
    }
    exp_file.close();

    vector<vector<double>> inputs;
    ifstream input_file("input.txt");
    if (!input_file) {
        cerr << "Error opening input.txt" << endl;
        return 1;
    }
    while (getline(input_file, line)) {
        if (!line.empty()) {
            vector<double> ab_input;
            istringstream ss(line);
            string str;
            while (getline(ss, str, ' ')) {
                if (!str.empty()) {
                    ab_input.push_back(stod(str));
                }
            }
            inputs.push_back(ab_input);
        }
    }
    input_file.close();

    for (auto & t : trees) {
        double sum = 0;
        for (auto & i : inputs) {
            if (i.size() >= 2) {
                sum += t.evaluateExpression(i[0], i[1]);
            }
        }
        t.setScore(sum / inputs.size());
    }

    sort(trees.begin(), trees.end());

    for (auto & t : trees) {
        cout << "Exp ";
        t.printExpression();
        cout << " Score " << t.getScore() << endl;
    }

    return 0;
}
