#ifndef TLDR_CLIENT_INCLUDE_UTILS_H_
#define TLDR_CLIENT_INCLUDE_UTILS_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

using std::string;

namespace tldr {

// The system namespace defines system-specific functions and constants.
namespace system {

namespace {
const int kMaxPathLength = 1024;  // Maximum path length.
}

// Create a child process to execute the command.
// On failure, -1 is returned. On success, return value of the command is
// returned. Note: the last element of `cmd` must be `nullptr`. e.g.
//     char *cmd[] = {"ls", "-l", "-h", nullptr};
//     RunCmd(cmd);
int RunCmd(char* const cmd[]);

}  // namespace system

// Same as `int RunCmd(char* const cmd[])`, but the last element of `cmd`
// doesn't need to be `nullptr`. e.g.
//     RunCmd({"ls", "-l", "-h"});
int RunCmd(const std::vector<std::string>& cmd);

// Execute the command in the specified working directory.
int RunCmd(const std::vector<std::string>& cmd, const std::string working_dir);

// Print information.
void PrintInfo(const string& info);

}  // namespace tldr

#endif  // TLDR_CLIENT_INCLUDE_UTILS_H_
