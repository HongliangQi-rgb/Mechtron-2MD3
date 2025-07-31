/*
explaination:
in this program, I use the double hash to solve for collision (which is the open addressing method)
for the hash function, I use the BKDEHash algorith, which is trace each character in the string and * by speed and plus the ascii value of the character. This is based on Google and Github's idea.
The compression function is based on the MAD method that tought in the class, the value of a and b are from internet, the ULL means they are unsigned long long.
the final hash function is the combination of the hash value and the compression, that gives a index for the array.
since my solution for the collision is open searching address; I use the double hashing method to get the new address for collision; the step of the double hashing always greater than 1 and less than capacity - 1, so the new address must in the array (since the index is contained in array).
in the insert function, the program will read from the txt (in the main function) and write the values to the hash map, in the loop, the first time the i is 0 so the hash 2 is eliminated; when the index is empty then insert the value and set the state tobe occupied, when the index is occupied by other keys, then use the loop to iterate the index and check for the next index's state.
if the index is occupied and the key is the same with input, then means the input is already inserted so return. If not continue the loop. if the loop is finished but the key still not be inserted, so the array is full and exit an error.
the find function does the same think as the insert; calculate the index and use itertaion to check the state, until find the state is occupied and the key is equal to the input then return true, if not return false.
the quick sort function is divided into 3 parts, which are partition, quick sort and the public wrapper. The partition function will choose the last element in the string as the pivot, and traverse the vector to compare the order of the leading alphabet (if the leading alphabet are same for 2 stings then compare the second and so on, the order is in the normal order); the string that less than the pivot will be moved to the left and the string which bigger than the pivot will be moved to the right.
note in the interval [low,i] are the elements must be less than pivot, and in [i+1, high] are elements that greater than pivot; since the partition swap the pivot and the i+1 and return the i+1 as the index of the pivot, then call the quicksort function to recursively call the partition to sort it.
the low>= high is the base case for the recursion. call the partition to get a pivot and divide the vector; use recursion to sort the left and right part of the array, until reaches the base case low>=high, which means there is only one element.
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;
class HashTable
{
private:
    enum EntryState
    {
        FREE,
        OCCUPIED
    };
    struct HashEntry
    {
        string key;
        EntryState state;
        HashEntry() : key(""), state(FREE) {}
    };
    static const size_t DEFAULT_CAPACITY = 100000; // default length of the array
    vector<HashEntry> table;                       // hash array for storing
    size_t capacity;                               // number of slot in the hash table
    size_t numElements;                            // the number of inserted elements
    unsigned long long hashFunction(const string &key) const
    {
        unsigned long long seed = 131;
        unsigned long long hashValue = 0;
        for (char c : key)
        {
            hashValue = hashValue * seed + static_cast<unsigned char>(c);
        }
        return hashValue;
    }
    size_t compressionFunction(unsigned long long y) const // use MAD
    {
        static const unsigned long long a = 31ULL;
        static const unsigned long long b = 7ULL;
        return static_cast<size_t>((a * y + b) % capacity);
    }
    size_t finalHashFunction(const string &key) const
    {
        unsigned long long y = hashFunction(key);
        return compressionFunction(y);
    }
    size_t doubleHashFunction(const string &key) const
    {
        return 1 + (hashFunction(key) % (capacity - 1));
    }

public:
    HashTable(size_t cap = DEFAULT_CAPACITY)
        : capacity(cap), numElements(0)
    {
        table.resize(capacity);
    }
    void insert(const string &key)
    {
        size_t hash1 = finalHashFunction(key);
        size_t hash2 = doubleHashFunction(key);
        for (size_t i = 0; i < capacity; i++)
        {
            size_t index = (hash1 + i * hash2) % capacity;
            if (table[index].state == FREE)
            {
                table[index].key = key;
                table[index].state = OCCUPIED;
                numElements++;
                return;
            }
            if (table[index].state == OCCUPIED && table[index].key == key)
            {
                return;
            }
        }
        cerr << "Error: Hash table is full." << endl;
        exit(1);
    }
    bool find(const string &key) const
    {
        size_t hash1 = finalHashFunction(key);
        size_t hash2 = doubleHashFunction(key);
        for (size_t i = 0; i < capacity; i++)
        {
            size_t index = (hash1 + i * hash2) % capacity;
            if (table[index].state == FREE)
            {
                return false;
            }
            if (table[index].state == OCCUPIED && table[index].key == key)
            {
                return true;
            }
        }
        return false;
    }
};

int partition(vector<string> &arr, int low, int high)
{
    string pivot = arr[high];
    int i = low - 1;                 // the boundary of the region of mimimum region (less than pivot)
    for (int j = low; j < high; j++) // j is the index to traverse the array
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<string> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(vector<string> &arr)
{
    if (!arr.empty())
    {
        quickSort(arr, 0, (int)arr.size() - 1);
    }
}

int main()
{
    HashTable hashTable;
    ifstream fin1("f-200-a.txt");
    if (!fin1)
    {
        cerr << "Error opening f1.txt" << endl;
        return 1;
    }
    string word;
    while (getline(fin1, word))
    {
        if (!word.empty())
        {
            hashTable.insert(word);
        }
    }
    fin1.close();

    ifstream fin2("f-200-b.txt");
    if (!fin2)
    {
        cerr << "Error opening f2.txt" << endl;
        return 1;
    }
    vector<string> foundWords;
    while (getline(fin2, word))
    {
        if (!word.empty() && hashTable.find(word))
        {
            foundWords.push_back(word);
        }
    }
    fin2.close();

    clock_t start = clock();
    quickSort(foundWords);
    clock_t end = clock();
    double timecost = double(end-start)/CLOCKS_PER_SEC;
    cout << timecost << "s" <<  endl;

    ofstream fout("out1.txt");
    if (!fout)
    {
        cerr << "Error opening out.txt" << endl;
        return 1;
    }
    for (const auto &w : foundWords)
    {
        fout << w << "\n";
    }
    fout.close();
}
