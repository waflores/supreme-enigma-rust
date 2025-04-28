#include <windows.h>
#include <shellapi.h>

#include <iostream>
#include <winuser.h>

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

  std::string b_powershell_script =
      runfiles->Rlocation("_main/notes/DisplayScript.ps1");

  //   We need to convert powershell_script to LPWSTR
  std::wstring _powershell_script(b_powershell_script.begin(),
                                  b_powershell_script.end());
  LPWSTR powershell_script = const_cast<wchar_t *>(_powershell_script.c_str());

  std::cout << "Hello from Rustoelem! Trying to read the powershell file now:"
            << std::endl
            << std::endl;

  LPCWSTR action_on_file = L"open";
  LPCWSTR interpreter = L"pwsh";
  ShellExecuteW(/* HWND  hwnd */ nullptr,
                /* LPCWSTR lpOperation */ action_on_file,
                /* LPCWSTR lpFile */ interpreter,
                /* LPCWSTR lpParameters */ powershell_script,
                /* LPCWSTR lpDirectory */ nullptr,
                /* INT nShowCmd */ SW_SHOWMAXIMIZED);
#if 0
  STARTUPINFOW si;
  PROCESS_INFORMATION pi;

  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  if (!CreateProcessW(
          /* lpApplicationName */ nullptr,
          /* lpCommandLine */ powershell_script,
          /* lpProcessAttributes */ nullptr,
          /* lpThreadAttributes */ nullptr,
          /* bInheritHandles */ FALSE,
          /* dwCreationFlags */ CREATE_NO_WINDOW | CREATE_NEW_PROCESS_GROUP |
              CREATE_SUSPENDED | CREATE_UNICODE_ENVIRONMENT,
          /* lpEnvironment */ nullptr,
          /* lpCurrentDirectory */ nullptr,
          /* lpStartupInfo */ &si,
          /* lpProcessInformation */ &pi)) {
    std::cerr << "CreateProcess failed (" << GetLastError() << ").\n";
    return 1;
  };

  std::cout << "Process created with ID: " << pi.dwProcessId << "\n";

  WaitForSingleObject(pi.hProcess, INFINITE);

  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
#endif

  return 0;
}

//   if (!
//   }
