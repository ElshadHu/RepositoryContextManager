#include "renderer.hpp"

namespace output {

	std::ostream& targetOut(std::ofstream& file, const std::string& filename) {
		if (filename.empty())
			return std::cout;
		file.open(filename);
		if (!file)
			throw std::runtime_error("Error opening output File: " + filename);
		return file;

	}


	static std::filesystem::path findGitRepository(const std::filesystem::path& beginPath) {
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

	void writeGitInfo(std::ostream& o, const std::filesystem::path& absolute) {
		o << "### GIT INFO \n\n";

		const auto repo = findGitRepository(absolute);
		gitInfo::GitInfo gi;
		if (!repo.empty()) gi = gitInfo::getGitData(repo.string());
		if (!gi.m_isGitRepository) {
			o << "Not a git repository\n\n";
		}
		else {
			o << "- Commit: " << gi.m_commit << "\n"
				<< "- Branch: " << gi.m_branch << "\n"
				<< "- Author: " << gi.m_author << "\n"
				<< "- Date: " << gi.m_date << "\n\n";
		}

	}

	bool writeCliCommands( const cli::Options& opt) {
			if (opt.showHelp) {
				std::cout << "the usage of repoctx [path..] [options]\n"
					<< "-h --help Show help\n"
					<< "-v --version Show version\n"
					<< " -o --output  Write output to file\n"
					<< " --include  Include file extensions (*.cpp,*.h)\n"
					<< " --exclude  Exclude files \n";
				return true;
			}

			if (opt.showVersion) {
				std::cout << "repoctx release 0.1\n";
				return true;
			}

			
			return false;

	}



	void writeFileStructure(std::ostream& o, const std::filesystem::path& path) {
		o << "Structure\n\n";

		//Capturing cout output
		std::streambuf* original_out = std::cout.rdbuf();
		std::ostringstream caughtOut;
		std::cout.rdbuf(caughtOut.rdbuf());

		//calling my function
		fsTravel::travelDirTree(path, 0);

		//restoring cout
		std::cout.rdbuf(original_out);
		o << caughtOut.str() << "\n\n";


	}

	

	fsTravel::TotalStatistics writeFileContents(std::ostream& o, const std::filesystem::path& path) {
		//capturing the output

		std::streambuf* original_out = std::cout.rdbuf();
		std::ostringstream caughtOut;
		std::cout.rdbuf(caughtOut.rdbuf());
		//calling the function
		auto statistics = fsTravel::travelFileContents(path);
		std::cout.rdbuf(original_out);

		o << caughtOut.str();
		o << '\n';
		return statistics;
	}


	void renderRepositoryContext(const std::string& filename, const cli::Options& opt) {
		try {
			std::ofstream fileOutput;
			std::ostream& o = targetOut(fileOutput, filename);
			for (const auto& input : opt.inputFiles) {
				const auto absolute = std::filesystem::absolute(input);
				o << "# Repository Context\n\n";
				o << "## File System Location\n\n" << absolute.string() << "\n\n";
				if (!std::filesystem::exists(absolute)) {
					std::cerr << "Error: Path does not exist: " << absolute << std::endl;
					continue;
				}
				writeGitInfo(o, absolute);
				writeFileStructure(o, absolute);
				 auto  statistics = writeFileContents(o, absolute);
				 o << "## Summary\n";
				 o << "- Total Files: " << statistics.m_totalFiles << '\n';
				 o << "- Total Lines: " << statistics.m_totalLines << '\n';
				 o << "- Total tokens: " << statistics.m_totalTokens << '\n';
			}

		}
		catch (const std::exception& err) {
			std::cerr << "Error with rendering: " << err.what() << '\n';
		}
	}

}
