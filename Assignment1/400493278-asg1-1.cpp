#include <iostream>

double BuyOnePotato(double price, int& num) { // make num be a reference, so that it can be changed
    num = num - 1;
    double money = price + price * 0.13;
    return money;
}
double BuyNumPotatoes(double price, int& num, int num_buy) { 
    num = num - num_buy;
    double money = price * num_buy + price * num_buy * 0.13;
    return money;
}

int main() {
    int potatoes_available = 20;
    float potato_price = 30.0;
    std::cout << "$" << BuyOnePotato(potato_price, potatoes_available)
    << std::endl;
    std::cout << potatoes_available << std::endl << std::endl;
    std::cout << "$" << BuyNumPotatoes(potato_price, potatoes_available, 3)
    << std::endl;
    std::cout << potatoes_available << std::endl;
    return EXIT_SUCCESS;
}

