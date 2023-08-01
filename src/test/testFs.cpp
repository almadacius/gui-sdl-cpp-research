#include "headers/logger.hpp"
#include "headers/fs.hpp"

#include <string>

using std::string;

// ================================================
void testAbsPath(const string& execPathRel) {
  string path = fs::absPath(execPathRel);
  SimpleLogger::logHeader(path);
}

void testDirname(const string& execPathRel) {
  string absPath = fs::absPath(execPathRel);
  string dirname = fs::dirname(absPath);
  SimpleLogger::logHeader(dirname);
}

// ================================================
int main(int argc, char* argv[]) {
  string execPathRel = argv[0];

  SimpleLogger::tryRun([execPathRel](){
    // testAbsPath(execPathRel);
    testDirname(execPathRel);
  });

  return 0;
}
