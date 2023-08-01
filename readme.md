# Static server cpp

researching the shape of a cpp project for supporting other projects.

- based on `crow` library for webserver functionality
- based on js `@almadash/builder` for installation and build

---

## crow

- [github](https://github.com/CrowCpp/Crow.git)
  + links
    - [docs](https://crowcpp.org/master/)
    - [SimpleApp](https://crowcpp.org/master/guides/app/)

  + setup
    - [setup](https://crowcpp.org/master/getting_started/setup/linux/)
    - copy contents of `/include` into your project `include` dir
    - in this case, `c_modules`

  + depends on `Boost.asio.hpp`
    - header-only, can be included individually
    - [standalone](https://think-async.com/Asio/)
