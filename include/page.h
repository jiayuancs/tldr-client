#ifndef TLDR_CLIENT_INCLUDE_PAGE_H_
#define TLDR_CLIENT_INCLUDE_PAGE_H_

#include <fstream>
#include <iostream>
#include <string>

#include "config.h"

using std::string;

namespace tldr {

// Render a page.
class Page {
 public:
  Page(const string &page_path, const Theme &theme) : page_path_(page_path), theme_(theme) {}
  bool Show() const;

 private:
  string page_path_;
  Theme theme_;
};

}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_PAGE_H_
