#include <iostream>
#include <cstdlib>
#include <ctime>

class Birthday {
public:
    int day;
    Birthday() {
        randomize();
    }
    void randomize() { // randomize the day of the year(birthday of a person) it is easier than comapre with month and day
        day = rand() % 365 + 1; //
    }
    bool operator==(const Birthday &other) const {// change the operator == to compare the day of the year between two person
        return (day == other.day);
    }
};

class BirthdayParadox {
public:
    Birthday *birthdays; 
    const int num_people;

    BirthdayParadox(int n) : num_people(n) { //the constructor for a array of birthdays
        birthdays = new Birthday[num_people];
    }

    ~BirthdayParadox() {//destructor the array of birthdays
        delete[] birthdays;
    }

    int Compare() const { //compare the birthdays of the people in the group
        for (int i = 0; i < num_people; i++) {
            for (int j = i + 1; j < num_people; j++) {
                if (birthdays[i] == birthdays[j]) { 
                    return 1;  // if have two same birthdays
                }
            }
        }
        return 0; // if not have two same birthdays
    }
};

int main() {
    srand(time(0));
    int group_sizes[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};
    const int experiments = 100; //do the experiment 100 times

    for (int n : group_sizes) {
        int compare_result = 0;

        for (int i = 0; i < experiments; i++){
            BirthdayParadox comp(n);
            compare_result += comp.Compare();
        }

        double probability = static_cast<double>(compare_result) / experiments; //calculate the probability by changing the compare_result to double
        
        std::cout << n << "," << compare_result << "," << probability << std::endl;
    }

    return 0;
}


