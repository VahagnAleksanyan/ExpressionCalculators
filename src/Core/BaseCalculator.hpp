#ifndef EXPRESSIONCALCULATORS_CORE_BASECALCULATOR_HPP
#define EXPRESSIONCALCULATORS_CORE_BASECALCULATOR_HPP

#include <string_view>
#include <string>

#include <ExpressionCalculators/Base/Logging.hpp>

namespace ExpressionCalculators { namespace Core {

using ValueType = double;

struct BaseCalculator
{
public:
  virtual ValueType calculate (std::string const& expression) const = 0;

protected:
  bool  checkCharacters (std::string const& expression)   const;
  bool  startsWithDigit (std::string const& expression)   const;
  bool    endsWithDigit (std::string const& expression)   const;
  ValueType toValueType (std::string const& numberString) const;

protected:
  static constexpr std::string_view m_allowedCharacters = "0123456789.+-*/";
  static constexpr std::string_view m_signs  = "+-*/";
  static constexpr std::string_view m_addSub = "+-";
  static constexpr std::string_view m_mulDiv = "*/";
};

} } // namespace ExpressionCalculators::Core

#endif // EXPRESSIONCALCULATORS_CORE_BASECALCULATOR_HPP

