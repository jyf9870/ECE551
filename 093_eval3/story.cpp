#include "story.hpp"

#include <iostream>
#include <set>

/*read the story content from the path
 *store the story into vector lines in class story
 */
Story Story::readFile() {
  std::string newpath = this->filePath;
  newpath.append("/");
  newpath.append("story.txt");

  std::ifstream ifs(newpath.c_str());
  if (!ifs.is_open()) {
    error("Failed to open file story.txt");
  }
  else {
    std::string line;
    while (std::getline(ifs, line)) {
      this->lines.push_back(line);
    }
  }
  ifs.close();
  return *this;
}

/*read story lines to page class 
 *store them into differnet fields
 */
Story Story::readLines() {
  size_t splitFirst, splitSecond;
  std::string pageNumber, pagePath, pageType, nextPage, choice;
  for (size_t i = 0; i < lines.size(); i++) {
    if (lines[i].find("@") != std::string::npos) {
      splitFirst = lines[i].find("@");
      if (lines[i].find(":", splitFirst + 1) != std::string::npos) {
        splitSecond = lines[i].find(":");
      }
      else {
        error("Illegal input lines in story.txt(@and:)!");
      }
      pageNumber = checkVaildNum(lines[i].substr(0, splitFirst), i);
      pageType = lines[i].substr(splitFirst + 1, splitSecond - splitFirst - 1);
      pagePath = lines[i].substr(splitSecond + 1);
      pagePath.insert(0, "/");
      pagePath.insert(0, filePath);
      Page p(pageNumber, pageType, pagePath);
      p = p.findPageContent();
      pages.push_back(p);
    }
    else if (lines[i].find(":") != std::string::npos) {
      splitFirst = lines[i].find(":");
      if (lines[i].find(":", splitFirst + 1) != std::string::npos) {
        splitSecond = lines[i].find(":", splitFirst + 1);
      }
      else {
        error("Illegal input lines in story.txt!(:and:)");
      }

      //this check is used in step4, to check if the choices have [condition]. If there is a condition in the choice, the substr should be different compared to the previous one
      if (lines[i].find("[") != std::string::npos &&
          lines[i].find("]") != std::string::npos) {
        size_t splitThird = lines[i].find("[");
        pageNumber = checkVaildNum(lines[i].substr(0, splitThird), i);
        choice = lines[i].substr(splitThird, splitFirst - splitThird);
        choice = choice + lines[i].substr(splitSecond + 1);
      }
      else {
        pageNumber = checkVaildNum(lines[i].substr(0, splitFirst), i);
        choice = lines[i].substr(splitSecond + 1);
      }
      nextPage =
          checkVaildNum(lines[i].substr(splitFirst + 1, splitSecond - splitFirst - 1), 0);
      Page page = findPage(pageNumber);
      page = page.addChoice(choice, nextPage);
      for (size_t n = 0; n < pages.size(); n++) {
        if (pages[n].getPageNum().compare(page.getPageNum()) == 0) {
          pages[n] = page;
        }
      }
    }

    //this check is used in step4, to add the condition in pages
    else if (lines[i].find("$") != std::string::npos) {
      splitFirst = lines[i].find("$");
      if (lines[i].find("=", splitFirst + 1) != std::string::npos) {
        splitSecond = lines[i].find("=", splitFirst + 1);
      }
      else {
        error("Illegal input lines in story.txt!(:and:)");
      }
      pageNumber = checkVaildNum(lines[i].substr(0, splitFirst), i);
      size_t index = pgNumToIndex(pageNumber);
      std::string str = lines[i].substr(splitFirst + 1, splitSecond - splitFirst - 1);
      pages[index].putMap(str, strToLong(lines[i].substr(splitSecond + 1)));
    }
    else {
      continue;
    }
  }
  checkWandL();
  return *this;
}

//transfer a string to long int numebr
long Story::strToLong(std::string str) {
  char * numEnd;
  long num = std::strtol(str.data(), &numEnd, 10);
  if (*numEnd != '\0')
    error("invaild string to long");
  return num;
}

//use a string page number to find the corresponding page, bacause the pagenumber is not alway as same as the page index
Page Story::findPage(std::string pageNumber) {
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getPageNum().compare(pageNumber) == 0) {
      return pages[i];
    }
  }
  error("choice page " + pageNumber + "doesn't exist");
  return pages[0];
}

/*this function is used in step1
 *print the story and the following choices
 */
void Story::print() {
  *this = readFile();
  *this = readLines();
  for (size_t i = 0; i < pages.size(); i++) {
    std::cout << "Page " << pages[i].getPageNum() << std::endl;
    std::cout << "==========" << std::endl;
    for (size_t j = 0; j < pages[i].getPageContent().size(); j++) {
      std::cout << pages[i].getPageContent()[j] << std::endl;
    }
  }
}

/*this function is used in step2
 *to check if all conditions are met for the story as a whole
*/
void Story::checkVaild() {
  *this = readFile();
  *this = readLines();

  // check if all of the next pages in the choice are vaild, which means find all of the next pages from the page number's vector
  std::vector<std::string> totalPageNum;
  for (size_t i = 0; i < pages.size(); i++) {
    totalPageNum.push_back(pages[i].getPageNum());
  }
  int find = 0;

  // Every page (except page 0) is referenced by at least one *other* page's choices.
  //each b is in totalpagenum
  //every page should be a at least one time
  for (size_t i = 0; i < pages.size(); i++) {
    for (size_t j = 0; j < pages[i].getNextPageSize(); j++) {
      find = 0;
      for (size_t z = 0; z < totalPageNum.size(); z++) {
        if (totalPageNum[z].compare(pages[i].getNextPage()[j]) == 0) {
          find = 1;
          break;
        }
      }
      if (find == 0) {
        error("The next page number " + pages[i].getNextPage()[j] +
              " doesn't in the total page number!");
      }
    }
  }

  // Every page (except page 0) is referenced by at least one *other* page's choices.
  std::set<std::string> reachable;
  for (size_t i = 0; i < pages.size(); i++) {
    for (size_t j = 0; j < pages[i].getNextPageSize(); j++) {
      reachable.insert(pages[i].getNextPage()[j]);
    }
  }
  reachable.insert(pages[0].getPageNum());
  for (size_t i = 0; i < totalPageNum.size(); i++) {
    find = 0;
    for (std::set<std::string>::iterator it = reachable.begin(); it != reachable.end();
         ++it) {
      if (*it == totalPageNum[i]) {
        find = 1;
        break;
      }
    }
    if (find == 0) {
      error("The page number " + totalPageNum[i] + " is not referenced by other page");
    }
  }

  //check At least one page must be a WIN page and at least one page must be a LOSE page.
  int win = 0;
  int lose = 0;
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getPageType().compare("W") == 0) {
      win = 1;
    }
    else if (pages[i].getPageType().compare("L") == 0) {
      lose = 1;
    }
  }
  if (win == 0)
    error("There is no win page!");
  if (lose == 0)
    error("There is no lose page!");
}

//start from page0, for each time, if there is a vaild input, call this funciton again and come to the next page
void Story::startStory(size_t index) {
  for (size_t j = 0; j < pages[index].getPageContent().size(); j++) {
    if (pages[index].getPageContent()[j].find("[") != std::string::npos) {
      size_t splitfir = pages[index].getPageContent()[j].find("[");
      size_t splitsec = pages[index].getPageContent()[j].find("=");
      size_t splitthi = pages[index].getPageContent()[j].find("]");
      std::string key =
          pages[index].getPageContent()[j].substr(splitfir + 1, splitsec - splitfir - 1);
      long num = strToLong(
          pages[index].getPageContent()[j].substr(splitsec + 1, splitthi - splitsec - 1));

      //to see if this condition is in the page map. Meanwhile, if the condition is not in the map, the default vaule for a key is 0.
      if ((pages[index].mapsize() != 0 && pages[index].getMapKey(key) == num) ||
          (pages[index].getMapKey(key) == 0 && num == 0)) {
        std::cout << pages[index].getPageContent()[j].substr(0, splitfir)
                  << pages[index].getPageContent()[j].substr(splitthi + 1) << std::endl;
      }
      else {
        size_t splitfor = pages[index].getPageContent()[j].find(". ");
        pages[index].putUnavaChoose(
            pages[index].getPageContent()[j].substr(1, splitfor - 1));
        std::cout << pages[index].getPageContent()[j].substr(0, splitfir)
                  << "<UNAVAILABLE>" << std::endl;
      }
    }
    else {
      std::cout << pages[index].getPageContent()[j] << std::endl;
    }
  }

  std::string nextPageNum = jump(pages[index].getPageNum());
  if (nextPageNum.compare("W") == 0 || nextPageNum.compare("L") == 0) {
    return;
  }
  else {
    for (size_t i = 0; i < pages.size(); i++) {
      if (pages[i].getPageNum().compare(nextPageNum) == 0) {
        if (pages[index].mapsize() != 0) {
          std::map<std::string, long> map = pages[index].getmap();
          for (std::map<std::string, long>::const_iterator it = map.begin();
               it != map.end();
               ++it) {
            pages[i].putMap(it->first, it->second);
          }
        }
        index = i;
        break;
      }
    }
  }
  startStory(index);
}

//input the currpage and return the next page number according to the use input. Meanwhile, check if the user input is vaild. If it is not a integer which is from 1 to next page size, it will alway in a loop until there is a vaild input.
std::string Story::jump(std::string currPage) {
  size_t input;
  size_t index;
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getPageNum().compare(currPage) == 0)
      index = i;
  }
  if (pages[index].getPageType().compare("W") == 0)
    return "W";
  if (pages[index].getPageType().compare("L") == 0)
    return "L";

  std::cin >> input;
  while (!std::cin.good() || input <= 0 || input > pages[index].getNextPageSize() ||
         pages[index].findUnavaChoose(input) == 1) {
    if (!std::cin.good()) {
      std::cin.clear();
      std::string badinput;
      std::cin >> badinput;
    }
    if (pages[index].findUnavaChoose(input) == 1) {
      std::cout << "That choice is not available at this time, please try again\n";
    }
    else {
      std::cout << "That is not a valid choice, please try again\n";
    }
    std::cin >> input;
  }

  return pages[index].getNextPage()[input - 1];
}

/* this function is used in step3 
 * the findCycleFree() function called the dfs() function and use a dfs algorithm with recursion to go through all of the nodes
*/
void Story::findCycleFree() {
  std::set<std::string> visited;
  visited.insert("");
  std::vector<std::string> path;
  std::vector<std::string> currpath;
  path = dfs(pages[0], path, visited, currpath);
  for (size_t j = 0; j < path.size(); j++) {
    std::cout << path[j] << std::endl;
  }
}

/*a set of visited is used to calculate the nodes in the garph.
 *a vector path is used to record the dfs path and push all of the cycle free win path into the vector. 
 *Once a node had been vis ited, it will be added to the visited set, the number of nextpagesize for each node can be considered as the weight for each node. Once we choose a child_node, the weight of the parent_node should be decreade 1, if the weight comes to 0, this node should be poped out from the visited set and the path vector.
*/
std::vector<std::string> Story::dfs(Page curr,
                                    std::vector<std::string> path,
                                    std::set<std::string> visited,
                                    std::vector<std::string> currpath) {
  std::set<std::string>::iterator it;
  if (curr.getPageType() == "L") {
    return path;
  }
  it = visited.find(curr.getPageNum());
  if (it == visited.end()) {
    visited.insert(curr.getPageNum());
    currpath.push_back(curr.getPageNum());
  }
  else {
    return path;
    //there is a cycle
  }
  if (curr.getPageType() == "W") {
    std::string res = "";
    for (size_t i = 0; i < currpath.size() - 1; i++) {
      res = res + currpath[i] + "(" + findChooseNum(currpath[i], currpath[i + 1]) + ")" +
            ",";
    }
    res = res + currpath[currpath.size() - 1] + "(" +
          findChooseNum(currpath[currpath.size() - 1], "") + ")";
    path.push_back(res);
    currpath.pop_back();
    return path;
  }

  for (size_t i = 0; i < curr.getNextPageSize(); i++) {
    path = dfs(pages[pgNumToIndex(curr.getNextPage()[i])], path, visited, currpath);
  }
  currpath.pop_back();
  visited.erase(curr.getPageNum());
  return path;
}

//transfer the page number into page index
size_t Story::pgNumToIndex(std::string pagenum) {
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getPageNum().compare(pagenum) == 0) {
      return i;
    }
  }
  error("Error when transfer pagenumber to pageindex!");
  return -1;
}
/*transfer the user input into the pagenumber
 *because the user only need to choose the choice whilch is start from 0, it should be transfered to the real pagenumber 
*/
std::string Story::findChooseNum(std::string first, std::string second) {
  if (second == "" && pages[pgNumToIndex(first)].getPageType() == "W") {
    return "win";
  }

  for (size_t i = 0; i < pages[pgNumToIndex(first)].getNextPageSize(); i++) {
    if (pages[pgNumToIndex(first)].getNextPage()[i].compare(second) == 0) {
      std::ostringstream ss;
      ss << i + 1;
      return ss.str();
    }
  }
  error("Can not find the next page!");
  return "";
}
//check all of the numbers in the structure is a vaild number, which means the ' ' can only appears in front of the numbers, no after
std::string Story::checkVaildNum(std::string str, size_t flag) {
  char * numEnd;
  size_t num = std::strtoull(str.data(), &numEnd, 10);
  if (*numEnd != '\0')
    error("invaild string to long");

  if (flag != 0 && flag != num) {
    std::cout << "pagesize" << flag << std::endl;
    std::cout << num << std::endl;
    error("the page number should be in order!");
  }

  std::ostringstream ss;
  ss << num;
  return ss.str();
}

void Story::checkWandL() {
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getPageType() == "W" || pages[i].getPageType() == "L") {
      if (pages[i].getNextPageSize() != 0) {
        error("win and lose page can not contains choices!");
      }
    }
  }
}
