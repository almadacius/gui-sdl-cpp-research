// [builder] implementation: shelf/logger.cpp
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <functional>
#include <stdexcept>

using std::string;
using std::function;
using std::exception;

class SimpleLogger {
  public:
  static void log(string msg);

  static void logLine();

  static void logBold();

  // ================================================
  static void logError(exception& err);

  static void logHeader(string message);

  // ================================================
  static void tryRun(function<void()> handler);
};

#endif
