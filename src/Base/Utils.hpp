#ifndef EXPRESSIONCALCULATORS_BASE_UTILS_HPP
#define EXPRESSIONCALCULATORS_BASE_UTILS_HPP

#include <type_traits>

namespace Utils {

template < typename    Type,  template <typename...> typename Template > struct IsInstantiationOf                              : std::false_type { };
template < typename... Types, template <typename...> typename Template > struct IsInstantiationOf<Template<Types...>,Template> : std:: true_type { };
template < typename    Type,  template <typename...> typename Template > constexpr auto IsInstantiationOfV = IsInstantiationOf<Type,Template>::value;

template < typename Type, auto... > struct DependentTrue  : std:: true_type { };
template < typename Type, auto... > struct DependentFalse : std::false_type { };
template < typename Type, auto... > constexpr auto DependentTrueV  = DependentTrue <Type>::value;
template < typename Type, auto... > constexpr auto DependentFalseV = DependentFalse<Type>::value;

} // namespace Uitls

#endif // EXPRESSIONCALCULATORS_BASE_UTILS_HPP

