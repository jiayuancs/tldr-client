#include <iostream>
#include <filesystem>

#include "cxxopts.hpp"

#include "config.h"
#include "page.h"
#include "version.h"

int main(int argc, char **argv) {
  // Read or create config file.
  tldr::Config config{};
  try {
    config.LoadConfig();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  cxxopts::Options options("tldr", "A tiny tldr client. More information: https://github.com/jiayuancs/tldr-client.");
  options.custom_help("[options]");
  options.positional_help("[command]");

  options.add_options("Available")
  ("c,command", "show the usage of command", cxxopts::value<std::string>())
  ("u,update", "update tldr pages", cxxopts::value<bool>())
  ("s,suffix", "specify the suffix of `tldr pages` directory, such as `-s zh` for `pages.zh`", cxxopts::value<std::string>())
  ("v,version", "show version", cxxopts::value<bool>())
  ("h,help", "show this help message", cxxopts::value<bool>());

  options.parse_positional({"command"});

  // Parse command line arguments
  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl << std::endl;
    std::cout << options.help() << std::endl;
    return 1;
  }

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result.count("version")) {
    std::cout << "tldr version " << PROJECT_VERSION_MAJOR << '.'
              << PROJECT_VERSION_MINOR << '.' << PROJECT_VERSION_PATCH
              << std::endl;
    return 0;
  }

  if (result.count("suffix")) {
    string suffix = result["suffix"].as<std::string>();
    config.SetSuffix(suffix);
  }

#ifndef NDEBUG
  config.PrintLog();
#endif  // NDEBUG

  if (result.count("update")) {
    // TODO: download tldr pages if not exist
    if (!std::filesystem::exists(config.GetGitRepoPath())) {
      std::cout << "No database.\n";
      std::cout << "Try: git clone " << config.GetGitRepoUrl() << " " << config.GetGitRepoPath() << std::endl;
      return 0;
    }

    // TODO: update tldr pages
    std::cout << "This option is not implemented yet.\n";
    std::cout << "Try: cd " << config.GetGitRepoPath() << " && git pull && cd -" << std::endl;
    return 0;
  }

  if (result.count("command")) {
    // Show the usage of command
    string command = result["command"].as<std::string>();
    string page_path = config.GetCommandPagePath(command);

    tldr::Page page{page_path, config.GetTheme()};
    if (!page.Show()) {
      std::cout << "No tldr entry for " << command << std::endl;
      std::cout << "Try: " << *argv << " -u" << std::endl;
    }

    return 0;
  }

  // Show the usage of tldr
  std::cout << options.help() << std::endl;
  return 0;
}
