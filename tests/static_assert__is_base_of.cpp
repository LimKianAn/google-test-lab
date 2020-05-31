#include <gtest/gtest.h>

#include <type_traits>

class base
{
};

template <typename Type>
class trial
{
    static_assert(
        std::is_base_of<base, Type>::value,
        "Type has to be derived from base.");

    Type my_type;
};

TEST(static_assert__is_base_of, nothing)
{
    class derived : base
    {
    };
    trial<derived> my_trial;
}