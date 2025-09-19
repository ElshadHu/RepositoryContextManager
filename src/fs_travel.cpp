#include "fs_travel.hpp"
#include <system_error>

namespace fsTravel {
	using namespace fs;

	//current file function which is not used except for this folder
	static std::string indent(int n) { 
		return std::string(n * 2, ' '); 
	}
	//for single file
	void travelSingleFile(const fs::path& filePath) {

			std::cout << filePath.filename().string()<<'\n';
	}


	/*
	 - Recursively traverses directory structure and displays tree structure
	 - Uses recursion with indentation to show hierarchy
	 - Respects git ignore patterns and handles filesystem errors in a correct way
	  - pathToAnalyze - root path to start go through from
	- depth - current recursion depth which is used for indentation
	 */

	void  travelDirTree(const fs::path& pathToAnalyze, int depth) {
		
		std::error_code errCode;//empty error code

		try {

				if (fs::is_regular_file(pathToAnalyze) && !isGitIgnored(pathToAnalyze)) {
					travelSingleFile(pathToAnalyze);
					return;
				}

			for (const auto& entry : fs::directory_iterator(pathToAnalyze, errCode)) {
				if (errCode) {
					std::cerr << "Error while iterating:" << entry.path() << errCode.message() << '/\n';
					errCode.clear();
					continue;
				}
				const auto fileOrDir = entry.path().filename().string();

				
				
				// Process directories recursively
				if (entry.is_directory() && !isGitIgnored(entry.path())) {
					std::cout << indent(depth)<< "/" << fileOrDir << '\n';
						travelDirTree(entry.path(), depth + 1);	
				}
				//Display regular files in the structure
				else if (entry.is_regular_file() && !isGitIgnored(entry.path())) {
					const auto extension = entry.path().extension().string();
						std::cout <<indent(depth) << fileOrDir << "\n";
				}


			}

		}
		catch (const fs::filesystem_error& ex) {
			std::cerr << "Filesystem error in the structure: " << ex.what() << '\n';
		}


	}


		/*
		 Main file processing function - analyzes all files and creates content
		 Applies include and  exclude patterns, goes through file contents, and gets statistics
		 Uses recursive directory iteration for discovering files 
		 TotalStatistics containing file count, line count, and token count
		*/

	TotalStatistics travelFileContents(const fs::path& pathToAnalyze) {
		TotalStatistics totals{ 0,0,0 };
		std::error_code errCode;
		try {
			if (isGitIgnored(pathToAnalyze)) {
				return TotalStatistics{ 0, 0, 0 };
			}
			//we are able to check via checkincludeExclude whether we need to exclude or include
			if (fs::is_regular_file(pathToAnalyze) && checkingExcludeInclude(pathToAnalyze) && !isGitIgnored(pathToAnalyze)) {
			
					totals.m_totalFiles = 1;
					totals.m_totalLines = countLines(pathToAnalyze);
					totals.m_totalTokens = countTokens(pathToAnalyze);

					readDisplayFile(pathToAnalyze);
				return totals;
			}

			for (auto const& entry : fs::recursive_directory_iterator(pathToAnalyze, errCode)) {
				if (errCode) {
					std::cerr << "Error accessing " << entry.path() << ": " << errCode.message() << '\n';
					errCode.clear();
					continue;
				}

				
		
				if (entry.is_regular_file() && checkingExcludeInclude(entry.path()) && !isGitIgnored(entry.path())) {
					const auto extension = entry.path().extension().string();
						++totals.m_totalFiles;
						totals.m_totalLines += countLines(entry.path());
						totals.m_totalTokens += countTokens(entry.path());
						readDisplayFile(entry.path()); //every time calls the files via the help of recursion
				}
			}
		}
		catch (const fs::filesystem_error& ex) {
			std::cerr << "Filesystem error: " << ex.what() << '\n';
		}
		return totals;
	}


	void readDisplayFile(const fs::path& filepath) {

		std::ifstream file(filepath);
		if (!file.is_open()) {
			std::cerr << "cannot open file: " << filepath << '\n';
			return;
		}

		std::cout << "\n### File:" << fs::relative(filepath) << '\n';
		std::string format = filepath.extension().string();
		std::cout << "``` " << getLanguageExtension(format) << '\n';
		int bytes = 0;
		std::string str;
		bool truncated = false;
		while (std::getline(file, str)) {
			if (bytes + str.length() > SIZEOFFILE) {
				truncated = true;
				break;
			}
			std::cout << str << '\n';
			bytes += str.length() + 1;//for newline
		}
		if (truncated) {
			std::cout << "\n.. [File truncated - exceeded " << SIZEOFFILE << " bytes\n";
		}
		std::cout <<"```" << '\n';
	}

}