#include <gtest/gtest.h>

#include <functional>
#include <iostream>
#include <string>

class name
{
public:
    std::string &get_name_incremented_with_A() { return _name += 'A'; }

private:
    std::string _name{};
};

TEST(test_mem_fn, nothing)
{
    name the_name;
    auto get_name = std::mem_fn(&name::get_name_incremented_with_A);
    EXPECT_EQ(get_name(the_name), "A");
}
