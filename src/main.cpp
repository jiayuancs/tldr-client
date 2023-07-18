#include <iostream>
#include <filesystem>

#include "cxxopts.hpp"

int main(int argc, char **argv) {

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
    std::cout << "tldr version 0.1.0" << std::endl;
    return 0;
  }

  return 0;
}
