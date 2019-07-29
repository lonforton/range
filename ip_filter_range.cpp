#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <range/v3/all.hpp>

using IpPool = std::vector<std::vector<int>>;
using IpAddressStr = std::vector<std::string>;
using IpAddress = std::vector<int>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
IpAddressStr split(const std::string &str, char splitter)
{
  IpAddressStr ip_address;

  std::string::size_type start = 0;
  std::string::size_type stop = str.find_first_of(splitter);
  while (stop != std::string::npos)
  {
    ip_address.push_back(str.substr(start, stop - start));

    start = stop + 1;
    stop = str.find_first_of(splitter, start);
  }

  ip_address.push_back(str.substr(start));

  return ip_address;
}

template<typename... Args>
IpPool filter(const IpPool& ip_pool, Args... args)
{
  std::vector<int> filter_expression{args...};

  IpPool ip_pool_filtered;

  for (auto const &ip_address : ip_pool)
  {
    if (std::equal(filter_expression.begin(), filter_expression.end(), ip_address.begin()))
    {
      ip_pool_filtered.push_back(ip_address);
    }
  }

  return ip_pool_filtered;
}

IpPool filter_any(const IpPool& ip_pool, int filter_expression)
{
  IpPool ip_pool_filtered;
  for (auto const &ip_address : ip_pool)
  {
    if (std::find_if(ip_address.begin(), ip_address.end(), 
    [filter_expression](int value) { return value == filter_expression; }) != ip_address.end())
    {
      ip_pool_filtered.push_back(ip_address);
    }
  }

  return ip_pool_filtered;
}

void output(const IpPool &ip_pool)
{
  for (auto const &ip_address : ip_pool)
  {
    bool first = true;
    for (auto const &ip_address_part : ip_address)
    {
      std::cout << (!first ? "." : "") << ip_address_part;
      first = false;
    }
    std::cout << std::endl;
  }
}

IpPool get_input(std::istream &is);

IpPool get_input()
{
  return get_input(std::cin);
}

IpPool get_input(std::istream &is)
{
  IpPool ip_pool;
  for (std::string line; std::getline(is, line) && line.size() > 0;)
  {
    IpAddressStr ip_address_str = split(split(line, '\t').at(0), '.');
    IpAddress ip_address;
    for(auto const& element : ip_address_str)
    {
      ip_address.push_back(std::stoi(element));
    }
    ip_pool.push_back(ip_address);
  }

  return ip_pool;
}
