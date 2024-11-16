#include "Three.h"
#include <stdexcept>
#include <algorithm>
#include <cstring> 

Three::Three() : len(1), digits(new unsigned char[1]{0}) {}

Three::Three(const size_t &n, unsigned char t) : len(n), digits(new unsigned char[n]) {
    if (t >= 3) {
        throw std::invalid_argument("Invalid digit for base 3");
    }
    std::fill(digits, digits + n, t);
}

Three::Three(const std::initializer_list<unsigned char> &t) : len(t.size()), digits(new unsigned char[t.size()]) {
    std::copy(t.begin(), t.end(), digits);
    validate();
}

Three::Three(const std::string &t) : len(t.size()), digits(new unsigned char[t.size()]) {
    for (size_t i = 0; i < t.size(); ++i) {
        char c = t[t.size() - 1 - i]; 
        if (c < '0' || c > '2') {
            throw std::invalid_argument("Invalid character for base 3");
        }
        digits[i] = c - '0';
    }
}

Three::Three(const Three& other) : len(other.len), digits(new unsigned char[other.len]) {
    std::memcpy(digits, other.digits, len);
}

Three::Three(Three&& other) noexcept : len(other.len), digits(other.digits) {
    other.len = 0;
    other.digits = nullptr;
}

Three::~Three() noexcept {
    delete[] digits;
}

Three Three::plus(const Three& other) const {
    size_t maxLength = std::max(len, other.len);
    Three result;
    delete[] result.digits;
    result.digits = new unsigned char[maxLength + 1]; 
    result.len = maxLength;

    unsigned char carry = 0;
    for (size_t i = 0; i < maxLength; ++i) {
        unsigned char digit1 = (i < len) ? digits[i] : 0;
        unsigned char digit2 = (i < other.len) ? other.digits[i] : 0;
        unsigned char sum = digit1 + digit2 + carry;
        result.digits[i] = sum % 3;
        carry = sum / 3;
    }

    if (carry != 0) {
        result.digits[maxLength] = carry;
        ++result.len;
    }

    result.strip();
    return result;
}

Three Three::minus(const Three& other) const {
    if (this->lessThan(other)) {
        throw std::invalid_argument("Result cannot be negative");
    }

    Three result;
    delete[] result.digits;
    result.digits = new unsigned char[len];
    result.len = len;

    unsigned char borrow = 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char digit1 = digits[i];
        unsigned char digit2 = (i < other.len) ? other.digits[i] : 0;
        int sub = digit1 - digit2 - borrow;
        if (sub < 0) {
            sub += 3;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits[i] = sub;
    }

    result.strip();
    return result;
}

Three& Three::operator=(const Three& other) {
    if (this != &other) {
        delete[] digits;
        len = other.len;
        digits = new unsigned char[len];
        std::memcpy(digits, other.digits, len);
    }
    return *this;
}

Three& Three::operator=(Three&& other) noexcept {
    if (this != &other) {
        delete[] digits;
        len = other.len;
        digits = other.digits;
        other.len = 0;
        other.digits = nullptr;
    }
    return *this;
}

bool Three::equals(const Three& other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Three::lessThan(const Three& other) const {
    if (len != other.len) {
        return len < other.len;
    }
    for (size_t i = len; i-- > 0; ) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    return false;
}

bool Three::greaterThan(const Three& other) const {
    return !this->lessThan(other) && !this->equals(other);
}

unsigned char* Three::getDigits() const {
    return digits;
}

size_t Three::getLength() const {
    return len;
}

void Three::validate() const {
    for (size_t i = 0; i < len; ++i) {
        if (digits[i] >= 3) {
            throw std::invalid_argument("Invalid digit for base 3");
        }
    }
}

void Three::strip() {
    while (len > 1 && digits[len - 1] == 0) {
        --len;
    }
}