#ifndef TLDR_CLIENT_INCLUDE_PAGE_H_
#define TLDR_CLIENT_INCLUDE_PAGE_H_

#include <fstream>
#include <iostream>
#include <string>

#include "config.h"

using std::ifstream;
using std::string;

namespace tldr {

// Render a page.
class Page {
 public:
  Page(const string &page_path, const Theme &theme)
      : theme_(theme), last_line_type_(kNone), page_file_(page_path) {}
  bool Show();

 private:
  // The type of the last line.
  enum {
    kNone,
    kTitle,
    kCmdDescription,
    kCodeDescription,
    kInlineCode,
    kCodeBlock
  } last_line_type_;

  void Strim();
  void StrimLeft();
  void StrimRight();
  void RenderTitle();
  void RenderCmdDescription();
  void RenderCodeDescription();
  void RenderInlineCode();  // inline code.
  void RenderCodeBlock();   // multiple lines of code.

  string current_line_;
  Theme theme_;
  const string kBlankChars{" \t"};
  ifstream page_file_;
};

}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_PAGE_H_
