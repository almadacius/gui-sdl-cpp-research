#ifndef T_LIBFS
#define T_LIBFS

// - requires cpp17
#include <filesystem>
#include <string>

using std::string;
using std::filesystem::path;

// ================================================
namespace fs {
  struct State {
    path projRoot;
    path assetDir;
  };

  State state;

  // ================================================
  path getExecPath(char* argv[]) {
    namespace cfs = std::filesystem;

    path execPath = cfs::canonical(path(argv[0]));
    return execPath;
  }

  // ================================================
  void init(char* argv[]) {
    namespace cfs = std::filesystem;

    path execPath = fs::getExecPath(argv);
    path projRoot = execPath.parent_path().parent_path();
    state.projRoot = projRoot;

    path assetDir = projRoot / "assets";
    state.assetDir = assetDir;
  }

  // ================================================
  string getAssetPath(string name) {
    namespace cfs = std::filesystem;
    path out = state.assetDir / name;
    return out;
  }
}

#endif
