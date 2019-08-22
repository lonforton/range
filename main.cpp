#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>

#include <boost/lexical_cast.hpp>

#include "ip_filter_range.cpp"

int main()
{
  auto t1 = std::chrono::high_resolution_clock::now();  
  IpPool ip_pool = get_input();
  std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << " - input" << std::endl;  t1 = std::chrono::high_resolution_clock::now();   

    try
    {      
      ip_pool = std::move(ip_pool) | ra::sort | ra::reverse;
      std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << " - sort" << std::endl; t1 = std::chrono::high_resolution_clock::now(); 

      output(ip_pool);
      std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << " - output" << std::endl; t1 = std::chrono::high_resolution_clock::now(); 

      // filter by first byte and output   // ip = filter(1)
      IpPool ip_filtered = filter(ip_pool, 1);
      output(ip_filtered);
      std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << " - filter_1" << std::endl; t1 = std::chrono::high_resolution_clock::now(); 

      // filter by first and second bytes and output   // ip = filter(46, 70)
      ip_filtered = filter(ip_pool, 46, 70);
      output(ip_filtered);
      std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << " - filter_2" << std::endl; t1 = std::chrono::high_resolution_clock::now(); 

      // filter by any byte and output     // ip = filter_any(46)
      ip_filtered = filter_any(ip_pool, 46);
      output(ip_filtered);
      std::cerr << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << " - filter_3" << std::endl; t1 = std::chrono::high_resolution_clock::now(); 
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
    }

  return 0;
}
