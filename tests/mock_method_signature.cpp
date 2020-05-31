#include <gmock/gmock.h>

class Interface
{
public:
    virtual ~Interface() = default;
    virtual int &get_value() const = 0;
};

class MockInterface final : public Interface
{
public:
    // MOCK_METHOD(int&, get_value, (), (const, override)); // only works for msbuild and gcc
    MOCK_CONST_METHOD0(get_value, int &()); // works for msbuild, gcc and clang
};

int &use_interface(Interface *interface_to_use)
{
    auto &value = interface_to_use->get_value();
    std::cout << ++value << '\n';
    return value;
}

TEST(ReturnRef_ReturnRefOfCopy, trial)
{
    MockInterface local_mock_interface;

    int value = 0;
    EXPECT_CALL(local_mock_interface, get_value).WillOnce(testing::ReturnRef(value));

    ASSERT_EQ(use_interface(&local_mock_interface), value);
}
