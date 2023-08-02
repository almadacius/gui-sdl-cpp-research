#include "headers/logger.hpp"

#include <string>
#include <iostream>
#include <functional>
#include <stdexcept>

using std::string;
using std::cout;
using std::endl;
using std::exception;

// ================================================
void SimpleLogger::log(string msg) {
  cout << msg << endl;
}

void SimpleLogger::logLine() {
  SimpleLogger::log("------------------------------------------------");
}

void SimpleLogger::logBold() {
  SimpleLogger::log("================================================");
}

// ================================================
void SimpleLogger::logError(exception& err) {
  SimpleLogger::logLine();
  SimpleLogger::log("ERROR");
  SimpleLogger::logLine();
  SimpleLogger::log(err.what());
  SimpleLogger::logLine();
}

void SimpleLogger::logHeader(string message) {
  SimpleLogger::logLine();
  SimpleLogger::log(message);
  SimpleLogger::logLine();
}

// ================================================
void SimpleLogger::tryRun(function<void()> handler) {
  try {
    handler();
  }
  catch(exception& err) {
    SimpleLogger::logError(err);
  }
}
