#include <iostream>
#include <string>
#include <filesystem>
#include <iostream>
#include "cli.hpp"
#include "fs_travel.hpp"
#include "git_info.hpp"


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
			std::cout << "REPOSITORY CONTEXT\n";
			std::cout << "Filesystem location\n";
			const auto path = std::filesystem::path(inputFile);
			std::filesystem::path absolutePath = std::filesystem::absolute(path);
			std::cout << absolutePath << '\n';

			gitInfo::GitInfo gitData = gitInfo::getGitData(".");

			if (!gitData.m_isGitRepository) {
				std::cout << "that is not a git repository\n";
			}
			else {
				std::cout << "- Commit: " << gitData.m_commit << '\n';
				std::cout << "- Branch: " << gitData.m_branch << '\n';
				std::cout << "- Author: " << gitData.m_author << '\n';
				std::cout << "- Date: " << gitData.m_date << '\n';
			}
			std::cout << "\n STRUCTURE \n";
			fsTravel::displayDirTree(path, 0);
			std::cout << "'''\n";
			std::cout << "\nFileContents\n";
			fsTravel::displayFileContents(path);

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