#include "headers/logger.hpp"
#include "headers/str.hpp"

// ================================================
void testConcat() {
  string message = str::concat("aa", "bb", " brebre ", "fdefre ", 42);
  SimpleLogger::logHeader(message);
}

void testFormat() {
  string message = str::format(
    "token1: '{}', token2: '{}'", "some token", 589
  );
  SimpleLogger::logHeader(message);
}

int main(int argc, char* argv[]) {
  SimpleLogger::tryRun([](){
    // testConcat();
    testFormat();
  });

  return 0;
}
