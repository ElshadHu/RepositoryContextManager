#include "config_manager.hpp"
namespace config {
    cli::Options loadFromConfig(const std::string &path) {
        cli::Options opts;

        if (!std::filesystem::exists(path)) { // Config doesn't exist; return default options
            return opts;
        }

        try {
            auto tbl = toml::parse_file(path); // Parse TOML file into table
            
            // Loading of each argument value from table
            if (auto out = tbl["output"].value<std::string>()) // Checks if key exists and assigns string
                opts.outputFile = *out; // Dereferences and stores the string in Options struct

            if (auto inc = tbl["include"].value<std::string>()) {
                opts.includePattern = *inc;
                std::string pattern = *inc; // Copy for use in lambda
                // Takes in variable pattern and argument for file path and passes into filter function
                opts.onIncludeFilter = [pattern](const std::filesystem::path &p) {
                    return onlyIncludedExtensions(p.string(), pattern); 
                };
            }

            if (auto exc = tbl["exclude"].value<std::string>()) {
                opts.excludePattern = *exc;
                std::string pattern = *exc;
                opts.onExcludeFilter = [pattern](const std::filesystem::path &p) {
                    return excludedExtensions(p.string(), pattern);
                };
            }

            if (auto rec = tbl["recent"].value<bool>(); rec && *rec) {
                opts.recent = true;
                opts.onRecentFilter = [](const std::filesystem::path &p) {
                    return isRecentlyModified(p);
                };
            }

            if (auto dirs = tbl["dirs_only"].value<bool>(); dirs && *dirs) {
                opts.dirsOnly = true;
            }
        }
        catch (const toml::parse_error &err) {
            std::cerr << "Failed to parse config.toml: " << err << "\n";
        }

        return opts;
    }
}
