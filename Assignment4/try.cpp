#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class LinkedBinaryTree {
public:
    struct Node {
        string elem;
        Node* left;
        Node* right;
        Node(const string & e, Node* l = nullptr, Node* r = nullptr)
            : elem(e), left(l), right(r) {}
    };

    LinkedBinaryTree() : root(nullptr), score(0) {}

    LinkedBinaryTree(const LinkedBinaryTree & other) {
        root = clone(other.root);
        score = other.score;
    }

    LinkedBinaryTree & operator=(const LinkedBinaryTree & other) {
        if (this != &other) {
            clear(root);
            root = clone(other.root);
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

    Node* getRoot() const { return root; }
    void setRoot(Node* r) { root = r; }

private:
    Node* root;   
    double score; 

    void printExpression(Node* t) const {
        if (t != nullptr) {
            if (t->left == nullptr && t->right == nullptr) {
                cout << t->elem;
            } else {
                if (t->elem == "abs") {
                    cout << "abs(";
                    printExpression(t->left);
                    cout << ")";
                } else {
                    cout << "(";
                    printExpression(t->left);
                    cout << t->elem;
                    printExpression(t->right);
                    cout << ")";
                }
            }
        }
    }

    double evaluateExpression(Node* t, double a, double b) const {
        if (t != nullptr) {
            if (t->left == nullptr && t->right == nullptr) {
                if (t->elem == "a")
                    return a;
                if (t->elem == "b")
                    return b;
                return stod(t->elem);
            } else {
                if (t->elem == "abs") {
                    return fabs(evaluateExpression(t->left, a, b));
                }
                double leftVal = evaluateExpression(t->left, a, b);
                double rightVal = evaluateExpression(t->right, a, b);
                if (t->elem == "+")
                    return leftVal + rightVal;
                if (t->elem == "-")
                    return leftVal - rightVal;
                if (t->elem == "*")
                    return leftVal * rightVal;
                if (t->elem == "/")
                    return leftVal / rightVal; 
                if (t->elem == ">")
                    return (leftVal > rightVal) ? 1 : -1;
            }
        }
        return 0;
    }

    Node* clone(Node* t) {
        if (t == nullptr)
            return nullptr;
        return new Node(t->elem, clone(t->left), clone(t->right));
    }


    void clear(Node* t) {
        if (t != nullptr) {
            clear(t->left);
            clear(t->right);
            delete t;
        }
    }
};


bool isOperator(const string & token) {
    return (token == "+" || token == "-" || token == "*" ||
            token == "/" || token == "abs" || token == ">");
}


LinkedBinaryTree createExpressionTree(const string & postfix) {
    stack<LinkedBinaryTree::Node*> st;
    istringstream iss(postfix);
    string token;
    while (iss >> token) {
        if (!isOperator(token)) { 
            st.push(new LinkedBinaryTree::Node(token));
        } else { 
            LinkedBinaryTree::Node* node = new LinkedBinaryTree::Node(token);
            if (token == "abs") {  
                if (st.empty()) {
                    cerr << "Error: insufficient operands for operator " << token << endl;
                    continue;
                }
                node->left = st.top();
                st.pop();
            } else { 
                if (st.size() < 2) {
                    cerr << "Error: insufficient operands for operator " << token << endl;
                    continue;
                }
                node->right = st.top();
                st.pop();
                node->left = st.top();
                st.pop();
            }
            st.push(node);
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
