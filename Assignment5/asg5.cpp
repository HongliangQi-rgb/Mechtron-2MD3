/*
Name: Hongliang Qi Student ID: 400493278
Design Explanation:
1. In this assignment, this program use a custom hash table. the hash function is based on a djb2 method. it iterates over each character in a string, multiplies 
the current hash value by a prime number, and then adds the ASCII value of the character. The final hash value is obtained by taking the modulo with the number 
of buckets.
2. Collision resolution is handled using separate chaining, meaning each bucket maintains a linked list. When inserting a new element, it is added at the head of 
the list. if there are two words with the same value. the new one with the same value will become the head of the linked list, and next is point to the original word
with the same word. as a result the collision is avoided. 
3.  For the sorting algorithm, quicksort is used to sort the words found in the hashtable, in lexicographical order. quick sort use a way of find a pivot first. in this 
code pivot is the middle one. then check the right item than pivot is bigger than the left item than pivot. then, use the quick sort to sort the items at the left and
right items recursively. the time complexity is O(nlogn). although it sometimes have the time complexity of O(n^2), but quick sort is still the quickest one. 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
using namespace std;

const int TABLE_SIZE = 1031;

class Node{
    public:
    string name;
    Node* next;
};

class Hashtable{
    public:
    Node ** table;
    Hashtable(){
        table = new Node*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++){
            table[i] = nullptr;
        }
    }

    ~Hashtable(){
        for (int i = 0; i < TABLE_SIZE; i++){
            Node* current = table[i];
            while (current != nullptr){
                Node* temp = current;
                current = current -> next;
                delete temp;
            }
        }
        delete [] table;
    }
    void insert(const string &s);
    bool find(const string &s)const;
};

unsigned int Hash(const string &s){
    unsigned long hash  = 5381;
    for (auto c : s){
        hash = hash * 33 + c;
    }
    return hash % TABLE_SIZE;
}

void Hashtable::insert(const string &s){
    unsigned int index = Hash(s);
    Node* current = table[index];
    while (current != nullptr){
        if (current -> name == s){
            return;
        }
        current = current -> next;
    }

    Node* newnode = new Node;
    newnode -> name = s;
    newnode -> next = table[index];
    table[index] = newnode;
}

bool Hashtable::find(const string &s)const{
    unsigned int index = Hash(s);
    Node* current = table[index];
    while(current != nullptr){
        if (current -> name == s){
            return true;
        }
        current = current -> next;
    }
    return false;
}

void quicksort(string arr[], int left, int right){
    if (left >= right){
        return;
    }
    int i = left;
    int j = right;
    string pivot = arr[ left + (right - left )/2];
    while (i <= j){
        while(arr[i] < pivot){
            i++;
        }
        while (arr[j] > pivot){
            j--;
        }
        if (i <= j){
            string temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }
    if (left < j){
        quicksort(arr, left, j );
    }
    if (i < right){
        quicksort (arr, i , right);
    }
}

int main(){
    Hashtable hashtable;
    ifstream file1("f-600-a.txt");
    if (!file1){
        cout << "cannot open the file" << endl;
        return 1;
    }
    string name;
    while(getline(file1,name)){
        if(!name.empty()){
            hashtable.insert(name);
        }
        
    }
    file1.close();
    ifstream file2("f-600-b.txt");
    if(!file2){
        cout<< "cannot open the file" << endl;
        return 1;
    }
    
    string sameword[1000];
    int counter = 0;
    while(getline(file2,name)){
        if(!name.empty() && hashtable.find(name)){
            sameword[counter++] = name;
        }
    }
    file2.close();

    

    if(counter > 0){
        clock_t start = clock();
        quicksort(sameword,0,counter-1);
        clock_t end = clock();
        double timecost = double(end-start)/CLOCKS_PER_SEC;
        cout << timecost << "s" <<  endl;
    }

    
    
    

    ofstream outfile("out.txt");
    if(!outfile){
        cout << "cannot build the file" << endl;
        return 1;
    }
    for (int i = 0; i < counter; i++){
        outfile << sameword[i] << "\n";
    }
    outfile.close();
    cout << "done" <<endl;
    return 0;
}


