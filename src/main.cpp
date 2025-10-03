#include <iostream>
#include <string>
#include <stdexcept>
#include "renderer.hpp"
#include "config_manager.hpp"
#include <toml++/toml.h>
#include <filesystem>

int main(int argc, char **argv) {

    try {
        cli::Options cfgOpt;
        cli::Options cliOpt;
        cli::Options opt;

        // Parse config.toml options
        cfgOpt = config::loadFromConfig("config.toml");
        // Parse cli options
        cliOpt = cli::parse(argc, argv);
        // Merge options, overiding any config options with cli options
        opt = cfgOpt;

        if (!cliOpt.outputFile.empty())
            opt.outputFile = cliOpt.outputFile;
        if (!cliOpt.includePattern.empty()) {
            opt.includePattern = cliOpt.includePattern;
            opt.onIncludeFilter = cliOpt.onIncludeFilter;
        }
        if (!cliOpt.excludePattern.empty()) {
            opt.excludePattern = cliOpt.excludePattern;
            opt.onExcludeFilter = cliOpt.onExcludeFilter;
        }
        if (cliOpt.recent) {
            opt.recent = true;
            opt.onRecentFilter = cliOpt.onRecentFilter;
        }
        if (cliOpt.dirsOnly)
            opt.dirsOnly = true;
        if (cliOpt.showHelp)
            opt.showHelp = true;
        if (cliOpt.showVersion)
            opt.showVersion = true;
        if (!cliOpt.inputFiles.empty())
            opt.inputFiles = cliOpt.inputFiles;

        if (output::writeCliCommands(opt)) {
            return 0;
        }
        output::renderRepositoryContext(opt.outputFile, opt);
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}