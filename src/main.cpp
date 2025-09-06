#include <iostream>
#include <string>
#include "cli.hpp"

int main(int argc, char**argv) {
	try {
		cli::Options opt = cli::parse(argc, argv);
		if (opt.showVersion) {
			std::cout << std::string(argv[0]) + "release 0.1\n";
			return 0;
		}
		if (opt.showHelp) {
			std::cout << "the usage of repoctx [path..] [options]\n"
					<<"-h --help Show help\n"
					<<"-v --version Show version\n"
					<<" -o --output  Write output to file\n";
			return 0;
		}
		for (const auto inputFile : opt.inputFiles) {
			std::cout << " - " << inputFile << '\n';
		}
		if (!opt.outputFile.empty()) {
			std::cout << "you need to write output to " << opt.outputFile << '\n';
		}

	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << '\n';
		return 1;
	}
	return 0;
}