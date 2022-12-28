#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <stdio.h>
#include <stdlib.h>

#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "set"
class Page {
 private:
  std::string pageNumber;
  std::vector<std::string> pageContent;
  std::string pagePath;
  std::vector<std::string> nextPage;
  std::vector<std::string> choice;
  size_t nextPageSize;
  std::string pageType;
  std::map<std::string, long> map;
  std::vector<std::string> unAvaChoose;

 public:
  Page(std::string pageNumber, std::string pageType, std::string pagePath) {
    this->pageNumber = pageNumber;
    this->pagePath = pagePath;
    std::vector<std::string> pageContent;
    this->pageContent = pageContent;
    std::vector<std::string> nextPage;
    this->nextPage = nextPage;
    std::vector<std::string> choice;
    this->choice = choice;
    this->nextPageSize = 0;
    this->pageType = pageType;
    std::map<std::string, long> map;
    this->map = map;
    std::vector<std::string> unAvaChoose;
    this->unAvaChoose = unAvaChoose;
  }
  Page findPageContent();
  Page addChoice();
  Page addChoice(std::string choice, std::string nextPage);
  Page addWorL(std::string pageType);
  std::string getPageNum() { return pageNumber; }
  std::vector<std::string> getPageContent() { return pageContent; }
  size_t getNextPageSize() { return nextPageSize; }
  std::vector<std::string> getNextPage() { return nextPage; }
  std::string getPageType() { return pageType; }
  void putMap(std::string str, long num);
  std::map<std::string, long> getmap() { return map; }
  long getMapKey(std::string str);
  size_t mapsize() { return map.size(); }
  void putUnavaChoose(std::string str) { unAvaChoose.push_back(str); }
  int findUnavaChoose(size_t input);
};

void error(const std::string & errormsg);
#endif
