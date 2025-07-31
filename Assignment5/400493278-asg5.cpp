/*
Name: Hongliang Qi Student ID:400493278
1. Hashfunction:
Uses a method similar to djb2. For each character in the string, it multiplies the current hash by 131 and adds the character’s ASCII value.
The resulting large integer is then compressed using a MAD method with constants (a = 31, b = 7) to obtain an index in the range [0, capacity-1].
A second hash (double hash) is computed as:
1 + (hashFunction(key) % (capacity - 1))
This ensures a non-zero step for collision resolution.
2. collision avoidance:
When inserting or searching, the initial index is given by the final hash function.
If the slot is occupied by a different key, the algorithm uses double hashing to probe the next index:
index = (hash1 + i * hash2) % capacity;
This method continues until an empty slot is found (for insert) or until the key is found 
3. sort method:
For the sorting algorithm, quicksort is used to sort the words found in the hashtable, in lexicographical order. quick sort use a way of find a pivot first. in this 
code pivot is the middle one. then check the right item than pivot is bigger than the left item than pivot. then, use the quick sort to sort the items at the left and
right items recursively. the time complexity is O(nlogn). although it sometimes have the time complexity of O(n^2), but quick sort is still the quickest one. 
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <time.h>
#include <vector>
using namespace std;

enum Entrystate{FREE, OCCUPIED}; // Enum to represent the state of each entry in the hash table

class HashEntry{
    public:
    string name;
    Entrystate state;
    HashEntry(): name(""), state(FREE){}
};

class HashTable{
    private:
    static const size_t DEFAULT_CAPACITY = 100000; // Default capacity of the hash table
    vector<HashEntry> table;  
    size_t capacity;
    size_t numElements;

    public:
    HashTable(size_t cap = DEFAULT_CAPACITY) // Constructor to initialize the hash table with a given capacity
        : capacity(cap), numElements(0)
    {
        table.resize(capacity);
    }

    unsigned long long hashFunction(const string &s) const { // Hash function to compute a hash value for a string
        unsigned long long seed = 131; 
        unsigned long long hashValue = 0;
        for (char c : s) {
            hashValue = hashValue * seed + static_cast<unsigned char>(c);
        }
        return hashValue;
    }
    
    size_t compressionFunction(unsigned long long y) const { // Compression function to map the hash value to a valid index in the table
        static const unsigned long long a = 31ULL;
        static const unsigned long long b = 7ULL;
        return static_cast<size_t>((a * y + b) % capacity);
    }
    
    size_t finalHashFunction(const string &s) const { // Final hash function to compute the index for a string
        unsigned long long y = hashFunction(s);
        return compressionFunction(y);
    }
    
    size_t doubleHashFunction(const string &s) const { // Double hash function to compute a step size for collision resolution
        return 1 + (hashFunction(s) % (capacity - 1));
    }
    void insert(const string &s);
    bool find(const string &s)const;
};


void HashTable::insert(const string &s) { // Insert a string into the hash table
    size_t hash1 = finalHashFunction(s);
    size_t hash2 = doubleHashFunction(s);
    for (size_t i = 0; i < capacity; i++) {
        size_t index = (hash1 + i * hash2) % capacity; // Compute the index using double hashing
        if (table[index].state == FREE) {
            table[index].name = s;
            table[index].state = OCCUPIED;
            numElements++;
            return;
        }
        if (table[index].state == OCCUPIED && table[index].name == s) {
            return; 
        }
    }
    cout << "Error: Hash table is full." << endl;
}

bool HashTable::find(const string &s) const {// Check if a string is in the hash table
    size_t hash1 = finalHashFunction(s);
    size_t hash2 = doubleHashFunction(s);
    for (size_t i = 0; i < capacity; i++) {
        size_t index = (hash1 + i * hash2) % capacity;
        if (table[index].state == FREE) {
            return false;
        }
        if (table[index].state == OCCUPIED && table[index].name == s) {
            return true;
        }
    }
    return false;
}

void quicksort(string arr[], int left, int right){ // Quicksort function to sort an array of strings
    if (left >= right){
        return;
    }
    int i = left;
    int j = right;
    string pivot = arr[ left + (right - left )/2];// Choose the pivot as the middle element
    while (i <= j){ // Partitioning the array
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
    if (left < j){ // Recursively sort the left part
        quicksort(arr, left, j );
    }
    if (i < right){ // Recursively sort the right part
        quicksort (arr, i , right);
    }
}

int main(){
    HashTable hashtable;
    ifstream file1("f-200-a.txt");
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
    ifstream file2("f-200-b.txt");
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
        clock_t start = clock(); // Calculate the time taken for sorting
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


