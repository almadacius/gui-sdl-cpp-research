#ifndef TAUR_STR_H
#define TAUR_STR_H

#include <type_traits>
#include <string>
#include <queue>
#include <sstream>

using std::string;
using std::queue;
using std::ostringstream;

using strQueue = queue<string>;

/* @info
  - for templating, the implementation MUST be on the header file
*/
namespace str {
  // ================================================
  // low level
  // ================================================
  inline string toString(const string& input) {
    return input;
  }

  template<typename T>
  typename std::enable_if<std::is_arithmetic<T>::value, string>::type
  toString(const T& input) {
    return std::to_string(input);
  }

  // ================================================
  inline void fillQueue(strQueue* q) { /* @pass */ }

  template <typename T, typename... Args>
  void fillQueue(strQueue* q, T item, Args... otherArgs) {
    q->push(toString(item));
    fillQueue(q, otherArgs...);
  }

  // ================================================
  // concat
  // ================================================
  /*
    @sample
    - str::concat("these", " are ", "joined: ", 42);
  */
  inline string concat() { return ""; }

  template<typename T, typename... Args>
  string concat(const T& first, const Args&... args) {
    return toString(first) + concat(args...);
  }

  // ================================================
  // format
  // ================================================
  /*
    @sample
    - str::format(
      "My name is {}. I'm {} years old.", name, age, height
    );
  */
  template <typename... Args>
  string format(const string& format, Args... args) {
    ostringstream oss;

    size_t index = 0;
    size_t tokenIndex = format.find("{}");

    strQueue* argQ = new strQueue();
    fillQueue(argQ, args...);

    while (tokenIndex != string::npos) {
      oss << format.substr(index, tokenIndex - index);
      oss << argQ->front();
      argQ->pop();
      index = tokenIndex + 2;
      tokenIndex = format.find("{}", index);
    }

    oss << format.substr(index);

    return oss.str();
  }
}

#endif
