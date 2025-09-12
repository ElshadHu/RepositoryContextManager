#include"cli.hpp"
#include <iostream>
#include <stdexcept>

namespace cli {

	Options	parse(int argc, char** argv) {
		Options options;

		for (int i = 1; i < argc;i++) {
			std::string_view argument = argv[i]; //every time gets the imput and checks the below conditions
			if (argument == "-h" || argument == "--help") {
				options.showHelp = true;
			}
			else if (argument == "-v" || argument == "--version") {
				options.showVersion = true;
			}
			else if (argument == "-o" || argument == "--output") {
			
				if (i + 1 < argc) {
					options.outputFile = argv[++i];
			}
			else {
				throw std::runtime_error("Missing file name after " + std::string(argument));
				}
			}
			else {
				options.inputFiles.push_back(argument);
			}
		}

		if (options.inputFiles.empty()) {
			options.inputFiles.push_back(".");
		}
		return options;
}
}