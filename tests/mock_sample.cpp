#include <gmock/gmock.h>



class Dependency {
public:
    virtual int plusOne(int x) = 0;
    virtual ~Dependency() = default;
};

class Dependency_Mock : public Dependency {
public:
    MOCK_METHOD1(plusOne, int(int));
};

class SomeClass {
public:
    void inject(std::unique_ptr<Dependency> dep) { 
        dependency = std::move(dep); 
    }

    int execute(int x) { 
        return dependency->plusOne(x); 
    }

private:
    std::unique_ptr<Dependency> dependency;
};

TEST(SomeClassTest, executeTestWithMock)
{
    auto dep = std::make_unique<Dependency_Mock>();
    EXPECT_CALL(
        *dep, 
        plusOne(testing::_)
    ).WillOnce(
        testing::Return(5)
    );

    SomeClass some;
    some.inject(std::move(dep));

    EXPECT_EQ(some.execute(5), 5); // execute
}