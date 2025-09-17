#include "utils.hpp"

	//we are gonna initialize these variable and during the execution we will check
	static  std::string m_includedExtension;
	static std::string m_excludedExtension;


	bool isGitIgnored(const std::filesystem::path& filePath) {
		constexpr std::array<std::string_view, 22> ignoredGit{
			".d", ".slo", ".lo", ".o", ".obj", ".gch", ".pch", ".ilk",
		".pdb", ".so", ".dylib", ".dll", ".mod", ".smod", ".lai",
		".la", ".a", ".lib", ".exe", ".out", ".app", ".dwo"
		};
		constexpr std::array<std::string_view, 8>ignoredDirs{
			".vs", "build", "out", ".git", ".github", ".gitignore", ".gitmodules", ".gitattributes"
		};
		std::string extension = filePath.extension().string();
		std::string filename = filePath.filename().string();

		//if it finds return it
		if (std::find(ignoredGit.begin(), ignoredGit.end(), extension) != ignoredGit.end())
			return true;

		for (const auto& entry : filePath) {
			std::string dirName = entry.string();
			if (std::find(ignoredDirs.begin(), ignoredDirs.end(), dirName) != ignoredDirs.end())
				return true;
		}

		return false;

	}

	void setFiltering(const std::string& include, const std::string& exclude) {
		m_includedExtension = include;
		m_excludedExtension = exclude;
	}

	bool checkingExcludeInclude(const std::filesystem::path& filepath) {
		if (!m_includedExtension.empty() && !onlyIncludedExtensions(filepath.string(), m_includedExtension)) {
			return false;
		}
		if (!m_excludedExtension.empty() && excludedExtensions(filepath.string(), m_excludedExtension)) {
			return false;
		}

		return true;
	}

	bool onlyIncludedExtensions(const std::string& filepath,const std::string&includedFiles) {
		if (filepath.empty()) {
			return false;
		}
		if (includedFiles.empty()) {
			return true;
		}
		
		std::stringstream ss(includedFiles);
		std::string str;
		std::vector<std::string> fileExtensions;

		while (std::getline(ss, str, ',')) {
			std::size_t posFirst = str.find_first_not_of('\t');
			std::size_t posLast = str.find_last_not_of('\t');
			str = str.substr(posFirst, posLast - posFirst + 1);
			fileExtensions.push_back(str);
		}

		std::filesystem::path path(filepath);
		std::string extension = path.extension().string();

		for (auto& included : fileExtensions) {
			if (included.size()>2 && included[0] == '*') {
				included = included.substr(1);//remove *
			}
			if (included == extension) {
				return true;
			}
		}
		return false;

	}

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








bool excludedExtensions(const std::string& filepath, const std::string& excludedExtension) {
	if (excludedExtension.empty()) return false;
	std::filesystem::path path(filepath);
	std::string filename = path.filename().string();
	std::string extension = path.extension().string();

	std::stringstream ss(excludedExtension);
	std::string keyFeature;
	while (std::getline(ss, keyFeature, ',')) {
		std::size_t posFirst = keyFeature.find_first_not_of(" \t");
		std::size_t posLast = keyFeature.find_last_not_of(" \t");
		if (posFirst != std::string::npos) {
			keyFeature = keyFeature.substr(posFirst, posLast - posFirst + 1);
		}

		if (filename.find(keyFeature) != std::string::npos) {
			return true;
		}

		if (keyFeature[0] == '.' && extension == keyFeature) {
			return true;
		}

		for (const auto& part : path) {
			if (part.string().find(keyFeature) != std::string::npos) {
				return true;
			}
		}
	}
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
