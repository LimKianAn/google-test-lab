#include <gtest/gtest.h>

#include <iostream>

class simple
{
public:
    int do_it()
    {
        auto really_do_it = [this] {
            return number;
        };

        return really_do_it();
    }

private:
    int number{};
};

TEST(test_simple, test_do_it)
{
    ASSERT_EQ(simple{}.do_it(), int{});
}