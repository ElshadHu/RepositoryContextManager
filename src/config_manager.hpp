#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <string>
#include "cli.hpp"

class ConfigManager
{
public:
    explicit ConfigManager(const std::string &path = "config.toml");
    void applyTo(cli::Options &options) const;

private:
    std::string configPath;
};

#endif