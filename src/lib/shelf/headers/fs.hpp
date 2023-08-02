// [builder] implementation: shelf/fs.cpp
#ifndef FS_H
#define FS_H

#include <string>

using std::string;

namespace fs {
  bool exists(const string& path);

  string absPath(const string& path);

  string dirname(const string& path);
}

#endif
