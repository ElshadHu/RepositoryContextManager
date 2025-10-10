#include <iostream>
#include <string>
#include <stdexcept>
#include "renderer.hpp"
#include "config_manager.hpp"
#include <filesystem>

int main(int argc, char **argv) {

    try {

       auto configOpts = config::loadFromConfig("config.toml");
        auto cliOpts = cli::parse(argc, argv);
        auto options = config::mergeOptions(configOpts, cliOpts);

        if (output::writeCliCommands(options)) {
            return 0;
        }

        output::renderRepositoryContext(options.outputFile, options);
    }
    catch (const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}