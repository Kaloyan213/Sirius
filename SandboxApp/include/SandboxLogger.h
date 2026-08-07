#pragma once

#include "Utility/Logger.h"

Logger& SandboxLogger () {
  static Logger instance ("Sandbox");
  return instance;
}