#include <gtest/gtest.h>

#include <future>

TEST(async_destructor, nothing)
{
  using namespace std;
  auto sleep = [](int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
  };

  {
    auto future = async(launch::async, sleep, 9);
  }
}