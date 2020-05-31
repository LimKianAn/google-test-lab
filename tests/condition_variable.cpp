#include <gtest/gtest.h>

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>

namespace shared_between_2_threads
{
    std::mutex the_mutex;
    std::condition_variable the_condition_variable;

    bool on_or_off;
    constexpr bool ON = true;
    constexpr bool OFF = false;
} // namespace shared_between_2_threads

void turn_it_on__notify__wait_for_off()
{
    using namespace shared_between_2_threads;
    using namespace std;
    while (true)
    {
        {
            lock_guard<mutex> the_scoped_lock(the_mutex);

            cout << "Turn-it-on-thread: I have the mutex!" << endl;

            // lines of code

            on_or_off = ON;
            cout << "Turn-it-on-thread: It's on!" << endl;
        }

        the_condition_variable.notify_one();

        unique_lock<mutex> the_unique_lock(the_mutex);

        cout << "Turn-it-on-thread: I have the mutex!" << endl;

        the_condition_variable.wait(
            the_unique_lock,
            [] { return on_or_off == OFF; });
    }
}

void wait_for_on__turn_it_off__notify()
{
    using namespace shared_between_2_threads;
    using namespace std;

    while (true)
    {

        unique_lock<mutex> the_unique_lock(the_mutex);

        cout << "Turn-it-off-thread: I have the mutex!" << endl;

        the_condition_variable.wait(
            the_unique_lock,
            [] { return on_or_off == ON; });

        cout << "Turn-it-off-thread: I have the mutex!" << endl;

        on_or_off = OFF;

        cout << "Turn-it-off-thread: It's off!" << endl;

        the_unique_lock.unlock();

        the_condition_variable.notify_one();
    }
}

TEST(condition_varaible, on_and_off_scenario)
{
    // std::thread who_turns_it_on(turn_it_on__notify__wait_for_off);
    // std::thread who_turns_it_off(wait_for_on__turn_it_off__notify);

    // who_turns_it_on.join();
    // who_turns_it_off.join();
}