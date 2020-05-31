#include <gtest/gtest.h>

#include <memory>
#include <vector>

std::unique_ptr<std::vector<int>> make_it()
{
    using namespace std;
    auto return_value = make_unique<vector<int>>();

    std::unique_ptr<std::vector<int>> the_thing = move(return_value);

    return the_thing;
}

TEST(return_unique_pointer, trial)
{
    auto the_thing = make_it();
}