// @library
#pragma once

#include <functional>
#include <iostream>

#ifdef _WINDOWS
#define NOMINMAX
#include <Windows.h>
#endif

#include "platform.h"

enum class ConsoleColor { FG_RED, FG_GREEN, FG_BLUE, FG_DEFAULT };

short GetColorCodeWin(ConsoleColor color) {
  switch (color) {
    case ConsoleColor::FG_RED:
      return 4 | 8;
    case ConsoleColor::FG_GREEN:
      return 2 | 8;
    case ConsoleColor::FG_BLUE:
      return 1 | 8;
    case ConsoleColor::FG_DEFAULT:
      return 7;
  }
}

const char* GetColorCodeUnix(ConsoleColor color) {
  switch (color) {
    case ConsoleColor::FG_RED:
      return "\033[31m";
    case ConsoleColor::FG_GREEN:
      return "\033[32m";
    case ConsoleColor::FG_BLUE:
      return "\033[34m";
    case ConsoleColor::FG_DEFAULT:
      return "\033[39m";
  }
}

template <typename T>
void PrintStdOutColored(ConsoleColor color, const T& value) {
  if (!platform::UseColorOutput()) {
    std::cout << value;
    return;
  }
#ifdef _WINDOWS
  const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO buffer_info;
  GetConsoleScreenBufferInfo(stdout_handle, &buffer_info);
  const WORD old_color_attrs = buffer_info.wAttributes;
  fflush(stdout);

  SetConsoleTextAttribute(stdout_handle, GetColorCodeWin(color));

  std::cout << value;
  fflush(stdout);

  SetConsoleTextAttribute(stdout_handle, old_color_attrs);
#else
  std::cout << GetColorCodeUnix(color) << value
            << GetColorCodeUnix(ConsoleColor::FG_DEFAULT);
#endif
}
