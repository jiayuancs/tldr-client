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
  Page(const string &page_path, const Theme &theme)
      : page_path_(page_path), theme_(theme), last_line_type_(kNone) {}
  bool Show();

 private:
  // The type of the last line.
  enum {
    kNone,
    kTitle,
    kCmdDescription,
    kCodeDescription,
    kCode
  } last_line_type_;

  void Strim();
  void StrimLeft();
  void StrimRight();
  void RenderTitle();
  void RenderCmdDescription();
  void RenderCodeDescription();
  void RenderCode();

  string current_line_;
  string page_path_;
  Theme theme_;
  const string kBlankChars{" \t"};
};

}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_PAGE_H_
