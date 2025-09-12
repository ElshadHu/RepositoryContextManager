#include "fs_travel.hpp"


//entry std::filesystem::directory_entry
namespace fsTravel {
	using namespace fs;

	void displayDirTree(const std::filesystem::path& pathToAnalyze, int depth) {
		std::error_code errCode;//empty err code
			
				//creates an iterator starting from the entry of the path and this will recursively travel through file or folders 
			for (auto entry = fs::recursive_directory_iterator(pathToAnalyze, errCode);entry != fs::recursive_directory_iterator();entry.increment(errCode)) {
				
				if (errCode) {
					std::cerr << "ERROR Cannot access " << entry->path() << ": " << errCode.message() << '\n';
					errCode.clear(); //clear it for next iteration
					continue; //skip  this one , go another
				}
			


			const auto fileOrDir = entry->path().filename().string();
			const auto level = entry.depth();
			const auto extension = entry->path().extension().string();
			if (entry->is_directory()) {
				std::cout << std::setw(level * 3) << "directory: " << fileOrDir << '\n';
			}
			else if (entry->is_regular_file() && allowedExtensions(extension)) {
				std::cout << std::setw(level * 3) << "file:" << fileOrDir << '\n';
			}
		}
		

	}

	bool allowedExtensions(const std::string& ext) {
		constexpr std::array<std::string_view, 16> allowedExts{
			".cpp", ".hpp", ".h", ".c",
			".js", ".py", ".java", ".ts", ".go",
			".json", ".yml", ".md", ".txt", ".xml"
		};
		if (std::find(allowedExts.begin(), allowedExts.end(), ext) != allowedExts.end())
			return true;
		return false;
	}

	void displayFileContents(const fs::path& pathToAnalyze) {

		//again will go recursively and  check the extensions and will go to read the file
		for (auto entry = recursive_directory_iterator(pathToAnalyze); entry != fs::recursive_directory_iterator(); entry++) {
			if (entry->is_regular_file()) {
				const auto extension = entry->path().extension().string();
				if (allowedExtensions(extension)) {
					readDisplayFile(entry->path());
				}
			}
		}
	}


	const std::string getLanguageExtension(const std::string& ext) {
		if (ext == ".cpp" || ext == ".hpp" || ext == ".h") {
			return "cpp";
		}
		else if (ext == ".c") {
			return "c";
		}
		else if (ext == ".js" || ext == ".mjs") {
			return "javascript";
		}
		else if (ext == ".py") {
			return "python";
		}
		else if (ext == ".java") {
			return "java";
		}
		else if (ext == ".ts") {
			return "typescript";
		}
		else if (ext == ".cs") {
			return "csharp";
		}
		else if (ext == ".go") {
			return "go";
		}
		else if (ext == ".json") {
			return "json";
		}
		else if (ext == ".xml") {
			return "xml";
		}
		else if (ext == ".yml") {
			return "yaml";
		}
		else if (ext == ".md") {
			return "markdown";
		}
		else if (ext == ".txt") {
			return "text";
		}
		return "text";
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
		std::cout << '\n';
	}

}