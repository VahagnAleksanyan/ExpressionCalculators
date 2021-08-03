#include <filesystem>
#include <iostream>
#include <utility>
#include <vector>

#include "Tester.hpp"

int main()
{
  auto rec = std::filesystem::current_path() /= "rec";

  std::vector<std::filesystem::directory_entry> files;
  for (auto&& file : std::filesystem::directory_iterator(rec))
    files.push_back(file);

  std::cout << "Files are:" << std::endl;
  for (auto&& file : files) std::cout << file << std::endl;

  Tester tester(std::move(files));
  tester.run();

  return 0;
}

