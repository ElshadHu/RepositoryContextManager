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
		o << "## GIT INFO \n\n";

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

	bool writeCliCommands(const std::string& filename, cli::Options& opt) {
		try {
			std::ofstream outFile;
			std::ostream& o = targetOut(outFile, filename);

			if (opt.showHelp) {
				outFile << "the usage of repoctx [path..] [options]\n"
					<< "-h --help Show help\n"
					<< "-v --version Show version\n"
					<< " -o --output  Write output to file\n";
				return true;
			}

			if (opt.showVersion) {
				outFile << std::string(opt.inputFiles[0]) + "release 0.1\n";
				return true;
			}
			return false;
		}
		catch (const std::exception& err) {
			std::cerr << err.what() << '\n';
			return false;
		}

	}



	void writeFileStructure(std::ostream& o, const std::filesystem::path& path) {
		o << "Structure\n\n";

		//Capturing cout output
		std::streambuf* original_out = std::cout.rdbuf();
		std::ostringstream caughtOut;
		std::cout.rdbuf(caughtOut.rdbuf());

		//calling my function
		fsTravel::travelDirTree(path, 0);

		//resotring cout
		std::cout.rdbuf(original_out);
		o << caughtOut.str() << "\n\n";


	}

	void writeFileContents(std::ostream& o, const std::filesystem::path& path) {
		//capturing the output

		std::streambuf* original_out = std::cout.rdbuf();
		std::ostringstream caughtOut;
		std::cout.rdbuf(caughtOut.rdbuf());
		//calling the function
		fsTravel::travelFileContents(path);
		std::cout.rdbuf(original_out);

		o << caughtOut.str();
		o << '\n';

	}


	void renderRepositoryContext(const std::string& filename, const cli::Options& opt) {
		try {
			std::ofstream fileOutput;
			std::ostream& o = targetOut(fileOutput, filename);
			for (const auto& input : opt.inputFiles) {
				const auto absolute = std::filesystem::absolute(input);
				o << "# Repository Context\n\n";
				o << "## File System Location\n\n" << absolute.string() << "\n\n";

				writeGitInfo(o, absolute);
				writeFileStructure(o, absolute);
				writeFileContents(o, absolute);

				o << "## Summary\n";
				o << "Repository analysis complete.\n\n";
			}

		}
		catch (const std::exception& err) {
			std::cerr << "Errorr: " << err.what() << '\n';
		}
	}

}
