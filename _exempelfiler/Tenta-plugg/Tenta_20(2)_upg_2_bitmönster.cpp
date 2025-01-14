#include <iostream>
using namespace std;

void setBit(unsigned long &week, int unit){
    week |= (1UL << unit);
}

void clearBit(unsigned long &week, int unit){
    week &= ~(1UL << unit);
}

bool checkBit(unsigned long &week, int unit){
    return (week & (1UL << unit));
}

int main() {
    unsigned long week01 = 0;  // Initialize to 0

    setBit(week01, 26);
    setBit(week01, 20);
    std::cout << checkBit(week01, 26) << std::endl;  // Should print 1 (true)

    clearBit(week01, 26);
    std::cout << checkBit(week01, 26) << std::endl;  // Should print 0 (false)

    return 0;
}