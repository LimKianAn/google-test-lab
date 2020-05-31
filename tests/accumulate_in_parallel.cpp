#pragma once

template <typename Iterator, typename Type>
struct accumulate_block
{
  void operator()(
      Iterator first_of_the_block,
      Iterator pass_the_last_of_the_block,
      Type &result)
  {
    result = std::accumulate(
        first_of_the_block,
        pass_the_last_of_the_block,
        result);
  }
};

template <typename Iterator, typename Type>
Type accumulate_in_parallel(Iterator first, Iterator past_the_last, Type initial_value)
{
  const unsigned long number_of_elements_in_total = std::distance(first, past_the_last);
  if (!number_of_elements_in_total)
    return initial_value;

  const unsigned long number_of_elements_per_thread = 25;
  const unsigned long number_of_threads_in_theory = 1 + (number_of_elements_in_total - 1) / number_of_elements_per_thread;

  const unsigned long number_of_threads_supported_by_hardware = std::thread::hardware_concurrency();

  const unsigned long number_of_threads = std::min(
      number_of_threads_supported_by_hardware != 0 ? number_of_threads_supported_by_hardware : 2,
      number_of_threads_in_theory);

  const unsigned long number_of_elements_per_block = number_of_elements_in_total / number_of_threads;

  std::vector<Type> results(number_of_threads);

  std::vector<std::thread> threads(number_of_threads - 1);

  Iterator start_of_the_block = first;
  for (unsigned long i = 0; i < (number_of_threads - 1); ++i)
  {
    Iterator past_the_last_of_the_block = start_of_the_block;
    std::advance(past_the_last_of_the_block, number_of_elements_per_block);

    thread[i] = std::thread(
        accumulate_block<Iterator, Type>(),
        start_of_the_block,
        past_the_last_of_the_block,
        std::ref(results[i]));

    start_of_the_block = past_the_last_of_the_block;
  }

  accumulate_block<Iterator, Type>()(
      start_of_the_block,
      past_the_last,
      results.back);

  for (auto &entry : threads)
    entry.join();

  return std::accumulate(
      std::begin(results),
      std::end(results),
      initial_value);
}
