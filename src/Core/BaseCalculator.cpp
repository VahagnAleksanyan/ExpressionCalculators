#include <type_traits>
#include <cassert> // VA::TODO::Remove

#include <ExpressionCalculators/Base/Utils.hpp>
#include "BaseCalculator.hpp"

namespace ExpressionCalculators { namespace Core {

bool BaseCalculator::checkCharacters(std::string const& expression) const { return expression.find_first_not_of(m_allowedCharacters) == std::string::npos; }
bool BaseCalculator::startsWithDigit(std::string const& expression) const { return m_signs.   find_first_of    (expression.front())  == std::string::npos; }
bool BaseCalculator::  endsWithDigit(std::string const& expression) const { return m_signs.   find_first_of    (expression.back ())  == std::string::npos; }

ValueType BaseCalculator::toValueType(std::string const& numberString) const
{
  if constexpr (false);
  else if constexpr (std::is_same_v<ValueType, float      >) return std::stof (numberString);
  else if constexpr (std::is_same_v<ValueType, double     >) return std::stod (numberString);
  else if constexpr (std::is_same_v<ValueType, double long>) return std::stold(numberString);
  // VA::TODO::Can't do static_assert because the expression is not type-dependent
  //else static_assert(Utils::DependentFalseV<ValueType>);
  else assert(false);
  return 0.0;
}

} } // namespace ExpressionCalculators::Core

