#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <string>
#include "cli.hpp"
#include <toml++/toml.h>
#include <filesystem>
#include <iostream>

namespace config {
    cli::Options loadFromConfig(const std::string &path);
    cli::Options mergeOptions(const cli::Options& configOptions, const cli::Options& cliOpts);
}

#endif