// @library
#pragma once

/**
 * This file defines platform-interfaces to several platform-specific
 * function.
 */

#ifdef _WINDOWS
#include <io.h>
#include <sys/stat.h>
#include <sys/types.h>  //must precede sys/stat.h
#include <cstdio>
#else  // UNIX
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace platform {

bool ENABLE_COLOR_OUTPUT = true;

int StdOutFd() {
#ifdef _WINDOWS
  return _fileno(stdout);
#else
  return STDOUT_FILENO;
#endif
}

int IsATty(int fd) {
#ifdef _WINDOWS
  return _isatty(fd);
#else
  return isatty(fd);
#endif
}

bool UseTtyOutput() {
  static int cached = IsATty(StdOutFd());
  return static_cast<bool>(cached);
}

bool UseColorOutput() { return UseTtyOutput() && ENABLE_COLOR_OUTPUT; }

bool IsDir(const char* path) {
#ifdef _WINDOWS
  struct _stat buf {};
  _stat(path, &buf);
  return (buf.st_mode & S_IFDIR) == S_IFDIR;
#else
  struct stat buf {};
  stat(path, &buf);
  return S_ISDIR(buf.st_mode);
#endif
}

char PathSep() {
#ifdef _WINDOWS
  return '\\';
#else
  return '/';
#endif
}

}  // namespace platform
