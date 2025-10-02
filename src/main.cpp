#include <iostream>
#include <string>
#include <stdexcept>
#include "renderer.hpp"
#include "config_manager.hpp"
#include <toml++/toml.h>
#include <filesystem>

int main(int argc, char **argv)
{
    cli::Options opt;
    try
    {

        ConfigManager cfg;
        cfg.applyTo(opt);

        opt = cli::parse(argc, argv);

        if (output::writeCliCommands(opt))
        {
            return 0;
        }
        output::renderRepositoryContext(opt.outputFile, opt);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}