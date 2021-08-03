#ifndef EXPRESSIONCALCULATORS_BASE_LOGGING_HPP
#define EXPRESSIONCALCULATORS_BASE_LOGGING_HPP

#include <type_traits>
#include <iostream>
#include <vector>
#include <string>

#include "Utils.hpp"

namespace Utils { namespace Logging {

template < typename Type > requires std::is_fundamental_v    <std::remove_cvref_t<Type>>             inline void print (Type&& object) { std::cout << object; }
template < typename Type > requires std::is_array_v          <std::remove_cvref_t<Type>>             inline void print (Type&& object) { std::cout << object; } // VA::TODO::Only for null-terminated char arrays
template < typename Type > requires std::is_same_v           <std::remove_cvref_t<Type>,std::string> inline void print (Type&& object) { std::cout << object; }
template < typename Type > requires Utils::IsInstantiationOfV<std::remove_cvref_t<Type>,std::vector> inline void print (Type&& object) { for (auto&& element : object) std::cout << element << ' '; }

inline void log() { std::cout << std::endl; }

template < typename First, typename... Rest >
inline void log(First&& first, Rest&&... rest)
{
  print(std::forward<First>(first));
  log(std::forward<Rest>(rest)...);
}

} } // namespace Utils::Logging

#ifdef EXPRESSIONCALCULATORS_LOGGING
#define LOG(...) Utils::Logging::log(__VA_ARGS__)
#else
#define LOG(...)
#endif

#endif // EXPRESSIONCALCULATORS_BASE_LOGGING_HPP

