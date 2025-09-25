#include <iostream>
#include <string>
#include <stdexcept>
#include "renderer.hpp"




int main(int argc, char**argv) {
    try {
        cli::Options opt;


         opt = cli::parse(argc, argv);


        if (output::writeCliCommands(opt)) {
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