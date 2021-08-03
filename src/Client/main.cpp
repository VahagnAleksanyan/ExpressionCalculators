#include <iostream>
#include <string>

#include <ExpressionCalculators/Core/InfixCalculator.hpp>

namespace Core = ExpressionCalculators::Core;

int main()
{
  Core::InfixCalculator infixCalculator;

  while(true)
  {
    std::cout << "Enter expression: ";
    std::string expression;
    std::cin >> expression;
    try
    {
      auto result = infixCalculator.calculate(expression);
      std::cout << "Result: " << result << std::endl << std::endl;
    }
    catch (std::invalid_argument& exception)
    {
      std::cout << exception.what() << std::endl << std::endl;
    }
  }

  return 0;
}

