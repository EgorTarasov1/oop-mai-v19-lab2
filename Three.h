#ifndef THREE_H
#define THREE_H

#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>

class Three {
public:
    Three();
    Three(const size_t &n, unsigned char t = 0);
    Three(const std::initializer_list<unsigned char> &t);
    Three(const std::string &t);
    Three(const Three& other);
    Three(Three&& other) noexcept;
    virtual ~Three() noexcept;

    Three operator+(const Three& other) const;
    Three operator-(const Three& other) const;
    Three& operator=(const Three& other);

    bool operator==(const Three& other) const;
    bool operator<(const Three& other) const;
    bool operator>(const Three& other) const;

    std::vector<unsigned char> getDigits() const;

private:
    std::vector<unsigned char> digits;

    void validate() const;
};

#endif 