#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <cassert>

#include "InfixCalculator.hpp"

namespace ExpressionCalculators { namespace Core {

ValueType InfixCalculator::calculate(std::string const& expression) const
{
  LOG("In InfixCalculator::calculate...");
  LOG("Expression is: ", expression);
  if (!checkCharacters(expression)) { LOG("Throwing exception, expression contains invalid characters!"); throw std::invalid_argument("Expression contains invalid characters!"); }
  if (!startsWithDigit(expression)) { LOG("Throwing exception, expression starts with sign!");            throw std::invalid_argument("Expression starts with sign!");            }
  if (!endsWithDigit  (expression)) { LOG("Throwing exception, expression ends with sign!");              throw std::invalid_argument("Expression ends with sign!");              }

  auto [numbers, signs] = split(expression);
  LOG("Expression is splitted!");
  LOG("Numbers are: ", numbers, ", signs are: ", signs);
  assert(numbers.size() == signs.size()+1);

  LOG("Calculating...");
  while(!signs.empty())
  {
    auto ii = firstOperationIndex(signs);
    LOG("First operation index: ", ii, ", operation: ", signs[ii]);
    switch(signs[ii])
    {
      case '+': LOG(numbers[ii], " += ", numbers[ii+1]); numbers[ii] += numbers[ii+1]; break;
      case '-': LOG(numbers[ii], " -= ", numbers[ii+1]); numbers[ii] -= numbers[ii+1]; break;
      case '*': LOG(numbers[ii], " *= ", numbers[ii+1]); numbers[ii] *= numbers[ii+1]; break;
      case '/': LOG(numbers[ii], " /= ", numbers[ii+1]); numbers[ii] /= numbers[ii+1]; break;
      default: assert(false);
    }
    LOG("Erasing numbers[", ii+1, "]: ", numbers[ii+1]);
    numbers.erase(numbers.begin()+ii+1);
    LOG("Erasing signs[", ii, "]: ", signs[ii]);
    signs.erase(signs.begin()+ii);
    LOG("Numbers are: ", numbers, ", signs are: ", signs);
  }
  assert(numbers.size() == 1);
  LOG("Calculation is finished, returning: ", numbers[0]);
  return numbers[0];
}

std::tuple<std::vector<double>, std::vector<char>> InfixCalculator::split(std::string const& expression) const
{
  LOG("Splitting expression...");
  size_t signsCount = std::count_if(expression.begin(), expression.end(), [](char const& ch) { return m_signs.find_first_of(ch) != std::string::npos; });
  LOG("Counted signs: ", signsCount);
  std::vector<size_t> signsIndexes;
  signsIndexes.reserve(signsCount);
  size_t ii = 0;
  while(ii != std::string::npos)
  {
    ii = expression.find_first_of(m_signs, ++ii);
    LOG("Pushing back in signs indexes: ", ii);
    signsIndexes.push_back(ii);
  }
  LOG("Signs indexes are: ", signsIndexes);
  assert(signsIndexes.size() == signsCount+1);
  std::vector<ValueType> numbers; numbers.reserve(signsCount+1);
  std::vector<char>      signs;   signs  .reserve(signsCount);
  LOG("Pushing back in numbers: ", toValueType(expression.substr(0, signsIndexes[0])));
  numbers.push_back(toValueType(expression.substr(0, signsIndexes[0])));
  for(auto it1 = signsIndexes.begin(), it2 = it1+1; it1 != signsIndexes.end() && it2 != signsIndexes.end(); ++it1, ++it2)
  {
    auto sign = expression[*it1];
    LOG("Pushing back in signs: ", sign);
    signs.push_back(sign);
    try
    {
      auto number = toValueType(expression.substr(*it1+1, *it2-*it1-1));
      LOG("Pushing back in numbers: ", number);
      numbers.push_back(number);
    }
    catch (std::invalid_argument& exception) { throw std::invalid_argument("Expression contains adjacent signs!"); }
    catch (std::out_of_range&     exception) { throw std::invalid_argument("Expression contains very large numbers!"); }
  }
  return {numbers, signs};
}

size_t InfixCalculator::firstOperationIndex(std::vector<char> const& signs) const
{
  LOG("Finding first operation index...");
  auto mulDivIt = std::find_if(signs.begin(), signs.end(), [](char const& ch) { LOG("Checking ", ch); return m_mulDiv.find_first_of(ch) != std::string::npos; });
  if (mulDivIt != signs.end()) { LOG("Found mul or div!"); return mulDivIt - signs.begin(); }
  assert(m_addSub.find_first_of(signs[0]) != std::string::npos);
  return 0;
}

} } // namespace ExpressionCalculators::Core

