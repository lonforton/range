#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>

#include <boost/lexical_cast.hpp>

#include "ip_filter_range.cpp"

int main(int argc, char *argv[])
{
  int repeat_number = 1;
  if (argc > 1)
    repeat_number = boost::lexical_cast<int>(argv[1]);

  uint64_t full_run_time = 0;
  IpPool ip_pool = get_input();

  for (auto i = 0; i < repeat_number; ++i) {
    auto t1 = std::chrono::high_resolution_clock::now();

    try
    {      
      ip_pool = std::move(ip_pool) | ra::sort | ra::reverse;

      output(ip_pool);

      // TODO filter by first byte and output   // ip = filter(1)
      IpPool ip_filtered = filter(ip_pool, 1);
      output(ip_filtered);

      // TODO filter by first and second bytes and output   // ip = filter(46, 70)
      ip_filtered = filter(ip_pool, 46, 70);
      output(ip_filtered);

      // TODO filter by any byte and output     // ip = filter_any(46)
      ip_filtered = filter_any(ip_pool, 46);
      output(ip_filtered);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }

    full_run_time += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count();
  }

  std::cout << "Repeated " << repeat_number << " times, average execution time " << full_run_time / repeat_number << std::endl;

  return 0;
}
