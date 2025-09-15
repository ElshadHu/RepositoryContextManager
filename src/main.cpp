#include <iostream>
#include <string>
#include <stdexcept>
#include "renderer.hpp"




int main(int argc, char**argv) {
    try {
        // Parse command line arguments
        cli::Options opt = cli::parse(argc, argv);

        // Handle version flag
        if (opt.showVersion) {
            std::cout << "repoctx release 0.1\n";
            return 0;
        }

     
        if (opt.showHelp) {
            std::cout << "Usage: repoctx [path...] [options]\n"
                << "  -h, --help     Show help\n"
                << "  -v, --version  Show version\n"
                << "  -o, --output   Write output to file\n";
            return 0;
        }

      
        output::renderRepositoryContext(opt.outputFile, opt);

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}