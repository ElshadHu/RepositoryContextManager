#include "config_manager.hpp"
namespace config
{

    cli::Options loadFromConfig(const std::string &path)
    {
        cli::Options opts;

        if (!std::filesystem::exists(path))
        {
            return opts;
        }

        try
        {
            auto tbl = toml::parse_file(path);

            if (auto out = tbl["output"].value<std::string>())
                opts.outputFile = *out;

            if (auto inc = tbl["include"].value<std::string>())
            {
                opts.includePattern = *inc;
                std::string pattern = *inc;
                opts.onIncludeFilter = [pattern](const std::filesystem::path &p)
                {
                    return onlyIncludedExtensions(p.string(), pattern);
                };
            }

            if (auto exc = tbl["exclude"].value<std::string>())
            {
                opts.excludePattern = *exc;
                std::string pattern = *exc;
                opts.onExcludeFilter = [pattern](const std::filesystem::path &p)
                {
                    return excludedExtensions(p.string(), pattern);
                };
            }

            if (auto rec = tbl["recent"].value<bool>(); rec && *rec)
            {
                opts.recent = true;
                opts.onRecentFilter = [](const std::filesystem::path &p)
                {
                    return isRecentlyModified(p);
                };
            }

            if (auto dirs = tbl["dirs_only"].value<bool>(); dirs && *dirs)
            {
                opts.dirsOnly = true;
            }
        }
        catch (const toml::parse_error &err)
        {
            std::cerr << "Failed to parse config.toml: " << err << "\n";
        }

        return opts;
    }

} // namespace config
