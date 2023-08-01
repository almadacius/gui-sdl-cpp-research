export module fs;

// ================================================
#include <sys/stat.h>

// this fails with declaration mismatches, as if using a different
// version of stdlibc++
#include <string>

/*
  this one fails because the stdlibc++ version does not
  support being imported as a module
  */
// import <string>;

using std::string;

// ================================================
export class Fs {
  public:
  static bool exists(string& path) {
    struct stat buffer;
    int result = stat(path.c_str(), &buffer);
    return result == 0;
  }
};
