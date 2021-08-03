#ifndef EXPRESSIONCALCULATORS_TEST_TESTER_HPP
#define EXPRESSIONCALCULATORS_TEST_TESTER_HPP

#include <filesystem>
#include <string_view>
#include <stdexcept>
#include <optional>
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>

#include <ExpressionCalculators/Base/Logging.hpp>
#include <ExpressionCalculators/Core/BaseCalculator.hpp>
#include <ExpressionCalculators/Core/InfixCalculator.hpp>

namespace Core = ExpressionCalculators::Core;
constexpr double EPSILON = 1.0e-10;

struct Sample
{
  friend std::ifstream& operator >> (std::ifstream& fin, Sample& sample);

public:
  Sample() = default;

  Sample(std::string&& expression, Core::ValueType answer)
    : m_expression(expression)
    , m_answer(answer)
  { }

  Sample(Sample&& other)
    : m_expression(std::move(other.m_expression))
    , m_answer(other.m_answer)
  { }

  bool isValid()   const { return !!m_expression && !!m_answer; }
  bool isTuned()   const { return isValid() && !!m_result; }
  bool isCorrect() const { return isTuned() && (std::abs(m_answer.value() - m_result.value()) < EPSILON); }

  void tune(Core::BaseCalculator const& calculator)
  {
    LOG("Tunning ", *m_expression);
    assert(isValid());
    try
    {
      m_result = calculator.calculate(m_expression.value());
    }
    catch(std::invalid_argument& except)
    {
      std::cout << except.what() << std::endl;
    }
  }

private:
  std::optional<std::string>     m_expression;
  std::optional<Core::ValueType> m_answer;
  std::optional<Core::ValueType> m_result;
};
using Samples = std::vector<Sample>;

std::ifstream& operator >> (std::ifstream& fin, Sample& sample)
{
  std::string expression;
  fin >> expression;
  Core::ValueType answer;
  fin >> answer;

  sample.m_expression = std::move(expression);
  sample.m_answer = answer;
  return fin;
}

struct Tester
{
public:
  Tester(std::vector<std::filesystem::directory_entry>&& files)
    : m_files(files)
  { }

  void run() const
  {
    for(auto&& file : m_files)
    {
      std::cout << "Tetsing file: " << file << std::endl;
      std::ifstream fileStream(file.path().string(), std::ios::in);
      if(!fileStream)
      {
        std::cout << file << ": couldn't open file!!" << std::endl;
        return;
      }
      else
        testFile(fileStream);
    }
  }

private:
  void testFile(std::ifstream& file) const
  {
    LOG("Starting to test file!");

    size_t passed = 0;
    size_t failed = 0;
    size_t count  = 0;
    file >> count;

    Samples samples;
    samples.reserve(count);

    LOG("Reading samples...");
    Sample sample;
    while(file >> sample)
      samples.push_back(std::move(sample));

    LOG("Tuning samples...");
    for(auto&& sample : samples)
      sample.tune(infixCalculator);

    LOG("Checking results...");
    for(auto&& sample : samples)
      sample.isCorrect() ? ++passed : ++failed;

    std::cout << "====== PASSED: " << passed << std::endl;
    std::cout << "====== FAILED: " << failed << std::endl;
  }

private:
  std::vector<std::filesystem::directory_entry> m_files;
  Core::InfixCalculator const infixCalculator;
};

#endif // EXPRESSIONCALCULATORS_TEST_TESTER_HPP

