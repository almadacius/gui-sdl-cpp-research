#include "headers/server.hpp"

#include "crow.h"

#include "headers/fs.hpp"
#include "headers/str.hpp"
#include "headers/logger.hpp"

#include <string>
#include <stdexcept>

// ================================================
using std::runtime_error;
using std::exception;

using std::string;

using crow::SimpleApp;
using crow::request;
using crow::response;

// ================================================
Server::Server(const ServerConfig& config) : config(config) {
  string message = str::format("static dir: {}", config.staticDir);
  SimpleLogger::logHeader(message);
}

// ================================================
void Server::ensureDir() {
  string staticDir = config.staticDir;

  if(!fs::exists(staticDir)) {
    throw runtime_error("static dir does NOT exist");
  }
}

string Server::getRequestedFile(const string& path) {
  string finalPath = str::concat(config.staticDir, "/", path);

  SimpleLogger::logLine();
  SimpleLogger::log(str::format("requested-> {}", path));
  SimpleLogger::log(str::format("resolved->  {}", finalPath));
  SimpleLogger::logLine();

  if(fs::exists(finalPath)) {
    return finalPath;
  }
  else {
    throw runtime_error(str::format("file not found: '{}'", path));
  }
}

// ================================================
void Server::run() {
  this->ensureDir();

  SimpleApp app;

  app
    .port(3000)
    .multithreaded();

  CROW_ROUTE(app, "/")([](response& res){
    res.redirect("/index.html");
    res.end();
  });

  CROW_ROUTE(app, "/<path>")(
    [this](request& req, response& res, string path){
      // string path = req.url_params.get("path");

      try {
        string file = getRequestedFile(path);
        // review input paths for `..` later
        res.set_static_file_info_unsafe(file);
        res.end();
      }
      catch(exception& err) {
        SimpleLogger::logError(err);
        res.end("file does NOT exist");
      }
    }
  );

  SimpleLogger::log("start server");
  app.run();
}
