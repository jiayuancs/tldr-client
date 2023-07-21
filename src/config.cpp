#include "config.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <stdexcept>

#ifndef NDEBUG
#include <iostream>
#endif  // NDEBUG

#include "toml.hpp"

namespace fs = std::filesystem;

namespace tldr {

namespace {
// Default configuration.
const string kDefaultConfiguraton = R"(
[database]
git_repo_url = "https://github.com/jiayuancs/tldr-pages.git"
pages_suffix = ""
platform = "linux"
  )";
}

void Config::LoadConfig() {
  // Get $HOME
  string home_path = getenv("HOME");
  if (home_path.empty()) {
    std::runtime_error("Environment variable $HOME not set");
  }
  cache_path_ = home_path + "/.tldrc";
  string conf_path = GetConfPath();

  // Create default config file if not exist.
  if (!std::filesystem::exists(conf_path)) {
    std::filesystem::create_directories(cache_path_);
    std::ofstream conf_file{conf_path};
    conf_file << kDefaultConfiguraton << std::endl;
  }

  // Read and parse config file.
  const auto config = toml::parse(conf_path);
  if (config.contains("database")) {
    const auto &db = config.at("database");
    if (db.contains("git_repo_url"))
      git_repo_url_ = toml::find<string>(db, "git_repo_url");
    if (db.contains("pages_suffix"))
      pages_suffix_ = toml::find<string>(db, "pages_suffix");
    if (db.contains("platform")) platform_ = toml::find<string>(db, "platform");
  }
}

void Config::SetSuffix(const string &suffix) { pages_suffix_ = suffix; }

string Config::GetCommandPagePath(const string &command) const {
  string page_path =
      GetPagesPath() + "/" + GetPlatform() + "/" + command + ".md";
  string page_path_common = GetPagesPath() + "/common/" + command + ".md";

  if (fs::exists(page_path) && fs::is_regular_file(page_path)) {
    return page_path;
  }
  if (fs::exists(page_path_common) && fs::is_regular_file(page_path_common)) {
    return page_path_common;
  }
  return "";
}

string Config::GetPlatform() const { return platform_; }

string Config::GetGitRepoPath() const { return cache_path_ + "/tldr"; }

string Config::GetConfPath() const { return cache_path_ + "/tldr.conf"; }

string Config::GetPagesPath() const {
  string suffix = pages_suffix_.empty() ? "" : ("." + pages_suffix_);
  return cache_path_ + "/tldr/pages" + suffix;
}

string Config::GetGitRepoUrl() const { return git_repo_url_; }

Theme Config::GetTheme() const { return theme_; }

#ifndef NDEBUG
void Config::PrintLog() const {
  std::clog << "----------------------------------------\n";
  std::clog << "platform: " << GetPlatform() << std::endl;
  std::clog << "git_repo_url: " << GetGitRepoUrl() << std::endl;
  std::clog << "git_repo_path: " << GetGitRepoPath() << std::endl;
  std::clog << "pages_path: " << GetPagesPath() << std::endl;
  std::clog << "----------------------------------------\n";
}
#endif  // NDEBUG

}  // namespace tldr
