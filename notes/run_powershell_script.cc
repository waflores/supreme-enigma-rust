#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

#include "tools/cpp/runfiles/runfiles.h"
using bazel::tools::cpp::runfiles::Runfiles;

int main(int argc, char **argv) {
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));

  // Important:
  //   If this is a test, use Runfiles::CreateForTest(&error).
  //   Otherwise, if you don't have the value for argv[0] for whatever
  //   reason, then use Runfiles::Create(&error).

  //   if (runfiles == nullptr) {
  // error handling
  //   }

  std::string powershell_script =
      runfiles->Rlocation("_main/notes/DisplayScript.ps1");

  std::cout << "Hello from Rustoelem! Trying to read the powershell file now:"
            << std::endl
            << std::endl;
  std::ifstream ifs(powershell_script);
  std::cout << ifs.rdbuf() << std::endl;

  return 0;
}

//   if (!CreateProcessW(
//           /* lpApplicationName */ nullptr,
//           /* lpCommandLine */ mutable_commandline.get(),
//           /* lpProcessAttributes */ nullptr,
//           /* lpThreadAttributes */ nullptr,
//           /* bInheritHandles */ attr_list->InheritAnyHandles() ? TRUE :
//           FALSE,
//           /* dwCreationFlags */ (create_window ? 0 : CREATE_NO_WINDOW) |
//               (handle_signals ? 0
//                               : CREATE_NEW_PROCESS_GROUP) // So that
//                               Ctrl-Break
//                                                           // isn't
//                                                           propagated
//               | CREATE_SUSPENDED // So that it doesn't start a new job
//               itself | EXTENDED_STARTUPINFO_PRESENT |
//               CREATE_UNICODE_ENVIRONMENT,
//           /* lpEnvironment */ env,
//           /* lpCurrentDirectory */ cwd.empty() ? nullptr : cwd.c_str(),
//           /* lpStartupInfo */ &info.StartupInfo,
//           /* lpProcessInformation */ &process_info)) {
//     DWORD err = GetLastError();
//   }
