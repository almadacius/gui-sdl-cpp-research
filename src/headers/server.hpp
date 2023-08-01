// [builder] implementation: core/server.cpp
#ifndef SERVER_H
#define SERVER_H

#include <string>

using std::string;

// ================================================
struct ServerConfig {
  string execPath;
  string staticDir;
};

// ================================================
class Server {
  private:
  const ServerConfig& config;

  public:
  Server(const ServerConfig& config);

  // ================================================
  void ensureDir();

  string getRequestedFile(const string& path);

  // ================================================
  void run();
};

#endif
