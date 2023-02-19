#pragma once

// Standard
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Common
#include "Common/Compiler.hpp"
#include "Common/Debug.hpp"
#include "Common/Logger.hpp"

// Disable all warnings for external headers
// This also guards against leaking warning pragmas
COMPILER_WARNINGS_DISABLE_ALL_PUSH()

// External/fmt
#include <fmt/format.h>

// External/spdlog
#include <spdlog/spdlog.h>

// External/SDL
#include <SDL.h>

// Restore disabled warnings
COMPILER_WARNINGS_DISABLE_ALL_POP()

// Common
#include "Common/NonCopyable.hpp"
#include "Common/ScopeGuard.hpp"
