#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void error() {
  exit(EXIT_FAILURE);
}
void iter(std::vector<std::string> v) {
  std::vector<std::string>::iterator it = v.begin();
  while (it != v.end()) {
    std::cout << *it << std::endl;
    it++;
  }
}
int main(int argc, char ** argv) {
  std::string s;
  std::vector<std::string> v;
  if (argc == 1) {
    while (!std::cin.eof()) {
      std::getline(std::cin, s);
      v.push_back(s);
    }
    std::sort(v.begin(), v.end());
    iter(v);
    v.clear();
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream f(argv[i]);
      if (f.fail()) {
        std::cerr << "Could not open" << argv[i] << std::endl;
        error();
      }
      while (!f.eof()) {
        std::getline(f, s);
        v.push_back(s);
      }
      std::sort(v.begin(), v.end());
      iter(v);
      v.clear();
    }
  }
  return EXIT_SUCCESS;
}
