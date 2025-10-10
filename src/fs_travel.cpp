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

				if (fs::is_regular_file(pathToAnalyze)) {
					travelSingleFile(pathToAnalyze);
					return;
				}

			for (const auto& entry : fs::directory_iterator(pathToAnalyze, errCode)) {
				if (errCode) {
					std::cerr << "Error while iterating:" << entry.path() << errCode.message() << '/\n';
					errCode.clear();
					continue;
				}

				if (isGitIgnored(entry.path())) {
					continue;
				}

				const auto fileOrDir = entry.path().filename().string();

				
				
				
				if (entry.is_directory()) {
					std::cout << indent(depth)<< "/" << fileOrDir << '\n';
						travelDirTree(entry.path(), depth + 1);	
				}
				//Display regular files in the structure
				else if (entry.is_regular_file()) {
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

	void travelFileContents(const fs::path& pathToAnalyze) {
	
		std::error_code errCode;
		try {
			
			if (fs::is_regular_file(pathToAnalyze) && !isGitIgnored(pathToAnalyze)) {
					readDisplayFile(pathToAnalyze);
			}

			for (auto const& entry : fs::recursive_directory_iterator(pathToAnalyze, errCode)) {
				if (errCode) {
					std::cerr << "Error accessing " << entry.path() << ": " << errCode.message() << '\n';
					errCode.clear();
					continue;
				}

				if (entry.is_regular_file() && !isGitIgnored(entry.path())) {
					const auto extension = entry.path().extension().string();
						readDisplayFile(entry.path()); 
				}
			}
		}
		catch (const fs::filesystem_error& ex) {
			std::cerr << "Filesystem error: " << ex.what() << '\n';
		}
	}


	

}