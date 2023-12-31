#include "page.h"

#include <regex>

namespace tldr {

bool Page::Show() {
  if (!page_file_.is_open()) {
    return false;
  }

  while (getline(page_file_, current_line_)) {
    // Delete blank characters.
    Strim();

    // Ignore blank lines.
    if (current_line_.empty()) {
      continue;
    }

    // Handle the <break> tag.
    HandleBreakTag();

    bool last_line_cmd_desc = false;
    switch (current_line_[0]) {
      case '#':
        RenderTitle();
        break;
      case '>':
        RenderCmdDescription();
        break;
      case '-':
        RenderCodeDescription();
        break;
      case '`':
        if (current_line_[1] == '`' && current_line_[1] == current_line_[2]) {
          RenderCodeBlock();
        } else {
          RenderInlineCode();
        }
        break;
      default:
        break;
    }
    std::cout << current_line_ << std::endl;
  }

  std::cout << std::endl;
  return true;
}

void Page::Strim() {
  StrimLeft();
  StrimRight();
}

void Page::StrimLeft() {
  size_t first = current_line_.find_first_not_of(kBlankChars);
  current_line_.erase(0, first);
}

void Page::StrimRight() {
  size_t last = current_line_.find_last_not_of(kBlankChars);
  current_line_.erase(last + 1);
}

void Page::RenderTitle() {
  // erase the first '#'.
  current_line_.erase(0, 1);
  StrimLeft();

  current_line_.insert(0, theme_.title);

  // [modified] tag theme.
  auto pos = current_line_.find("[modified]");
  if (pos != string::npos) {
    string color = theme_.reset + theme_.title_modified_tag;
    current_line_.insert(pos, color);
  }

  // [new] tag theme.
  pos = current_line_.find("[new]");
  if (pos != string::npos) {
    string color = theme_.reset + theme_.title_new_tag;
    current_line_.insert(pos, color);
  }

  current_line_.append(theme_.reset);

  last_line_type_ = kTitle;
}

void Page::RenderCmdDescription() {
  // Erase the first '>'.
  current_line_.erase(0, 1);
  StrimLeft();

  current_line_.insert(0, theme_.cmd_description);
  current_line_.append(theme_.reset);

  // Leave a blank line between the other paragraphs.
  if (last_line_type_ != kCmdDescription) {
    current_line_.insert(0, "\n");
  }

  last_line_type_ = kCmdDescription;
}

void Page::RenderCodeDescription() {
  current_line_.insert(1, theme_.code_description);
  current_line_.append(theme_.reset);

  // Leave a blank line between the other paragraphs.
  if (last_line_type_ != kCodeDescription) {
    current_line_.insert(0, "\n");
  } else {
    current_line_[0] = ' ';
  }

  last_line_type_ = kCodeDescription;
}

void Page::RenderInlineCode() {
  // Erase the first '`'.
  current_line_.erase(0, 1);
  current_line_.insert(0, theme_.inline_code);

  // Erase the last '`' if exists.
  int idx = current_line_.find_last_of("`");
  if (idx != string::npos) {
    current_line_.erase(idx, 1);
    current_line_.insert(idx, theme_.reset);
  } else {
    current_line_.append(theme_.reset);
  }

  // Render code placeholder.
  RenderPlaceholder(theme_.inline_code);

  // Indent two space characters
  current_line_.insert(0, "  ");

  // Leave a blank line between the other paragraphs.
  if (last_line_type_ != kInlineCode) {
    current_line_.insert(0, "\n");
  }

  last_line_type_ = kInlineCode;
}

void Page::RenderCodeBlock() {
  string buf = "\n" + theme_.code_block;

  while (getline(page_file_, current_line_)) {
    // end of code block.
    if (current_line_.find("```") != string::npos) {
      StrimLeft();
      if (current_line_.find("```") == 0) {
        break;
      }
    }

    buf.append("  " + current_line_ + "\n");
  }

  // Erase the last '\n'.
  if (buf[buf.size() - 1] == '\n') {
    buf.erase(buf.size() - 1, 1);
  }

  buf.append(theme_.reset);
  current_line_ = buf;

  last_line_type_ = kCodeBlock;
}

void Page::RenderPlaceholder(const string &end_theme) {
  static const string kPlaceholder = "(\\{\\{.*?\\}\\})";
  static const string fmt = theme_.code_placeholder + "$1" + end_theme;
  std::regex reg{kPlaceholder};
  current_line_ = std::regex_replace(current_line_, reg, fmt);
}

void Page::HandleBreakTag() {
  static const string kBreakTag = "<break>";
  auto idx = current_line_.rfind(kBreakTag);

  // Clean last_line_type_ if the current line end with <break> tag.
  if (idx != string::npos && idx == current_line_.size() - kBreakTag.size()) {
    current_line_.erase(idx, kBreakTag.size());
    last_line_type_ = kNone;
  }
}

}  // namespace tldr
