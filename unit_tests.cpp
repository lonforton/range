#define BOOST_TEST_MODULE ranfe_test_module

#include <boost/test/unit_test.hpp>

#include "ip_filter_range.cpp"

namespace std
{
template <class T>
inline std::ostream &operator<<(std::ostream &os, std::vector<T> const &v)
{
  bool first = true;
  for (auto const &element : v)
  {
    os << (!first ? "." : "");
    os << element;
    first = false;
  }
  os << endl;
  return os;
}
} // namespace std

BOOST_AUTO_TEST_SUITE(range_input_suite)

BOOST_AUTO_TEST_CASE(range_input_test)
{
  std::stringstream ss;
  ss << std::string("4.5.66.7") << std::endl << std::string("6.74.8.9 5 6") << std::endl << std::string("5.7.254.0 1");

  IpPool ip_pool = get_input(ss);

  BOOST_CHECK(ip_pool.size() != 0);
  BOOST_CHECK(ip_pool.size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(range_sort_suite)

BOOST_AUTO_TEST_CASE(range_sort_test)
{
  std::stringstream ss;
  ss << std::string("1.11.69.33 1 1") << std::endl << std::string("1.101.1.1") << std::endl << std::string("1.70.144.70 0") << std::endl 
     << std::string("1.87.203.225") << std::endl << std::string("1.3.234.8 0 111") << std::endl;

  IpPool ip_pool = get_input(ss);  

  std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());

  std::vector<std::vector<int>> expected_sorted_ip_pool { {1, 101, 1, 1}, {1,87,203,225}, {1,70,144,70}, {1, 11, 69, 33}, {1,3,234,8} };

  BOOST_CHECK_EQUAL_COLLECTIONS(ip_pool.begin(), ip_pool.end(), expected_sorted_ip_pool.begin(), expected_sorted_ip_pool.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(range_test_suite)

BOOST_AUTO_TEST_CASE(range_filter_1_test)
{
  std::stringstream ss;
  ss << std::string("1.5.46.7") << std::endl << std::string("4.50.6.8 111") << std::endl << std::string("1.5.6.99") << std::endl << std::string("3.46.60.7") << std::endl << std::string("2.1.1.1") << std::endl;

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());

  IpPool filtered_ip_pool = filter(ip_pool, 1);

  IpPool expected_filtered_ip_pool { {1, 5, 46, 7}, {1, 5, 6, 99} };

  BOOST_CHECK_EQUAL_COLLECTIONS(filtered_ip_pool.begin(), filtered_ip_pool.end(), expected_filtered_ip_pool.begin(), expected_filtered_ip_pool.end());
}

BOOST_AUTO_TEST_CASE(range_filter_2_test)
{
  std::stringstream ss;
  ss << std::string("1.5.46.7") << std::endl << std::string("4.50.6.8 0 0") << std::endl << std::string("1.46.6.99") << std::endl << std::string("3.46.60.7") << std::endl;

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());

  IpPool filtered_ip_pool = filter(ip_pool, 1, 46);

  IpPool expected_filtered_ip_pool { {1,46, 6, 99} };

  BOOST_CHECK_EQUAL_COLLECTIONS(filtered_ip_pool.begin(), filtered_ip_pool.end(), expected_filtered_ip_pool.begin(), expected_filtered_ip_pool.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(range_any_suite)

BOOST_AUTO_TEST_CASE(range_filter_any_test)
{
  std::stringstream ss;
  ss << std::string("4.5.46.7") << std::endl << std::string("4.5.6.8 1 0") << std::endl << std::string("406.5.146.99 1 0") << std::endl << std::string("3.46.6.7") << std::endl;

  IpPool ip_pool = get_input(ss);

  std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<int>>());

  IpPool filtered_ip_pool = filter_any(ip_pool, 46);

  IpPool expected_filtered_ip_pool { {4, 5, 46, 7}, {3, 46, 6, 7}};

  BOOST_CHECK_EQUAL_COLLECTIONS(filtered_ip_pool.begin(), filtered_ip_pool.end(), expected_filtered_ip_pool.begin(), expected_filtered_ip_pool.end());
}

BOOST_AUTO_TEST_SUITE_END()

