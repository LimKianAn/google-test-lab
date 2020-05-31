#include <gmock/gmock.h>

#include <memory>

class interface_thing
{
public:
    virtual ~interface_thing() = 0;
};

interface_thing::~interface_thing() = default;

class thing : public interface_thing
{
};

class interface_thing_to_test
{
public:
    virtual ~interface_thing_to_test() = default;

    virtual void take_non_copyable_parameter(std::unique_ptr<interface_thing> other_thing) = 0;
    virtual std::unique_ptr<interface_thing> return_non_copyable() = 0;
};

void proxy__take_non_copyable_parameter(interface_thing *other_thing)
{
}

interface_thing *proxy__return_non_copyable()
{
    return new thing();
}

class mock_interface_thing_to_test
{
public:
    //void take_non_copyable_parameter(std::unique_ptr<interface_thing> other_thing) {
    //    proxy__take_non_copyable_parameter(other_thing.get() );
    //}

    //virtual std::unique_ptr<interface_thing> return_non_copyable() {
    //    return std::unique_ptr<interface_thing>(proxy__return_non_copyable() );
    //}

    MOCK_METHOD1(take_non_copyable_parameter, void(std::unique_ptr<interface_thing>));
    MOCK_METHOD0(return_non_copyable, std::unique_ptr<interface_thing>());

    //MOCK_METHOD1(proxy__take_non_copyable_parameter, void(interface_thing*) );
    //MOCK_METHOD0(proxy__return_non_copyable, interface_thing*() );
};

TEST(mock_functions_with_uncopyable_in_the_signature, nothing)
{
}
