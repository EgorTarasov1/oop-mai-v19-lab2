#include "Three.h"
#include <algorithm>

Three::Three() : digits(1, 0) {}

Three::Three(const size_t &n, unsigned char t) : digits(n, t) {
    for (unsigned char digit : digits) {
        if (digit >= 3) {
            throw std::invalid_argument("Invalid digit for base 3");
        }
    }
}

Three::Three(const std::initializer_list<unsigned char> &t) : digits(t) {
    validate();
}

Three::Three(const std::string &t) {
    for (char c : t) {
        if (c < '0' || c > '2') {
            throw std::invalid_argument("Invalid character for base 3");
        }
    }
    
    for (auto it = t.rbegin(); it != t.rend(); ++it) {
        digits.push_back(*it - '0');
    }
}

Three::Three(const Three& other) : digits(other.digits) {}

Three::Three(Three&& other) noexcept : digits(std::move(other.digits)) {}

Three::~Three() noexcept {}

Three Three::operator+(const Three& other) const {
    Three result;
    size_t maxLength = std::max(digits.size(), other.digits.size());
    result.digits.resize(maxLength, 0);

    unsigned char carry = 0;
    for (size_t i = 0; i < maxLength; ++i) {
        unsigned char digit1 = (i < digits.size()) ? digits[i] : 0;
        unsigned char digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char sum = digit1 + digit2 + carry;
        result.digits[i] = sum % 3;  
        carry = sum / 3;             
    }

    if (carry != 0) {
        result.digits.push_back(carry);
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    return result;
}

Three Three::operator-(const Three& other) const {
    if (*this < other) {
        throw std::invalid_argument("Result cannot be negative");
    }

    Three result;
    result.digits.resize(digits.size(), 0);

    unsigned char borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        unsigned char digit1 = digits[i];
        unsigned char digit2 = (i < other.digits.size()) ? other.digits[i] : 0;
        int sub = digit1 - digit2 - borrow;
        if (sub < 0) {
            sub += 3;  
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = sub;
    }

    while (result.digits.size() > 1 && result.digits.back() == 0) {
        result.digits.pop_back();
    }

    return result;
}

Three& Three::operator=(const Three& other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}

bool Three::operator==(const Three& other) const {
    return digits == other.digits;
}

bool Three::operator<(const Three& other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (size_t i = digits.size(); i-- > 0; ) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool Three::operator>(const Three& other) const {
    return !(*this < other) && !(*this == other);
}

std::vector<unsigned char> Three::getDigits() const {
    return digits;
}

void Three::validate() const {
    for (unsigned char digit : digits) {
        if (digit >= 3) {
            throw std::invalid_argument("Invalid digit for base 3");
        }
    }
}