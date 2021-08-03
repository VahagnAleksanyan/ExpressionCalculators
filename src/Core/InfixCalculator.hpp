#ifndef EXPRESSIONCALCULATORS_CORE_INFIXCALCULATOR_HPP
#define EXPRESSIONCALCULATORS_CORE_INFIXCALCULATOR_HPP

#include <vector>
#include <tuple>

#include "BaseCalculator.hpp"

namespace ExpressionCalculators { namespace Core {

struct InfixCalculator : BaseCalculator
{
public:
  virtual ValueType calculate (std::string const& expression) const override;

private:
  size_t firstOperationIndex (std::vector<char> const& signs) const;
  std::tuple<std::vector<ValueType>, std::vector<char>> split (std::string const& expression) const;
};

} } // namespace ExpressionCalculators::Core

#endif // EXPRESSIONCALCULATORS_CORE_INFIXCALCULATOR_HPP

