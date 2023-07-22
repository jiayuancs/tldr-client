#ifndef TLDR_CLIENT_INCLUDE_CONFIG_H_
#define TLDR_CLIENT_INCLUDE_CONFIG_H_

#include <string>
#include <vector>

using std::string;

namespace tldr {

struct Theme {
  string title{"\033[1;37m"};             // bold; white
  string title_modified_tag{"\033[33m"};  // yellow
  string title_new_tag{"\033[32m"};       // green
  string cmd_description{"\033[37m"};     // white
  string code_description{"\033[32m"};    // green
  string inline_code{"\033[33m"};         // yellow
  string code_placeholder{"\033[34m"};    // bule
  string code_block{"\033[34m"};          // bule
  string reset{"\033[0m"};
};

class Config {
 public:
  Config() = default;

  // Load configuation from file, or create default configuation file if not exist.
  void LoadConfig();

  // Use pages.{{suffix}} as the default `tldr pages` directory.
  void SetSuffix(const string &suffix);

  // Get the path of the page of the command.
  string GetCommandPagePath(const string &command) const;

  string GetPlatform() const;
  string GetGitRepoPath() const;
  string GetPagesPath() const;
  string GetGitRepoUrl() const;
  Theme GetTheme() const;

#ifndef NDEBUG
  void PrintLog() const;
#endif  // NDEBUG

 private:
  string GetConfPath() const;

  // TODO: Get platform automatically.
  string platform_{"linux"};
  string cache_path_;
  string pages_suffix_{};
  string git_repo_url_{"https://github.com/jiayuancs/tldr-pages.git"};
  Theme theme_;
};

}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_CONFIG_H_
