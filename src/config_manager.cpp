#include "config_manager.hpp"
#include <toml++/toml.h>
#include <filesystem>
#include <iostream>

ConfigManager::ConfigManager(const std::string &path)
    : configPath(path) {}

void ConfigManager::applyTo(cli::Options &options) const
{
    if (!std::filesystem::exists(configPath))
    {
        std::cerr << "Warning: " << configPath << " not found, using CLI args only.\n";
        return;
    }

    try
    {
        auto config = toml::parse_file(configPath);

        if (auto out = config["output"].value<std::string>())
            if (options.outputFile.empty())
                options.outputFile = *out;

        if (auto inc = config["include"].value<std::string>())
            if (options.includePattern.empty())
                options.includePattern = *inc;

        if (auto exc = config["exclude"].value<std::string>())
            if (options.excludePattern.empty())
                options.excludePattern = *exc;

        if (auto dirs = config["dirs_only"].value<bool>())
            options.dirsOnly = *dirs;

        if (auto rec = config["recent"].value<bool>())
            options.recent = *rec;
    }
    catch (const toml::parse_error &err)
    {
        std::cerr << "Error parsing " << configPath << ": "
                  << err.description()
                  << " at " << err.source().begin << "\n";
    }
}