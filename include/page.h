#ifndef TLDR_CLIENT_INCLUDE_PAGE_H_
#define TLDR_CLIENT_INCLUDE_PAGE_H_

#include <fstream>
#include <iostream>
#include <string>

#include "config.h"

using std::string;

namespace tldr {

class Page {
 public:
  Page(const string command) : command_(command) {}

  bool Show() const;

 private:
  string command_;

  string GetPagePath() const;
};

}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_PAGE_H_
