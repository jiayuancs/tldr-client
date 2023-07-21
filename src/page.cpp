#include "page.h"

#include <filesystem>

namespace fs = std::filesystem;

using std::ifstream;

namespace tldr {

bool Page::Show() const {
  ifstream page_file{page_path_};
  if (!page_file.is_open()) {
    return false;
  }

  string buf;
  while (getline(page_file, buf)) {
    // Ignore blank lines.
    if (buf.empty()) {
      continue;
    }

    bool last_line_cmd_desc = false;
    switch (buf[0]) {
      case '#':
        std::cout << theme_.title << buf.substr(2) 
                  << theme_.reset << "\n\n";

        break;
      case '>':
        std::cout << theme_.cmd_description << buf.substr(2) 
                  << theme_.reset << "\n";
        break;
      case '-':
        std::cout << "\n" << theme_.code_description << buf 
                  << theme_.reset << "\n";
        break;
      case '`': {
        auto idx = buf.find('`', 1);
        buf[idx] = '\0';
        std::cout << "  " << theme_.code << buf.substr(1) << theme_.reset
                  << "\n";
      }
      break;
      default:
        break;
    }
  }

  std::cout << std::endl;
  return true;
}


}  // namespace tldr
