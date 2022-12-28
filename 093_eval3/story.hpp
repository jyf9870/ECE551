#ifndef _STORY_HPP_
#define _STORY_HPP_
#include "page.cpp"
class Story {
 private:
  std::string filePath;
  std::vector<std::string> lines;
  std::vector<Page> pages;

 public:
  Story(std::string filePath) {
    std::vector<Page> p;
    pages = p;
    this->filePath = filePath;
    std::vector<std::string> lines;
    this->lines = lines;
  }
  Story readFile();
  Story readLines();
  long strToLong(std::string str);
  Page findPage(std::string pageNumber);
  void print();
  void checkVaild();
  void startStory(size_t index);
  std::string jump(std::string currPage);
  void findCycleFree();
  std::vector<std::string> dfs(Page curr,
                               std::vector<std::string> path,
                               std::set<std::string> visited,
                               std::vector<std::string> currpath);
  size_t pgNumToIndex(std::string pagenum);
  std::string findChooseNum(std::string first, std::string second);
  std::string checkVaildNum(std::string str, size_t flag);
  void checkWandL();
};
#endif
