#include <iostream>
#include <string>
#include <filesystem>
#include <iostream>
#include "cli.hpp"
#include "fs_travel.hpp"
#include "git_info.hpp"


//helper functions for finding .git

std::filesystem::path findGitRepository(const std::filesystem::path& beginPath) {
		std::filesystem::path searchingPath = std::filesystem::absolute(beginPath);//we get the absolute path
		//if it exists it will return  this path  that is the first check
		//later when we create the parentPath  and will change the path and gets the parent directory until it finds or path becomes same . if it does not find C:/ = C:/ break it and return empty {}
		while (!searchingPath.empty()) {
			if (std::filesystem::exists(searchingPath / ".git")) { 
				return searchingPath;
				}

			auto parentPath = searchingPath.parent_path();
			if (parentPath == searchingPath) {
				break;
			}
			searchingPath = parentPath;
		}
		//if did not find return empty path
		return std::filesystem::path{};
}

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
			std::cout << "# Repository Context\n\n";
			std::cout << "## File System Location\n\n";
			const auto path = std::filesystem::path(inputFile);
			std::filesystem::path absolutePath = std::filesystem::absolute(path);
			std::cout << absolutePath << '\n';


			std::filesystem::path gitRepoPath = findGitRepository(absolutePath);
			gitInfo::GitInfo gitData;

			if (!gitRepoPath.empty()) {
				gitData = gitInfo::getGitData(gitRepoPath.string());
			}



			if (!gitData.m_isGitRepository) {
				std::cout << "that is not a git repository\n";
			}
			else {
				std::cout << "- Commit: " << gitData.m_commit << '\n';
				std::cout << "- Branch: " << gitData.m_branch << '\n';
				std::cout << "- Author: " << gitData.m_author << '\n';
				std::cout << "- Date: " << gitData.m_date << '\n';
			}
			std::cout << "\n## Structure\n```\n";
			fsTravel::displayDirTree(path, 0);
			std::cout << "'''\n";
			std::cout << "\n ##FileContents\n";
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