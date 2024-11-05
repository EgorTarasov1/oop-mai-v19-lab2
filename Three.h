#ifndef THREE_H
#define THREE_H

#include <string>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

class Three {
public:
    Three();
    Three(const size_t &n, unsigned char t = 0);
    Three(const std::initializer_list<unsigned char> &t);
    Three(const std::string &t);
    Three(const Three& other);
    Three(Three&& other) noexcept;
    ~Three() noexcept;

    Three operator+(const Three& other) const;
    Three operator-(const Three& other) const;
    Three& operator=(const Three& other);
    Three& operator=(Three&& other) noexcept;

    bool operator==(const Three& other) const;
    bool operator<(const Three& other) const;
    bool operator>(const Three& other) const;

    unsigned char* getDigits() const;
    size_t getLength() const;

private:
    size_t len;
    unsigned char* digits;

    void validate() const;
    void strip();
};

#endif