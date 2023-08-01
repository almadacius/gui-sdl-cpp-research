#include "headers/logger.hpp"
#include "headers/fs.hpp"
#include "headers/str.hpp"
#include "headers/server.hpp"

#include <stdexcept>
#include <iostream>

using std::runtime_error;

// ================================================
// separated for commenting and testing without the server header
void runServer(const string& execPath, string& staticDir) {
  ServerConfig config;
  config.execPath = execPath;
  config.staticDir = staticDir;

  Server* server = new Server(config);
  server->run();
}

void mainOperation(int argc, char* argv[]) {
  if(argc < 2) {
    throw runtime_error("base dir to serve not provided");
  }

  string execPath = fs::absPath(argv[0]);
  string execDir = fs::dirname(execPath);

  string staticDirRel = argv[1];
  string staticDir = str::concat(execDir, "/", staticDirRel);

  runServer(execPath, staticDir);
}

// ================================================
int main(int argc, char* argv[]) {
  SimpleLogger::tryRun([argc, argv](){
    mainOperation(argc, argv);
  });

  return 0;
}
