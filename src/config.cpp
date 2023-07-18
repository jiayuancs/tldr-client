#include "config.h"

#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <fstream>

#ifndef NDEBUG
#include <iostream>
#endif  // NDEBUG

namespace tldr {
namespace config {

string platform = "linux";
string platform_common = "common";
string cache_path;
string git_repo_path;
string pages_path;

const string git_repo_name = "tldr";
string git_repo_url = "https://github.com/jiayuancs/tldr-pages.git";

namespace color {

string title = "\033[1;37m";             // bold; white
string title_modified_tag = "\033[33m";  // yellow
string title_tag_new_tag = "\033[32m";   // green
string cmd_description = "\033[37m";     // white
string code_description = "\033[32m";    // green
string code = "\033[33m";                // yellow
string code_placeholder = "\033[34m";    // bule
string reset = "\033[0m";

}  // namespace color


// Read or create config file, set global variables
void init_config(string suffix) {
  string home_path = getenv("HOME");
  if (home_path.empty()) {
    std::runtime_error("Environment variable $HOME not set");
  }

  cache_path = home_path + "/.tldrc";
  git_repo_path = cache_path + "/" + git_repo_name;
  string conf_path = cache_path + "/tldr.conf";

  // TODO: read or create config file, get platform, tldr pages suffix, etc.
  if (!std::filesystem::exists(conf_path)) {
    std::filesystem::create_directories(cache_path);
    std::ofstream conf_file{conf_path};
    conf_file << "git_repo_url = " << git_repo_url << std::endl;
  }

  // Use pages.{{suffix}} as the default `tldr pages` directory.
  suffix = suffix.empty() ? "" : "." + suffix;
  pages_path = cache_path + "/" + git_repo_name + +"/pages" + suffix;

#ifndef NDEBUG
  std::clog << "[log] platform = " << platform << std::endl;
  std::clog << "[log] cache_path = " << cache_path << std::endl;
  std::clog << "[log] pages_path = " << pages_path << std::endl;
  std::clog << "[log] git_repo_path = " << git_repo_path << std::endl;
  std::clog << "[log] git_repo_name = " << git_repo_name << std::endl;
  std::clog << "[log] git_repo_url = " << git_repo_url << std::endl;
  std::clog << std::endl;
#endif
}

}  // namespace config
}  // namespace tldr
