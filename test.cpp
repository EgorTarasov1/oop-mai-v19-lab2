#include <gtest/gtest.h>
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

TEST(ThreeTest, DefaultConstructor) {
    Three t;
    EXPECT_EQ(to_string(t), "0");
}

TEST(ThreeTest, SizeConstructor) {
    Three t(3, 2);
    EXPECT_EQ(to_string(t), "222");
}

TEST(ThreeTest, InitializerListConstructor) {
    Three t({1, 2, 0});
    EXPECT_EQ(to_string(t), "021");
}

TEST(ThreeTest, StringConstructor) {
    Three t("201");
    EXPECT_EQ(to_string(t), "201");  
}

TEST(ThreeTest, Addition) {
    Three t1({1, 2, 0});  
    Three t2("201");      
    Three t3 = t1.plus(t2);  
    EXPECT_EQ(to_string(t3), "222");
}

TEST(ThreeTest, Subtraction) {
    Three t1("221");      
    Three t2("201");      
    Three t3 = t1.minus(t2);  
    EXPECT_EQ(to_string(t3), "20");
}

TEST(ThreeTest, Comparison) {
    Three t1({1, 2, 0});
    Three t2("201");
    EXPECT_FALSE(t1.equals(t2));  
    EXPECT_TRUE(t1.lessThan(t2));  
    EXPECT_FALSE(t1.greaterThan(t2)); 
}

TEST(ThreeTest, SubtractionNegativeResult) {
    Three t1({1, 0, 0});
    Three t2("201");
    EXPECT_THROW(t1.minus(t2), std::invalid_argument);  
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}