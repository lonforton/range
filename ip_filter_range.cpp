#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <range/v3/all.hpp>

namespace rs = ranges::v3;
namespace rv = ranges::v3::view;
namespace ra = ranges::v3::action;

using IpPool = std::vector<std::vector<int>>;
using IpAddressStr = std::vector<std::string>;
using IpAddress = std::vector<int>;

IpAddressStr split(const std::string &str, char splitter)
{   
  return str | rv::split(splitter);
}

template<typename... Args>
IpPool filter(const IpPool& ip_pool, Args... args)
{
  std::vector<int> filter_expression{args...};

  IpPool ip_pool_filtered;

  rs::for_each(ip_pool, [&](const auto& ip_address) {
    if (rs::equal(filter_expression.begin(), filter_expression.end(), ip_address.begin()))
    {
      ip_pool_filtered.push_back(ip_address);
    }
  });

  return ip_pool_filtered;
}

IpPool filter_any(const IpPool& ip_pool, int filter_expression)
{  
  IpPool ip_pool_filtered;
  for(auto ip_address : ip_pool    
     | rv::filter([filter_expression](const auto& ip_addr)   
                  { 
                     return rs::any_of(ip_addr, [filter_expression](int value) { return value == filter_expression; });
                  })      
     )         
  {  
    ip_pool_filtered.push_back(ip_address);
  }    

  return ip_pool_filtered;
}

void output(const IpPool &ip_pool)
{ 
  rs::for_each(ip_pool, [](const auto& ip_address){
    bool first = true;
    rs::for_each(ip_address, [&first](const auto& ip_address_part)
    {
      std::cout << (!first ? "." : "") << ip_address_part; 
      first = false; 
    });
    std::cout << std::endl;
  });
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
    rs::for_each(ip_address_str, [&](const auto& element) { ip_address.push_back(std::stoi(element));  });
    ip_pool.push_back(ip_address);
  }

  return ip_pool;
}
