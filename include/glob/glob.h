
#pragma once
#include <string>
#include <vector>
#include <regex>

#ifdef GLOB_USE_GHC_FILESYSTEM
#include <ghc/filesystem.hpp>
#else
#include <filesystem>
#endif

namespace glob {

#ifdef GLOB_USE_GHC_FILESYSTEM
namespace fs = ghc::filesystem;
#else
namespace fs = std::filesystem;
#endif

/// \param pathname string containing a path specification
/// \return vector of paths that match the pathname
///
/// Pathnames can be absolute (/usr/src/Foo/Makefile) or relative (../../Tools/*/*.gif)
/// Pathnames can contain shell-style wildcards
/// Broken symlinks are included in the results (as in the shell)
std::vector<fs::path> glob(const std::string &pathname);

/// \param pathnames string containing a path specification
/// \return vector of paths that match the pathname
///
/// Globs recursively.
/// The pattern “**” will match any files and zero or more directories, subdirectories and
/// symbolic links to directories.
std::vector<fs::path> rglob(const std::string &pathname);

/// Runs `glob` against each pathname in `pathnames` and accumulates the results
std::vector<fs::path> glob(const std::vector<std::string> &pathnames);

/// Runs `rglob` against each pathname in `pathnames` and accumulates the results
std::vector<fs::path> rglob(const std::vector<std::string> &pathnames);

/// Initializer list overload for convenience
std::vector<fs::path> glob(const std::initializer_list<std::string> &pathnames);

/// Initializer list overload for convenience
std::vector<fs::path> rglob(const std::initializer_list<std::string> &pathnames);

std::regex compile_pattern_to_regex(std::string_view pattern);
} // namespace glob
