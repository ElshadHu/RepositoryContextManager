#include "fs_travel.hpp"


//entry std::filesystem::directory_entry
namespace fsTravel {
	using namespace fs;

	void displayDirTree(const std::filesystem::path& pathToAnalyze, int depth) {

		
		for (auto entry = fs::recursive_directory_iterator(pathToAnalyze);entry != fs::recursive_directory_iterator();entry++) {
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
		constexpr std::array<std::string_view, 2>allowedExts{ ".hpp",".cpp"};
		if (std::find(allowedExts.begin(), allowedExts.end(), ext) != allowedExts.end())
			return true;
		return false;
	}

	void displayFileContents(const fs::path& pathToAnalyze) {
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
		if (ext == ".hpp" || ext == ".cpp") {
			return "cpp";
		}
		return"not found";
	}

	void readDisplayFile(const fs::path& filepath) {
		std::ifstream file(filepath);
		if (!file.is_open()) {
		std::cerr << "cannot open file: " << filepath << '\n';
		return;
		}

		std::cout << "\n### File:" << fs::relative(filepath) << '\n';
		std::string format = filepath.extension().string();
		std::cout << "'''" << getLanguageExtension(format) << '\n';
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