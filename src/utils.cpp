#include "utils.h"

namespace tldr {

// The system namespace defines system-specific functions.
namespace system {

// Create a child process to execute the command.
// On failure, -1 is returned. On success, return value of the command is
// returned. Note: the last element of `cmd` must be `nullptr`. e.g.
//     char *cmd[] = {"ls", "-l", "-h", nullptr};
//     RunCmd(cmd);
int RunCmd(char* const cmd[]) {
  pid_t pid = fork();
  if (pid < 0) {
    PrintInfo("Error: fork error");
    return -1;
  }

  // child process
  if (pid == 0) {
    execvp(cmd[0], cmd);
    // Error if execvp() returns.
    PrintInfo("Error: execvp error");
    return -1;
  }

  // parent process
  int status;
  if (wait(&status) == -1) {
    PrintInfo("Error: wait error");
    return -1;
  }

  if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  return -1;
}

}  // namespace system

// Same as `int RunCmd(char* const cmd[])`, but the last element of `cmd`
// doesn't need to be `nullptr`. e.g.
//     RunCmd({"ls", "-l", "-h"});
int RunCmd(const std::vector<std::string>& cmd) {
  // Convert std::vector<std::string> to char* [].
  std::vector<char*> cmd_array;
  for (const auto& arg : cmd) {
    cmd_array.push_back(const_cast<char*>(arg.c_str()));
  }
  cmd_array.push_back(nullptr);

  return tldr::system::RunCmd(cmd_array.data());
}

// Execute the command in the specified working directory.
int RunCmd(const std::vector<std::string>& cmd, const std::string working_dir) {
  // Go to the specified directory
  char old_working_dir[tldr::system::kMaxPathLength] = {0};
  char* tmp = getcwd(old_working_dir, tldr::system::kMaxPathLength);
  if (tmp != old_working_dir) {
    PrintInfo("Error: getcwd error");
    return -1;
  }
  if (chdir(working_dir.c_str()) != 0) {
    PrintInfo("Error: chdir error");
    return -1;
  }

  // Execute the command.
  int status = RunCmd(cmd);

  // Go back to the original directory
  if (chdir(old_working_dir) != 0) {
    PrintInfo("Error: chdir error");
    return -1;
  }

  return status;
}

// Print information.
void PrintInfo(const string& info) {
  std::cerr << info << " in " << __FUNCTION__ << std::endl;
}

}  // namespace tldr
