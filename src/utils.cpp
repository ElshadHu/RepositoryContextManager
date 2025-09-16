#include "utils.hpp"


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





 //constexpr for compile time
bool isExcludedDirectory(const std::filesystem::path& p) {
	constexpr std::array<std::string_view, 10> dirs{
		".git","build","out","dist","node_modules","CMakeFiles",".vs",".idea","target","cmake-build-debug"
	};
	for (const auto& dir : p) {
		auto stringDir = dir.string();
		if (std::find(dirs.begin(), dirs.end(), stringDir) != dirs.end()) return true;
	}

	return false;

}


bool isExcludedFile(const std::filesystem::path& p) {
	const auto fileExtension = p.extension().string();
	if (fileExtension == ".gitignore") return true;
	return false;

}

bool allowedExtensions(const std::string& ext) {
	constexpr std::array<std::string_view, 14> allowedExts{
		".cpp", ".hpp", ".h", ".c",
		".js", ".py", ".java", ".ts", ".go",
		".json", ".yml", ".md", ".xml"
	};
	if (std::find(allowedExts.begin(), allowedExts.end(), ext) != allowedExts.end())
		return true;
	return false;
}


std::size_t countTokens(const std::filesystem::path& filepath) {
	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "file did not open for tokens: " << filepath << '\n';
		return 0;
	}
	char perChar;
	std::size_t numOfChars = 0;
	while (file.get(perChar)) {
		numOfChars++;
	}

	return numOfChars / 4;
}



std::size_t countLines(const std::filesystem::path& filepath) {

	std::ifstream file(filepath);
	if (!file) {
		std::cerr << "file did not open for line counting: "<< filepath << '\n';
		return 0;
	}
	std::size_t numOfLines = 0;
	std::string line;
	while (std::getline(file, line)) {
		++numOfLines;
	}
	return numOfLines;
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
