#include "page.h"

#include <filesystem>

namespace fs = std::filesystem;
namespace color = tldr::config::color;

using std::ifstream;

namespace tldr {

bool Page::Show() const {
  string page_path = GetPagePath();

  // Page not found.
  if (page_path.empty()) {
    return false;
  }

  ifstream page_file{page_path};

  string buf;
  while (getline(page_file, buf)) {
    // Ignore blank lines.
    if (buf.empty()) {
      continue;
    }

    bool last_line_cmd_desc = false;
    switch (buf[0]) {
      case '#':
        std::cout << color::title << buf.substr(2) 
                  << color::reset << "\n\n";

        break;
      case '>':
        std::cout << color::cmd_description << buf.substr(2) 
                  << color::reset << "\n";
        break;
      case '-':
        std::cout << "\n" << color::code_description << buf 
                  << color::reset << "\n";
        break;
      case '`': {
        auto idx = buf.find('`', 1);
        buf[idx] = '\0';
        std::cout << "  " << color::code << buf.substr(1) << color::reset
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

string Page::GetPagePath() const {
  string pages_path = config::pages_path + "/" + config::platform + 
                      "/" + command_ + ".md";
  string com_pages_path = config::pages_path + "/" + config::platform_common +
                          "/" + command_ + ".md";

  if (fs::exists(pages_path) && 
      fs::is_regular_file(pages_path)) {
    return pages_path;
  } else if (fs::exists(com_pages_path) &&
             fs::is_regular_file(com_pages_path)) {
    return com_pages_path;
  } else {
    return "";
  }
}

}  // namespace tldr
