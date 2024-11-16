#include <iostream>
#include "Three.h"

std::string to_string(const Three& t) {
    std::string result;
    size_t length = t.getLength();
    const unsigned char* digits = t.getDigits();
    for (size_t i = 0; i < length; ++i) {
        result = std::to_string(digits[i]) + result;
    }
    return result;
}

int main() {
    try {
        Three t1({1, 2, 2});
        Three t2("201");
        Three t3(5, 1); 

        std::cout << "t1: " << to_string(t1) << std::endl;
        std::cout << "t2: " << to_string(t2) << std::endl;
        std::cout << "t3: " << to_string(t3) << std::endl;

        Three t4 = t1.plus(t2);
        std::cout << "t1 + t2: " << to_string(t4) << std::endl;

        Three t5 = t1.minus(t2);
        std::cout << "t1 - t2: " << to_string(t5) << std::endl;

        std::cout << "t1 == t2: " << (t1.equals(t2) ? "true" : "false") << std::endl;
        std::cout << "t1 < t2: " << (t1.lessThan(t2) ? "true" : "false") << std::endl;
        std::cout << "t1 > t2: " << (t1.greaterThan(t2) ? "true" : "false") << std::endl;

        Three t6;
        t6 = t1; 
        std::cout << "t6 (assigned from t1): " << to_string(t6) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}