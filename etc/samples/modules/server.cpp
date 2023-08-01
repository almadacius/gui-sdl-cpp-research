#include "crow.h"

import fs1;

// ================================================
using std::string;
using std::cout;
using std::endl;

using crow::SimpleApp;
using crow::request;
using crow::response;

// ================================================
class Logger {
  public:
  Logger() {}

  void log(string msg) {
    cout << msg << endl;
  }
};

// ================================================
class Server {
  private:
  Logger* logger;

  public:
  Server() {
    logger = new Logger();
  }

  void run() {
    SimpleApp app;

    app
      .port(3000)
      .multithreaded();

    CROW_ROUTE(app, "/<path>")(
      [this](request& req, response& res, string path){
        // string path = req.url_params.get("path");
        logger->log("received request:");
        logger->log(path);

        if(Fs::exists(path)) {
          res.end("file exists");
        }
        else {
          res.end("file does NOT exist");
        }
      }
    );

    logger->log("start server");
    app.run();
  }
};

// ================================================
int main() {
  Server* serverPtr = new Server();
  Server server = *serverPtr;
  server.run();

  return 0;
}
