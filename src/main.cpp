#include <iostream>
#include <string>
#include <stdexcept>
#include "renderer.hpp"




int main(int argc, char**argv) {
    try {
        cli::Options opt = cli::parse(argc, argv);

           // checking filters via static variables 
        setFiltering(opt.fileExtension, opt.excludePattern, opt.recent);

        if (output::writeCliCommands(opt)) {
            return 0;
        }

        // Parse command line arguments
        output::renderRepositoryContext(opt.outputFile, opt);

    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}