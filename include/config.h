#ifndef TLDR_CLIENT_INCLUDE_CONFIG_H_
#define TLDR_CLIENT_INCLUDE_CONFIG_H_

#include <string>
#include <vector>

using std::string;

namespace tldr {
namespace config {

extern string platform;
extern string platform_common;
extern string cache_path;
extern string pages_path;
extern string git_repo_path;

extern const string git_repo_name;
extern string git_repo_url;

namespace color {

extern string title;
extern string title_modified_tag;
extern string title_tag_new_tag;
extern string cmd_description;
extern string code_description;
extern string code;
extern string code_placeholder;
extern string reset;

}  // namespace color

// Read or create config file, set global variables.
// `suffix` is the suffix of `tldr pages` directory.
void init_config(string suffix);

}  // namespace config
}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_CONFIG_H_
