#include "page.hpp"

/*store the page content from a page.txt file into the page content vector in page class
*/
Page Page::findPageContent() {
  std::ifstream ifs(pagePath.c_str());
  if (!ifs.is_open()) {
    error("Failed to open file page" + pageNumber);
  }
  else {
    std::string line;
    while (std::getline(ifs, line)) {
      this->pageContent.push_back(line);
    }
  }
  ifs.close();
  pageContent.push_back("\0");
  if (pageType.compare("N") == 0) {
    addChoice();
  }
  else {
    addWorL(pageType);
  }
  return *this;
}

//add a asking line in order to have the formal format
Page Page::addChoice() {
  pageContent.push_back("What would you like to do?\n");
  return *this;
}

//add the choices into page content vector
Page Page::addChoice(std::string choice, std::string nextPage) {
  this->choice.push_back(choice);
  this->nextPage.push_back(nextPage);
  nextPageSize++;
  std::stringstream ss;
  ss << nextPageSize;
  std::string res = ss.str();
  pageContent.push_back(" " + res + ". " + choice);
  return *this;
}

/*add the output condition.
 *if the page typr is win or lose, there should not be a choice, instead, the win or lose page should be displayed.
 */
Page Page::addWorL(std::string pageType) {
  if (pageType.compare("W") == 0) {
    pageContent.push_back("Congratulations! You have won. Hooray!");
  }
  else if (pageType.compare("L") == 0) {
    pageContent.push_back("Sorry, you have lost. Better luck next time!");
  }
  else {
    error("Illegal page type!");
  }
  return *this;
}

//find the corresponding key in the map
long Page::getMapKey(std::string str) {
  std::map<std::string, long>::iterator it;
  it = map.find(str);
  if (it != map.end()) {
    return map.find(str)->second;
  }

  //if the key can not be found in this map
  return 0;
}

void Page::putMap(std::string str, long num) {
  map.insert(std::pair<std::string, long>(str, num));
}

//compare the user input with the available choice, if the user input is not available, return 0, otherwise return 1;
int Page::findUnavaChoose(size_t input) {
  int res = 0;
  if (unAvaChoose.size() == 0)
    return res;
  std::ostringstream ss;
  ss << input;
  for (std::vector<std::string>::iterator it = unAvaChoose.begin();
       it != unAvaChoose.end();
       ++it) {
    if (ss.str().compare(*it) == 0) {
      res = 1;
      return res;
    }
  }
  return 0;
}
void error(const std::string & errormsg) {
  std::cerr << errormsg << std::endl;
  exit(EXIT_FAILURE);
}
