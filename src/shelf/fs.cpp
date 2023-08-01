#include "headers/fs.hpp"

#include <sys/stat.h>
#include <string>
// @requires c++17
#include <filesystem>

using std::string;
namespace filesystem = std::filesystem;

// ================================================
namespace fs {
  bool exists(const string& path) {
    struct stat buffer;
    int result = stat(path.c_str(), &buffer);
    return result == 0;
  }

  // you can get the base path from `main.argv[0]`, probably not portable
  string absPath(const string& path) {
    string absPath = filesystem::canonical(path);
    return absPath;
  }

  string dirname(const string& input) {
    filesystem::path path = input;
    return path.parent_path();
  }
}
