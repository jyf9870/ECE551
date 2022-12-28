#include "story.cpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    error("Illegal input format!");
  }
  std::string filePath = argv[1];
  Story story(filePath);
  story.checkVaild();
  story.startStory(0);
  return EXIT_SUCCESS;
}
