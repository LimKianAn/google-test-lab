#include <gtest/gtest.h>

#include <iostream>
#include <memory>

class pure_abstract
{
public:
    virtual ~pure_abstract() = 0;
};

pure_abstract::~pure_abstract() {} // always needed

class derived : public pure_abstract
{
public:
    ~derived() override = default;
};

TEST(pure_abstrct, nothing)
{
    std::vector<std::unique_ptr<pure_abstract>> vector_of_base{};
    vector_of_base.push_back(std::make_unique<derived>());
}