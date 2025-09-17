#include "fs_travel.hpp"
#include <system_error>

//entry std::filesystem::directory_entry
namespace fsTravel {
	using namespace fs;


	static std::string indent(int n) { 
		return std::string(n * 3, ' '); 
	}

	void travelSingleFile(const fs::path& filePath) {

			std::cout << filePath.filename().string()<<'\n';
	}
	void  travelDirTree(const fs::path& pathToAnalyze, int depth) {
	
		std::error_code errCode;//empty err code

		try {

				if (fs::is_regular_file(pathToAnalyze) && !isGitIgnored(pathToAnalyze)) {
					travelSingleFile(pathToAnalyze);
					return;
					}
			for (const auto& entry : fs::directory_iterator(pathToAnalyze, errCode)) {
				if (errCode) {
					std::cerr << "Error entering" << entry.path() << errCode.message() << '/\n';
					errCode.clear();
					continue;
				}
				const auto filename = entry.path().filename().string();

				
				std::cout << indent(depth);

				if (entry.is_directory() && !isGitIgnored(entry.path())) {
					std::cout << filename << '\n';
					
					if (depth < 10) 
						travelDirTree(entry.path(), depth + 1);
					
				}
				else if (entry.is_regular_file() && !isGitIgnored(entry.path())) {
					const auto extension = entry.path().extension().string();
						std::cout << filename << "\n";
				}


			}

		}
		catch (const fs::filesystem_error& ex) {
			std::cerr << "Filesystem error: " << ex.what() << '\n';
		}


	}



	TotalStatistics travelFileContents(const fs::path& pathToAnalyze) {
		TotalStatistics totals{ 0,0,0 };
		std::error_code errCode;
		try {
			if (isGitIgnored(pathToAnalyze)) {
				return TotalStatistics{ 0, 0, 0 };
			}
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
						readDisplayFile(entry.path());
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